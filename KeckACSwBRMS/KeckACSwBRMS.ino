// Program Name: KeckACSTestset.ino
// Author: JP Fumo
// Date: 04/24/22
// Description:  The program controls the W.M. Keck ACS GALIL/Cypress Control
// Law evaluation module.
// =========================================================================
// History
// =========================================================================
// REV    DATE      Author
// 0.0.0  04/24/22  JPF Initial Integration
// 0.1.0  04/25/22  JPF Implemented Testset Menu Structure
// 0.1.1  04/26/22  JPF Integrated Rotary Switch GUI
// 0.1.2  04/27/22  JPF Integrated the GALIL Error, initial CL
// 0.2.0  04/28/22  JPF Motor Home, GALIL Motor Control Law
// 0.2.1  04/29/22  JPF Added elapsed time to GALIL control, and direction on sign of steps
// 0.2.2  04/30/22  JPF Integrated MTRPUL, and Error Integrator
// 0.2.3  05/01/22  JPF Integrated APC, and Error Integrator, weird vibration on complete
// 0.2.4  05/02/22  JPF Fixed vibration issue, A and B inverted in cable ...argh
// 0.2.5  05/02/22  JPF Work on error integration, not stepping for small increments
// 0.2.6  05/03/22  JPF not stepping for small increments (cont.)
// 0.2.7  05/04/22  JPF not stepping for small increments (cont.)
// 0.2.8  05/05/22  JPF Finished small steps.  Integrated I2C current sensor, and write to flash
// 0.2.9  05/20/22  JPF Integrate REV:A CCA
// 0.3.0  05/21/22  JPF Integrate Cypress Control Law
// 0.3.1  06/28/22  JPF Porting Paul's Cypress device interface...
// 0.3.2  07/21/22  JPF Added Cyptress Home Routine
// 0.3.3  07/28/22  JPF Re-integrated GALIL menu and write to SD card. Cleaned up dead code
// 0.4.0  08/04/22  PMR Split into multiple source files and remove more dead code/variables/defines

/***************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>

#include "Adafruit_GFX.h"
#include <HardwareSerial.h>
#include <TFT_eSPI.h>
#include <Wire.h>
#include "PCF8574.h"
#include <Adafruit_INA219.h>
#include "ILI9341_t3n.h"

#include <FastLED.h>

// For the CLI
#include <SerialCommands.h>

// For the JSON output of recorded position data
#include <ArduinoJson.h>

#include "KeckACS.h"




#pragma message "---------- BUILDING MAIN SKETCH ----------"

CRGB leds[1];

// Set i2c address
PCF8574 pcf8574(0x38); //pcf8574A addr = 0x70

Adafruit_INA219 ina219g(0x44);
Adafruit_INA219 ina219c(0x40);

long steps = 0;
int direction = 0;
uint32_t GalilStartTime, GalilEndTime;

boolean inmotion = false;

int encoder0Pos = 0;
int valRotary, lastValRotary;

int bufptr = 0;
int blockcnt = 0;
int delayval = 500; // delay for half a second
int ledToggle = 0;

File file;

// Date and time related
uint32_t time_now = 0;
String dataMessage;
unsigned char datamsg[640];


/* Structure for capturing data from movement */
#define MAX_SAMPLES 10000

StaticJsonDocument<100000> samples_json;

typedef struct {
  uint32_t ts;
  uint32_t apc;
  int16_t current;
} sample_t;

sample_t samples[MAX_SAMPLES];
uint32_t sample_index = 0;
uint32_t recording_oversample_time = 0;
bool SamplesAreCypress = false;

bool Data_Enable = false;
unsigned int GainAmp = 1;
long ElapsedTime = 0;

short Start = 1;
short menu = 19;  
short sample = 0;       // index for double buffer
uint8_t rotation = 0;
int buttonState = 0;
volatile bool RotaryFlag = false;

int TimeBetweenSamples = 1;  //seconds
bool processmenuflag = false;
bool processmenuitem = false;




int DataFiles = 0;
//int Position = 0;
int GALIL_Count = 0;
int GALIL_MTRPUL = 0;
int Cypress_Count = 0;
int mode = 0; // 0 = none, 1 = GALIL, 2 = Cypress
int MTRPUL = 0;
volatile long APC = 0;
int para1 = 0;
int para2 = 0;
int para3 = 0;
bool recording = false;
int GALIL_gain = 0;
int CYP_P = 0;
int CYP_I = 0;
int CYP_D = 0;
unsigned int Steps = 0;
unsigned int nsteps = 0;
bool write_file = false;


ILI9341_t3n tft = ILI9341_t3n(TFT_CS, TFT_DC, TFT_RST);

// Width and height of LCD
#define WIDTH  240  // was 320
#define HEIGHT 320  // was 240 

static int menuitem = 0;
static int pagenum = 0;

IntervalTimer myTimer;

typedef struct mv_t {
  union {
    int8_t b;
    int16_t w;
    int32_t l;
    float f;
  } mval;
} myi;


// Encapsulate each menu item
typedef struct menuitem_t {

  char menuname[40];  // Menu name
  itype_t itemtype;   // -1 = label, 0 = function call, 1 = selectable, 2 = editable, 3 = Exit
  int edittype;       // 0 = bool, 1 = int, 2 = unsigned nit, 3 = ON/OFF, 4 = FWD/REV
  int itemmin;        // min value
  int itemmax;        // max value
  myi mvalue;         // value
  int vsize;          // size of value 0 = b, 1 = w, 2 = l, 3 = f
  int level;          // what level
  int encodergain;    // what level
  int (*myfunc)(int); // function called on select

} myitem;


// define menu structures
struct menu {
  char title[40]; // title of page
  int numitems; // number of items
  myitem m[16]; // total number of items per menu page
} mymenu[6];  // six menus total


// Encoder A/B/index
volatile int A, B, C;


// SPI interrupt routine
void SPI_INT(void) {
  uint8_t c = 0;
  c = SPDR;
  Serial.printf("%d ", c);
}



void doEncoder()
{
  A = digitalRead(encoder0PinA);
  B = digitalRead(encoder0PinB);

#ifdef DEBUG_SWITCHES
  Serial.printf("rotary: a = %d, b = %d\n", A, B);
#endif

  RotaryFlag = true;
}

volatile   int sA, sB, sC;
void doStrutEncoderA()
{
  int r_sw = 0;
  sA = digitalRead(GALIL_A);
  sB = digitalRead(GALIL_B);

  if (sA == 0 && sB == 0)
    r_sw = 0;
  else if (sA == 1 && sB == 0)
    r_sw = 1;
  else if (sA == 0 && sB == 1)
    r_sw = 2;
  else if (sA == 1 && sB == 1)
    r_sw = 3;


  if (r_sw == 1 || r_sw == 2) {
    //CW;
    APC--;
    Serial.printf("A CW %d\n", APC);
  } else if (r_sw == 0 || r_sw == 3) {
    //CCW
    APC++;
    Serial.printf("A CCW %d\n", APC);
  }
  mymenu[PAGE_GALIL].m[APCREG].mvalue.mval.l = APC;
  //Serial.printf("a=%d, b=%d, r_sw= %d, APC= %d", sA, sB, r_sw, APC);
  //Serial.println("");
  //DrawMenus(pagenum);
}

void doStrutEncoderB()
{
  int r_sw = 0;
  sA = digitalRead(GALIL_A);
  sB = digitalRead(GALIL_B);

  if (sA == 0 && sB == 0)
    r_sw = 0;
  else if (sA == 1 && sB == 0)
    r_sw = 1;
  else if (sA == 0 && sB == 1)
    r_sw = 2;
  else if (sA == 1 && sB == 1)
    r_sw = 3;


  if (r_sw == 1 || r_sw == 2) {
    //CW;
    APC++;
    Serial.printf("B CCW %d\n", APC);
  } else if (r_sw == 0 || r_sw == 3) {
    //CCW
    APC--;
    Serial.printf("B CW %d\n", APC);
  }
  mymenu[PAGE_GALIL].m[APCREG].mvalue.mval.l = APC;

  //Serial.printf("a=%d, b=%d, r_sw= %d, APC= %d", sA, sB, r_sw, APC);
  //Serial.println("");
  //DrawMenus(pagenum);
}









void DrawMenus(int level) { // level = menu number

  String Dstr;
  String Tstr;
  char Teststr[40];
  int Xoffset = 10;
  int Yoffset = 25;
  int Yincrement = 20;
  int index = 1;
  int i;
  float etime;
  int myerror;

  tft.setTextSize(2);
  Dstr = " ft";
  Tstr = " in";
  tft.fillScreen(TFT_BLACK);
  tft.drawRect(0, 0, WIDTH, HEIGHT - 1, TFT_GREEN);
  tft.setCursor(10, 5);

  tft.setTextColor(TFT_ORANGE, TFT_BLACK);
  strcpy(Teststr, mymenu[level].title);

#ifdef DEBUG_MENUS
  Serial.printf("M>>> %d, %s\n", level, Teststr);
#endif

  tft.printf("%s", Teststr);
  tft.println("");

  if (level == PAGE_GALIL) { // update values

    if (abs(mymenu[PAGE_GALIL].m[CYCLES].mvalue.mval.l) >= 1) {
      mymenu[PAGE_GALIL].m[TOTAL].mvalue.mval.l = mymenu[PAGE_GALIL].m[STEPS].mvalue.mval.l * (int)mymenu[PAGE_GALIL].m[CYCLES].mvalue.mval.b;
    } else {
      mymenu[PAGE_GALIL].m[TOTAL].mvalue.mval.l = mymenu[PAGE_GALIL].m[STEPS].mvalue.mval.l;
    }

    myerror = readGALILError();
    mymenu[PAGE_GALIL].m[ERR].mvalue.mval.b = myerror;

#ifdef DEBUG_MENUS
    Serial.printf("Count: %d,TOTAL %d\n", (int)mymenu[PAGE_GALIL].m[CYCLES].mvalue.mval.b, (int)mymenu[PAGE_GALIL].m[TOTAL].mvalue.mval.l);
#endif
  }

  if (level == PAGE_CYPRESS) { // update values

    if (abs(mymenu[PAGE_CYPRESS].m[CYCLES].mvalue.mval.l) >= 1) {
      mymenu[PAGE_CYPRESS].m[TOTAL].mvalue.mval.l = (int)mymenu[PAGE_CYPRESS].m[STEPS].mvalue.mval.l * (int)mymenu[PAGE_CYPRESS].m[CYCLES].mvalue.mval.b;
    } else {
      mymenu[PAGE_CYPRESS].m[TOTAL].mvalue.mval.l = (int)mymenu[PAGE_CYPRESS].m[STEPS].mvalue.mval.b;
    }

#ifdef DEBUG_MENUS
    Serial.printf("Count: %d,TOTAL %d\n", (int)mymenu[PAGE_CYPRESS].m[CYCLES].mvalue.mval.b, (int)mymenu[PAGE_CYPRESS].m[TOTAL].mvalue.mval.l);
#endif
  }


  index = 1;
  for (i = 0; i < mymenu[level].numitems; i++) {

    tft.setCursor(Xoffset, Yoffset + Yincrement * index);

    if (i == menuitem) {

      if (processmenuitem == true) {
        tft.setTextColor(TFT_ORANGE, TFT_BLACK);
      } else {
        tft.setTextColor(TFT_GREEN, TFT_BLACK);
      }

      if (mymenu[level].m[i].itemtype == editable || mymenu[level].m[i].itemtype == noneditable ) {

        if (mymenu[level].m[i].vsize == 3) {

          tft.printf("%s: %d", mymenu[level].m[i].menuname, (int)mymenu[level].m[i].mvalue.mval.l);
          tft.println("");
          //GALIL_MTRPUL =  mymenu[1].m[1].mvalue.mval.l * mymenu[1].m[6].mvalue.mval.l;
          //mymenu[1].m[TOTAL].mvalue.mval.l = GALIL_MTRPUL;

        } else {

          tft.printf("%s: %d", mymenu[level].m[i].menuname, (int)(mymenu[level].m[i].mvalue.mval.b));
          tft.println("");
          //GALIL_MTRPUL =  mymenu[1].m[1].mvalue.mval.b * mymenu[1].m[6].mvalue.mval.b;
          //mymenu[1].m[TOTAL].mvalue.mval.b = GALIL_MTRPUL;
        }

      } else {
        tft.printf("%s", mymenu[level].m[i].menuname);
        tft.println("");
      }

    } else {

      tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);

      if (mymenu[level].m[i].itemtype == editable || mymenu[level].m[i].itemtype == noneditable ) {

        if ((level == PAGE_GALIL || level == PAGE_CYPRESS) && i == ELAPSED) {

          etime = (float)(mymenu[level].m[ELAPSED].mvalue.mval.l * 0.000001);
          tft.printf("%s: %f", mymenu[level].m[i].menuname, etime);

        } else if (level == PAGE_CYPREPLY && i == 9) {

          tft.printf("%s: %08d", mymenu[level].m[i].menuname, mymenu[level].m[i].mvalue.mval.l);

        } else {

          if (mymenu[level].m[i].vsize == 3) {

            tft.printf("%s: %d", mymenu[level].m[i].menuname, mymenu[level].m[i].mvalue.mval.l);
            tft.println("");

          } else {

            tft.printf("%s: %d", mymenu[level].m[i].menuname, mymenu[level].m[i].mvalue.mval.b);
            tft.println("");
          }
        }

      } else {
        tft.printf("%s", mymenu[level].m[i].menuname);
        tft.println("");
      }

    }

    index++;

#ifdef DEBUG_MENUS
    Serial.printf("i: %d, mval: %d\n", i, mymenu[level].m[i].mvalue.mval.l);
#endif

    tft.updateScreen();
  }


  //  if(level==CYPRESS){
  //    FillinCypressResponse(level);
  //    CypressStatus();
  //  }


}






int item_changed = 1; // draw it the first time

void CheckMenu() {

  if (!(buttonState = digitalRead(buttonSelectPin)))
  {
    Serial.println("ButtonSelect");
    menu = true;
    //Serial.printf("%d,", menuitem);
    //Serial.println("Menu Select");

    // Call a function
    if (mymenu[pagenum].m[menuitem].itemtype == funcall) {

      // If there's a function to call, call it.
      if ( mymenu[pagenum].m[menuitem].myfunc != NULL) {

        mymenu[pagenum].m[menuitem].myfunc(3);
      }

      // Advance to next menu
    } else if (mymenu[pagenum].m[menuitem].itemtype == selectable) {

      pagenum = menuitem + 1;

      // Exit
    } else if (mymenu[pagenum].m[menuitem].itemtype == myexit) {

      pagenum = 0;
      menuitem = 0;
      mode = 0;
    }
    //DrawMenus(pagenum);
    //CheckSW();
    item_changed = 1;
    tft.fillScreen(TFT_BLACK);
  }
  else if (!(buttonState = digitalRead(buttonUpPin)))
  {
    Serial.println("buttonUpPin");
    menuitem--;
    if (menuitem < 0)
      menuitem = mymenu[pagenum].numitems - 1; // point at the top of the list
    Serial.printf("%d,", menuitem);
    Serial.println("menuitem");
    delay(100);
    while (!(buttonState = digitalRead(buttonUpPin)));
    item_changed = 1;
    lastValRotary = 0;
    valRotary = 0;;
    tft.fillScreen(TFT_BLACK);
    //DrawMenus(pagenum);
  }
  else if (!(buttonState = digitalRead(buttonDownPin)))
  {
    
    menuitem++;
    if (menuitem > mymenu[pagenum].numitems - 1) // point at the bottom of the list
      menuitem = 0;
    
    #ifdef DEBUG_SWITCHES
    Serial.println("buttonDownPin");
    Serial.printf("%d,", menuitem);
    Serial.println("menuitem");
    #endif 

    delay(100);
    while (!(buttonState = digitalRead(buttonUpPin)));
    item_changed = 1;
    lastValRotary = 0;
    valRotary = 0;;
    tft.fillScreen(TFT_BLACK);
    //DrawMenus(pagenum);
  }
  if (item_changed == 1) { // from interrupt Button B

    #ifdef DEBUG_SWITCHES
    Serial.printf("%d,", menuitem);
    Serial.println("Menu Select");
    #endif 
    
    //menuitem = 0;
    DrawMenus(pagenum);
    //CheckSW();
    item_changed = 0;
  }
}



void CheckSW()
{
  while (menu == true) {
    //M5.update();
    if (!(buttonState = digitalRead(buttonDownPin)))
    {
      if (menuitem < mymenu[pagenum].numitems)
        menuitem++;
      Serial.printf("%d,", menuitem);
      Serial.println("Btn A");
      DrawMenus(pagenum);
      if (menuitem == mymenu[pagenum].numitems + 1) {
        menu = false;
        tft.fillScreen(TFT_BLACK);
      }

      delay(100);
      while (!(buttonState = digitalRead(buttonDownPin)));
    }
    else if (!(buttonState = digitalRead(buttonSelectPin)))
    {
      Serial.printf("%d,", menuitem);
      Serial.println("Btn B");
      processmenuitem = true;
      DrawMenus(pagenum);
      //ProcessMenus(pagenum);
      delay(100);
      while (!(buttonState = digitalRead(buttonSelectPin)));

    } else if (!(buttonState = digitalRead(buttonUpPin))) {
      if (menuitem > 0)
        menuitem--;
      Serial.printf("%d,", menuitem);
      Serial.println("Btn C");
      DrawMenus(pagenum);
      delay(100);
      while (!(buttonState = digitalRead(buttonUpPin)));
    }
  }
}


void toggleLED(void) {

  if (ledToggle > 1) {

    leds[0] = CRGB(50, 0, 0);
    FastLED.show();

  } else {

    leds[0] = CRGB(0, 50, 50);
    FastLED.show();

  }

  if (ledToggle >= 2)
    ledToggle = 0;
  else
    ledToggle++;
}


void configmenu(void) {

  char Teststr[40];
  // TOP LEVEL
  strcpy(mymenu[PAGE_TOP].title, "KECK ACS CONTROLS");
  strcpy(Teststr, mymenu[PAGE_TOP].title);

#ifdef DEBUG_MENUS
  Serial.printf("%s", Teststr);
  Serial.println("");
#endif

  /* -------------------------------------------------------- */
  /* TOP MENU */

  mymenu[PAGE_TOP].numitems = 6;
  strcpy(mymenu[PAGE_TOP].m[0].menuname, "GALIL CONTROLS");
  mymenu[PAGE_TOP].m[0].itemtype = selectable;
  mymenu[PAGE_TOP].m[0].level = 0;
  mymenu[PAGE_TOP].m[0].myfunc = NULL;

  strcpy(mymenu[PAGE_TOP].m[1].menuname, "CYPRESS CONTROLS");
  mymenu[PAGE_TOP].m[1].itemtype = selectable;
  mymenu[PAGE_TOP].m[1].level = 0;
  mymenu[PAGE_TOP].m[1].myfunc = NULL;

  strcpy(mymenu[PAGE_TOP].m[2].menuname, "CYPRESS STATUS");
  mymenu[PAGE_TOP].m[2].itemtype = label;
  mymenu[PAGE_TOP].m[2].level = 0;
  mymenu[PAGE_TOP].m[2].myfunc = NULL;

  strcpy(mymenu[PAGE_TOP].m[3].menuname, "CHANGE SSD");
  mymenu[PAGE_TOP].m[3].itemtype = funcall;
  mymenu[PAGE_TOP].m[3].level = 0;
  mymenu[PAGE_TOP].m[3].myfunc = NULL; // &ChangeSSD;

  strcpy(mymenu[PAGE_TOP].m[4].menuname, "GALIL PARAMS");
  mymenu[PAGE_TOP].m[4].itemtype = label;
  mymenu[PAGE_TOP].m[4].level = 0;
  mymenu[PAGE_TOP].m[4].myfunc = NULL;

  strcpy(mymenu[PAGE_TOP].m[5].menuname, "CYPRESS RESPONSE");
  mymenu[PAGE_TOP].m[5].itemtype = selectable;
  mymenu[PAGE_TOP].m[5].level = 0;
  mymenu[PAGE_TOP].m[5].myfunc = NULL;

  /* -------------------------------------------------------- */
  /* GALIL MENU */

  strcpy(mymenu[PAGE_GALIL].title, "GALIL CONTROLS");
  mymenu[PAGE_GALIL].numitems = 12;

  strcpy(mymenu[PAGE_GALIL].m[HOME].menuname, "HOME");
  mymenu[PAGE_GALIL].m[HOME].itemtype = funcall;
  mymenu[PAGE_GALIL].m[HOME].level = 0;
  mymenu[PAGE_GALIL].m[HOME].myfunc = &GALILHome;

  strcpy(mymenu[PAGE_GALIL].m[STEPS].menuname, "STEPS");
  mymenu[PAGE_GALIL].m[STEPS].encodergain = 10;
  mymenu[PAGE_GALIL].m[STEPS].itemtype = editable;
  mymenu[PAGE_GALIL].m[STEPS].level = 0;
  mymenu[PAGE_GALIL].m[STEPS].myfunc = NULL;
  mymenu[PAGE_GALIL].m[STEPS].vsize = 3;

  strcpy(mymenu[PAGE_GALIL].m[TOTAL].menuname, "TOTAL");
  mymenu[PAGE_GALIL].m[TOTAL].itemtype = noneditable;
  mymenu[PAGE_GALIL].m[TOTAL].level = 0;
  mymenu[PAGE_GALIL].m[TOTAL].vsize = 3;
  mymenu[PAGE_GALIL].m[TOTAL].myfunc = NULL;

  strcpy(mymenu[PAGE_GALIL].m[MAX].menuname, "MAX MOVE");
  mymenu[PAGE_GALIL].m[MAX].itemtype = funcall;
  mymenu[PAGE_GALIL].m[MAX].level = (int) NULL;
  mymenu[PAGE_GALIL].m[MAX].myfunc = &GALILMax;

  strcpy(mymenu[PAGE_GALIL].m[CLEAR].menuname, "CLEAR STEPS");
  mymenu[PAGE_GALIL].m[CLEAR].itemtype = funcall;
  mymenu[PAGE_GALIL].m[CLEAR].level = (int) NULL;
  mymenu[PAGE_GALIL].m[CLEAR].myfunc = &GALILClear;

  strcpy(mymenu[PAGE_GALIL].m[CYCLES].menuname, "CYCLES");
  mymenu[PAGE_GALIL].m[CYCLES].encodergain = 1;
  mymenu[PAGE_GALIL].m[CYCLES].itemtype = editable;
  mymenu[PAGE_GALIL].m[CYCLES].level = 0;
  mymenu[PAGE_GALIL].m[CYCLES].mvalue.mval.w = 1;
  mymenu[PAGE_GALIL].m[CYCLES].myfunc = NULL;
  mymenu[PAGE_GALIL].m[CYCLES].vsize = 1;

  strcpy(mymenu[PAGE_GALIL].m[ELAPSED].menuname, "ETIME");
  mymenu[PAGE_GALIL].m[ELAPSED].itemtype = noneditable;
  mymenu[PAGE_GALIL].m[ELAPSED].level = 0;
  mymenu[PAGE_GALIL].m[ELAPSED].myfunc = NULL;

  strcpy(mymenu[PAGE_GALIL].m[ERR].menuname, "ERROR");
  mymenu[PAGE_GALIL].m[ERR].itemtype = noneditable;
  mymenu[PAGE_GALIL].m[ERR].level = 0;
  mymenu[PAGE_GALIL].m[ERR].myfunc = NULL;

  strcpy(mymenu[PAGE_GALIL].m[APCREG].menuname, "APC");
  mymenu[PAGE_GALIL].m[APCREG].itemtype = noneditable;
  mymenu[PAGE_GALIL].m[APCREG].level = 0;
  mymenu[PAGE_GALIL].m[APCREG].myfunc = NULL;
  mymenu[PAGE_GALIL].m[APCREG].vsize = 3;

  strcpy(mymenu[PAGE_GALIL].m[RECORD].menuname, "RECORD");
  mymenu[PAGE_GALIL].m[RECORD].itemtype = editable;
  mymenu[PAGE_GALIL].m[RECORD].level = 0;
  mymenu[PAGE_GALIL].m[RECORD].myfunc = NULL;

  strcpy(mymenu[PAGE_GALIL].m[MGO].menuname, "GO");
  mymenu[PAGE_GALIL].m[MGO].itemtype = funcall;
  mymenu[PAGE_GALIL].m[MGO].level = 0;
  mymenu[PAGE_GALIL].m[MGO].myfunc = &GALILGo;

  strcpy(mymenu[PAGE_GALIL].m[MEXIT].menuname, "EXIT");
  mymenu[PAGE_GALIL].m[MEXIT].itemtype = myexit;
  mymenu[PAGE_GALIL].m[MEXIT].level = 0;
  mymenu[PAGE_GALIL].m[MEXIT].myfunc = NULL;

  /* -------------------------------------------------------- */
  /* CYPRESS MENU - CONTROLS */

  strcpy(mymenu[PAGE_CYPRESS].title, "CYPRESS CONTROLS");
  mymenu[PAGE_CYPRESS].numitems = 12;

  strcpy(mymenu[PAGE_CYPRESS].m[HOME].menuname, "HOME");
  mymenu[PAGE_CYPRESS].m[HOME].itemtype = funcall;
  mymenu[PAGE_CYPRESS].m[HOME].level = 0;
  mymenu[PAGE_CYPRESS].m[HOME].myfunc = &CypressHome;

  strcpy(mymenu[PAGE_CYPRESS].m[STEPS].menuname, "STEPS");
  mymenu[PAGE_CYPRESS].m[STEPS].encodergain = 10;
  mymenu[PAGE_CYPRESS].m[STEPS].itemtype = editable;
  mymenu[PAGE_CYPRESS].m[STEPS].level = 0;
  mymenu[PAGE_CYPRESS].m[STEPS].myfunc = NULL; //&drawTopPage;

  strcpy(mymenu[PAGE_CYPRESS].m[TOTAL].menuname, "TOTAL");
  mymenu[PAGE_CYPRESS].m[TOTAL].itemtype = noneditable;
  mymenu[PAGE_CYPRESS].m[TOTAL].level = 0;
  mymenu[PAGE_CYPRESS].m[TOTAL].myfunc = NULL;
  mymenu[PAGE_CYPRESS].m[TOTAL].vsize = 3;

  strcpy(mymenu[PAGE_CYPRESS].m[MAX].menuname, "MAX MOVE");
  mymenu[PAGE_CYPRESS].m[MAX].itemtype = funcall;
  mymenu[PAGE_CYPRESS].m[MAX].level = 0;
  mymenu[PAGE_CYPRESS].m[MAX].myfunc = &CypressMax;

  strcpy(mymenu[PAGE_CYPRESS].m[CLEAR].menuname, "CLEAR STEPS");
  mymenu[PAGE_CYPRESS].m[CLEAR].itemtype = funcall;
  mymenu[PAGE_CYPRESS].m[CLEAR].level = 0;
  mymenu[PAGE_CYPRESS].m[CLEAR].myfunc = &CypressClear;

  strcpy(mymenu[PAGE_CYPRESS].m[CYCLES].menuname, "CYCLES");
  mymenu[PAGE_CYPRESS].m[CYCLES].encodergain = 1;
  mymenu[PAGE_CYPRESS].m[CYCLES].itemtype = editable;
  mymenu[PAGE_CYPRESS].m[CYCLES].level = 0;
  mymenu[PAGE_CYPRESS].m[CYCLES].mvalue.mval.w = 1;
  mymenu[PAGE_CYPRESS].m[CYCLES].myfunc = NULL;
  mymenu[PAGE_CYPRESS].m[CYCLES].vsize = 1;

  strcpy(mymenu[PAGE_CYPRESS].m[ELAPSED].menuname, "ELAPSED");
  mymenu[PAGE_CYPRESS].m[ELAPSED].itemtype = noneditable;
  mymenu[PAGE_CYPRESS].m[ELAPSED].level = 0;
  mymenu[PAGE_CYPRESS].m[ELAPSED].myfunc = NULL;

  strcpy(mymenu[PAGE_CYPRESS].m[ERR].menuname, "ERROR");
  mymenu[PAGE_CYPRESS].m[ERR].itemtype = noneditable;
  mymenu[PAGE_CYPRESS].m[ERR].level = 0;
  mymenu[PAGE_CYPRESS].m[ERR].myfunc = NULL;

  strcpy(mymenu[PAGE_CYPRESS].m[APCREG].menuname, "APC");
  mymenu[PAGE_CYPRESS].m[APCREG].itemtype = noneditable;
  mymenu[PAGE_CYPRESS].m[APCREG].level = 0;
  mymenu[PAGE_CYPRESS].m[APCREG].vsize = 3;
  mymenu[PAGE_CYPRESS].m[APCREG].myfunc = NULL;

  strcpy(mymenu[PAGE_CYPRESS].m[RECORD].menuname, "RECORD");
  mymenu[PAGE_CYPRESS].m[RECORD].itemtype = noneditable;
  mymenu[PAGE_CYPRESS].m[RECORD].level = 0;
  mymenu[PAGE_CYPRESS].m[RECORD].myfunc = NULL;

  strcpy(mymenu[PAGE_CYPRESS].m[MGO].menuname, "GO");
  mymenu[PAGE_CYPRESS].m[MGO].itemtype = funcall;
  mymenu[PAGE_CYPRESS].m[MGO].level = 0;
  mymenu[PAGE_CYPRESS].m[MGO].myfunc = &CypressGo;

  strcpy(mymenu[PAGE_CYPRESS].m[MEXIT].menuname, "EXIT");
  mymenu[PAGE_CYPRESS].m[MEXIT].itemtype = myexit;
  mymenu[PAGE_CYPRESS].m[MEXIT].level = 0;
  mymenu[PAGE_CYPRESS].m[MEXIT].myfunc = NULL;


  /* -------------------------------------------------------- */
  /* CYPRESS MENU - RESPONSE */

  strcpy(mymenu[PAGE_CYPREPLY].title, "CYPRESS RESPONSE");
  mymenu[PAGE_CYPREPLY].numitems = 12;

  strcpy(mymenu[PAGE_CYPREPLY].m[0].menuname, "CHECKSUM");
  mymenu[PAGE_CYPREPLY].m[0].itemtype = noneditable;
  mymenu[PAGE_CYPREPLY].m[0].level = 0;
  mymenu[PAGE_CYPREPLY].m[0].myfunc = NULL;

  strcpy(mymenu[PAGE_CYPREPLY].m[1].menuname, "VERSION");
  mymenu[PAGE_CYPREPLY].m[1].encodergain = 10;
  mymenu[PAGE_CYPREPLY].m[1].itemtype = noneditable;
  mymenu[PAGE_CYPREPLY].m[1].level = 0;
  mymenu[PAGE_CYPREPLY].m[1].myfunc = NULL;

  strcpy(mymenu[PAGE_CYPREPLY].m[2].menuname, "MSG SIZE");
  mymenu[PAGE_CYPREPLY].m[2].itemtype = noneditable;
  mymenu[PAGE_CYPREPLY].m[2].level = 0;
  mymenu[PAGE_CYPREPLY].m[2].myfunc = NULL;

  strcpy(mymenu[PAGE_CYPREPLY].m[3].menuname, "OPCODE");
  mymenu[PAGE_CYPREPLY].m[3].itemtype = noneditable;
  mymenu[PAGE_CYPREPLY].m[3].level = 0;
  mymenu[PAGE_CYPREPLY].m[3].myfunc = NULL;

  strcpy(mymenu[PAGE_CYPREPLY].m[4].menuname, "STATE");
  mymenu[PAGE_CYPREPLY].m[4].itemtype = noneditable;
  mymenu[PAGE_CYPREPLY].m[4].level = 0;
  mymenu[PAGE_CYPREPLY].m[4].myfunc = NULL;

  strcpy(mymenu[PAGE_CYPREPLY].m[5].menuname, "FAULT");
  mymenu[PAGE_CYPREPLY].m[5].encodergain = 1;
  mymenu[PAGE_CYPREPLY].m[5].itemtype = editable;
  mymenu[PAGE_CYPREPLY].m[5].level = 0;
  mymenu[PAGE_CYPREPLY].m[5].myfunc = NULL;

  strcpy(mymenu[PAGE_CYPREPLY].m[6].menuname, "SEQUENCE");
  mymenu[PAGE_CYPREPLY].m[6].itemtype = noneditable;
  mymenu[PAGE_CYPREPLY].m[6].level = 0;
  mymenu[PAGE_CYPREPLY].m[6].myfunc = NULL;

  strcpy(mymenu[PAGE_CYPREPLY].m[7].menuname, "NUM CHKSUM");
  mymenu[PAGE_CYPREPLY].m[7].itemtype = noneditable;
  mymenu[PAGE_CYPREPLY].m[7].level = 0;
  mymenu[PAGE_CYPREPLY].m[7].myfunc = NULL;

  strcpy(mymenu[PAGE_CYPREPLY].m[8].menuname, "CURRENT");
  mymenu[PAGE_CYPREPLY].m[8].itemtype = noneditable;
  mymenu[PAGE_CYPREPLY].m[8].level = 0;
  mymenu[PAGE_CYPREPLY].m[8].myfunc = NULL;

  strcpy(mymenu[PAGE_CYPREPLY].m[9].menuname, "POSITION");
  mymenu[PAGE_CYPREPLY].m[9].itemtype = noneditable;
  mymenu[PAGE_CYPREPLY].m[9].level = 0;
  mymenu[PAGE_CYPREPLY].m[9].myfunc = &CypressGo;

  strcpy(mymenu[PAGE_CYPREPLY].m[10].menuname, "PWM");
  mymenu[PAGE_CYPREPLY].m[10].itemtype = noneditable;
  mymenu[PAGE_CYPREPLY].m[10].level = 0;
  mymenu[PAGE_CYPREPLY].m[10].myfunc = NULL;

  strcpy(mymenu[PAGE_CYPREPLY].m[11].menuname, "EXIT");
  mymenu[PAGE_CYPREPLY].m[11].itemtype = myexit;
  mymenu[PAGE_CYPREPLY].m[11].level = 0;
  mymenu[PAGE_CYPREPLY].m[11].myfunc = NULL;

}



void checkRotary(void) {
  int r_sw = 0;

  if (RotaryFlag == true) {
    //Serial.println("RotaryFlag==true");
    if (A == 0 && B == 0)
      r_sw = 0;
    else if (A == 1 && B == 0)
      r_sw = 1;
    else if (A == 0 && B == 1)
      r_sw = 2;
    else if (A == 1 && B == 1)
      r_sw = 3;

    if (r_sw == 1 || r_sw == 2) {
      //CW;
      valRotary++;
      //Serial.println("CW");
    } else if (r_sw == 0 || r_sw == 3) {
      //CCW
      valRotary--;
      //Serial.println("CCW");
    }
  }
  RotaryFlag = false;
}


static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  while (millis() - start < ms) {};
}


/* ----------------------------------------------------------------------------------------------------------- */
/* High Frequency rate groups at a base 10KHz */
void HighFrequency() { 

    static uint32_t brmsTask;                 // The BRMS schedule counter

    static uint32_t brmsRG1Mask = 0b00000001; // Rate group 1 mask
    static uint32_t brmsRG2Mask = 0b00000010; // Rate group 2 mask
    static uint32_t brmsRG3Mask = 0b00000100; // Rate group 3 mask
    static uint32_t brmsRG4Mask = 0b00001000; // Rate group 4 mask
    static uint32_t brmsRG5Mask = 0b00010000; // Rate group 5 mask
    static uint32_t brmsRG6Mask = 0b00100000; // Rate group 6 mask

    uint32_t ElapsedTime = 0;

    /* Increment the BRMS task counter infinitely */
    brmsTask++;

    /* Determine which rate group to run.  Do this by applying the rate group masks
       sequentially until one results in a "true" value.  
    
       For example: the 1st rate group is invoked every time the brmsTask value ends 
       in 0bxxx1, and ignored when it's 0bxxx0.  
    
       The second rate group is invoked half as often as the first: when the brmsTask
       value ends in 0bxx10. 
    
       The third rate group is invoked half as often as the second: when brmsTask
       ends in 0bx100.  
    
       In this way, we have decreasing tiers of tasks that are run for at most 200us.
    
       The "background" task does not run at interrupt level.  The main() of the program
       represents everything non time critical, using whatever CPU is left over when the
       interrupt returns.
    */

    /* Rate group 0 is run every 100us (every invocation).  Equal to a 10KHz update rate. */

    /* Move the Galil only when enabled! */
    if (GalilEnable) {
  
      if (galil_err == false && inmotion == true && Galil_SlowFlag == false) {
    
        /* If we are more than 15 steps away from the destination, stream them into the Galil controller */
        if (nsteps > 15) {
          
          nsteps -= 1;
          
          if (direction == CW) {
            digitalWrite(GALIL_INC, LOW);
            delayMicroseconds(10);
            digitalWrite(GALIL_INC, HIGH);
            delayMicroseconds(10);
            
          } else {
            digitalWrite(GALIL_DEC, LOW);
            delayMicroseconds(10);
            digitalWrite(GALIL_DEC, HIGH);
            delayMicroseconds(10);
          }
          
        } else {
          Galil_SlowFlag = true;  // enable the GALIL slow motion
          Serial.println("Galil Slow Enabled");
        }
      }
    }  
    
    if (brmsTask & brmsRG1Mask) {
        
        /* Rate group 1 is run every 200us.  Equal to a 5KHz update rate. */
        if (GalilEnable) {
          chkGALILError();  // reset the GALIL input
        }
        
    } else if (brmsTask & brmsRG2Mask) {
        
        /* Rate group 2 is run every 400us, or 2.5KHz*/
        if ((recording && inmotion) || (recording_oversample_time > 0))
          SDAppendMotionGalil(APC, rawcurrent);
        
    } else if (brmsTask & brmsRG3Mask) {
        
        /* Rate group 3 is run every 800us, or 1.25KHz*/
        
    } else if (brmsTask & brmsRG4Mask) {
     
        /* Rate group 4 is run every 1.6ms, or 625Hz*/

    } else if (brmsTask & brmsRG5Mask) {
     
        /* Rate group 5 is run every 3.2ms, or 312Hz*/
        if (GalilEnable) {
          GALIL_Slow();
        }

    } else if (brmsTask & brmsRG6Mask) {
     
        /* Rate group 6 is run every 6.4ms, or 156Hz*/
        
        /* Query the Cypress device if it's configured and ready */
        if (CypressEnable) {
          CypressStatus();

          /* Infer that the Cypress is moving from the position error */
          if (CypressInmotion) {
            
            if (CypressPosition == CypressDestination) {
            
              CypressWriteFile = true;
              CypressInmotion = false;

              CypressEndTime = micros();
              ElapsedTime = CypressEndTime - CypressStartTime;
              Serial.printf("move to %d is complete in %0.1f us\n", CypressPosition, ElapsedTime);
              SDSetTimes(CypressStartTime, CypressEndTime);
            }
          } else {
            CypressInmotion = (CypressPosition != CypressDestination);
            CypressStartTime = micros();
          }

          if ((CypressRecording && CypressInmotion) || (recording_oversample_time > 0)) 
            SDAppendMotionCypress(CypressPosition, CypressCurrent);
            
        }
        
    }
  
}



void setup() {

  Serial.begin(115200);
  Serial.println("=========================================================");
  Serial.println(">>>    STARTING ACS GALIL/CYPRESS EVALUATION BOARD    <<<");

  // Setup the CLI
  SetupControls();


  pinMode(38, OUTPUT); // Timer2 status

  SPI1.begin();

  // init current sensors
  ina219g.begin();
  ina219g.setCalibration_32V_1A();
  ina219c.begin();
  ina219c.setCalibration_32V_1A();

  // Initialize the I2C port expander
  for (int i = 0; i < 8; i++) {
    pcf8574.pinMode(i, INPUT);
  }

  if (pcf8574.begin()) {
    Serial.println(">>> PCF8574 OK");
  } else {
    Serial.println(">>> PCH8574 NOT OK");
  }

  tft.begin();


  configmenu();  //setup the control menus

  // Initialize the GALIL Interface
  pinMode(GALIL_ERRn, INPUT);
  pinMode(GALIL_RST, OUTPUT);
  pinMode(GALIL_CLK, OUTPUT);
  pinMode(GALIL_DEC, OUTPUT);
  pinMode(GALIL_INC, OUTPUT);
  pinMode(GALIL_IDX, INPUT);
  pinMode(GALIL_HOM, INPUT);
  pinMode(GALIL_B, INPUT);
  pinMode(GALIL_A, INPUT);


  // Initial Pin Level
  digitalWrite(GALIL_DEC, LOW);
  digitalWrite(GALIL_INC, LOW);

  //Initialize the GALIL clock = 4MHz
  pinMode(GALIL_CLK, OUTPUT);
  analogWriteFrequency(GALIL_CLK, 4000000);
  analogWriteResolution(5);
  analogWrite(GALIL_CLK, 15);
  smartDelay(100);

  // Reset the GALIL device
  digitalWrite(GALIL_RST, HIGH);
  smartDelay(100);
  digitalWrite(GALIL_RST, LOW);
  smartDelay(100);
  digitalWrite(GALIL_RST, HIGH);

  // Setup Cypress I/O
  //pinMode(TFT_MISO, INPUT);
  //pinMode(TFT_MOSI, OUTPUT);
  //pinMode(TFT_CLK, OUTPUT);

  pinMode(Cypress_RSTn, OUTPUT);
  digitalWrite(Cypress_RSTn, HIGH);
  smartDelay(100);
  pinMode(Cypress_RSTn, OUTPUT);
  digitalWrite(Cypress_RSTn, LOW);
  smartDelay(100);
  pinMode(Cypress_RSTn, OUTPUT);
  digitalWrite(Cypress_RSTn, HIGH);

  smartDelay(100);
  pinMode(CypressCSPin, OUTPUT);
  digitalWrite(CypressCSPin, HIGH);
  pinMode(TFT_MISO, INPUT);

  smartDelay(100);
  pinMode(PWM_DISABLE_MOT0, OUTPUT);
  digitalWrite(PWM_DISABLE_MOT0, LOW);

  // initialize the pushbutton pin as an input:
  pinMode(buttonUpPin, INPUT);
  pinMode(buttonSelectPin, INPUT);
  pinMode(buttonDownPin, INPUT);

  // init rotary encoder pins
  pinMode(encoder0PinA, INPUT_PULLUP);
  pinMode(encoder0PinB, INPUT_PULLUP);
  pinMode(encoder0Btn, INPUT_PULLUP);

  pinMode(Cypress_IDX, INPUT);
  pinMode(Cypress_HOM, INPUT);
  attachInterrupt(encoder0PinA, doEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(GALIL_HOM), doGalilHome, LOW);
  attachInterrupt(digitalPinToInterrupt(GALIL_IDX), doGalilIndex, LOW);
  attachInterrupt(digitalPinToInterrupt(GALIL_A), doStrutEncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(GALIL_B), doStrutEncoderB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(GALIL_ERRn), doGALILError, LOW);
  //attachInterrupt(digitalPinToInterrupt(Cypress_HOM), docpHome, LOW);
  //attachInterrupt(digitalPinToInterrupt(Cypress_IDX), docpIndex, HIGH);

  pinMode(backlight_EN, OUTPUT);
  digitalWrite(backlight_EN, HIGH);

  FastLED.addLeds<WS2812B, 6, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);

  // read diagnostics (optional but can help debug problems)

  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print(">>> Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print(">>> MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print(">>> Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print(">>> Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print(">>> Self Diagnostic: 0x"); Serial.println(x, HEX);

  tft.setRotation(2); //was 3
  tft.fillScreen(ILI9341_BLACK);


  Serial.println(">>> initializing Cypress");
  CypressInit();  
  CypressStatus();
  
  DrawMenus(pagenum);
  Galil_SlowFlag = false;
  galil_err = false;
  inmotion = false;
  write_file = false;
  myTimer.begin(HighFrequency, 100); // start the BRMS at 10KHz

  Serial.println(">>> SETUP COMPLETE                                    <<<");
  Serial.println("=========================================================");
  Serial.println("");
  Serial.println("---------------------------------------------------------");
  Serial.println("KECK ACS CONTROLS - TYPE 'help' FOR COMMANDLINE FUNCTIONS");
  Serial.println("---------------------------------------------------------");
}

int btn;
int lcnt = 0;
char SW_STATE;
int r_sw = 0;

void loop(void) {

  static uint32_t last_current_time = 0;
  static uint32_t last_cypress_time = 0;
  item_changed = 0;
  static bool do_once = false;

  /* Hey kids, what time is it? */
  time_now = millis();

  /* Get the latest current reading, every 10ms */
  if (time_now > last_current_time + 10) {
    rawcurrent = ina219g.getCurrent_raw();
    last_current_time = time_now;
  }

  /* Check rotary switches for changes */
  checkRotary();

  if (valRotary > lastValRotary)
  {
    //Serial.printf("mode %d", mode);
    if (mode == 1 || mode == 2) {
      if (menuitem == RECORD) {
        recording = true;
        mymenu[1].m[RECORD].mvalue.mval.b = recording;
      } else {
        mymenu[pagenum].m[menuitem].mvalue.mval.b = valRotary;
      }
      DrawMenus(pagenum);
    }
  }
  if (valRotary < lastValRotary)  {

    if (mode == 1 || mode == 2) {
      if (menuitem == RECORD) {
        recording = false;
        mymenu[1].m[RECORD].mvalue.mval.b = recording;
      } else {
        mymenu[pagenum].m[menuitem].mvalue.mval.b = valRotary;
      }
      DrawMenus(pagenum);
    }
  }
  lastValRotary = valRotary;



  //myerror = readGALILError(); // get the error value from the GALIL device
  //mymenu[GALIL].m[ERR].mvalue.mval.b = myerror; // update the error

  //if((abs)(myerror)>0)
  // DrawMenus(pagenum);


  /* Get the Cypress status and periodically update the user */

  /* Update the screen with the latest Cypress, every 100ms */
  if (time_now >= last_cypress_time + 100) {

    if ((LastCypressPosition != CypressPosition) || (!do_once)) {
      Serial.printf("Cypress state: %d, dest: %d, position: %d, current: %d\n", CypressState, CypressDestination, CypressPosition, CypressCurrent);
      LastCypressPosition = CypressPosition;      
    }
    

    do_once = true;
    last_cypress_time = time_now;      
  }

  if (CypressReinit) {
    Serial.println(">>> Re-initializing Cypress");
    CypressInit();  
    CypressReinit = false;
  }


  /* Process the CLI once motion is done and sampling is complete */
  if ((recording_oversample_time == 0) && (!inmotion)) {
    serial_commands_.ReadSerial();
    CheckMenu();
    delay(10);
  }

  /* Write the file out to disk when prompted */
  if ((recording || CypressRecording) && (write_file || CypressWriteFile)) {

    /* Wait for oversample time to expire */
    if (time_now > recording_oversample_time) {
      
      recording = false;
      CypressRecording = false;
      write_file = false;
      CypressWriteFile = false;
      recording_oversample_time = 0;      

      Serial.printf(">>> Writing capture to disk, %d data points at %d ms\n", sample_index, time_now);
      SDWriteMotion();
      DrawMenus(pagenum);
      
    }
    
  } else if (write_file || CypressWriteFile) {
      /* Not recording, but file write triggered, so just reset */
      recording = false;
      CypressRecording = false;
      write_file = false;
      CypressWriteFile = false;
      recording_oversample_time = 0;      

      Serial.printf(">>> Move complete at %d ms\n", time_now);
  }
  

  toggleLED();
  if (pagenum == 0 && menuitem == 0) // set the mode if on the first page
    mode = 1;
  if (pagenum == 0 && menuitem == 1) // set the mode if on the first page
    mode = 2;
  if (pagenum == 0 && menuitem == 2) {
    DrawMenus(3);
    smartDelay(1000);
  }

  lcnt++; // loop counter
}






#pragma message "---------- BUILDING MAIN SKETCH - DONE ----------"
