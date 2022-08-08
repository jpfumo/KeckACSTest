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

#include "KeckACS.h"




#pragma message "---------- BUILDING MAIN SKETCH ----------"

CRGB leds[1];

// Set i2c address
PCF8574 pcf8574(0x38); //pcf8574A addr = 0x70

Adafruit_INA219 ina219g(0x44);
Adafruit_INA219 ina219c(0x40);

int ptype;
int mtype;
int itype;

enum ptype {TOP, GALIL, CYPRESS, CYPREPLY};
enum mtype {HOME, STEPS, TOTAL, MAX, CLEAR, CYCLES, ELAPSED, ERR, APCREG , RECORD, MGO, MEXIT};
enum itype {label = -1, funcall, selectable, editable, noneditable, myexit};

// label, static label, does nothing
// funcall, goto this function &function_name
// selectable, Goto to this menu
// editable, Can change the value of this item, used to create an input value
// noneditable, cannot change the value, used to display a value
// myexit, indicates the menu exit point (pagenum =0, itemnum = 0)






float kp, ki, kd;

long steps=0;
int direction = 0;
long TimeIn, TimeOut;

boolean inmotion = false;

int encoder0Pos = 0;
int valRotary,lastValRotary;

int bufptr = 0;
int blockcnt = 0;
int delayval = 500; // delay for half a second
int ledToggle = 0;

File file;

// Date and time related
unsigned long time_now = 0;
String dataMessage;
unsigned char datamsg[640];

// Define CS pin for the SD card module
const int chipSelect = BUILTIN_SDCARD;  // teensy4.1 internal SD slot!!!e


#define BUFF_SIZE 65536

union {
  uint32_t lwords[BUFF_SIZE];
  uint16_t words[BUFF_SIZE*2];
  unsigned char chars[BUFF_SIZE*4];
}i2s_buff;

bool Data_Enable = false;
bool Galil_SlowFlag = false;
unsigned int GainAmp = 1;
long ElapsedTime = 0;
int sequence = 0;

short Start = 1;
short menu = 19;
short sample = 0;       // index for double buffer
uint8_t rotation = 0;
int buttonState = 0;
volatile bool RotaryFlag = false;

int TimeBetweenSamples = 1;  //seconds
int firsttime = 0;
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

#define filetag "/ACS"
static int filenum = 0;
static char filename[15];
static char filelabel[15];
static int filestatus = 0;

IntervalTimer myTimer;

typedef struct mv{
  union {
   int8_t b;
   int16_t w;
   int32_t l;
   float f;
  } mval;
}myi;


// Encapsulate each menu item
typedef struct Menuitem{
  char menuname[40];  // Menu name
  int itemtype; // -1 = label, 0 = function call, 1 = selectable, 2 = editable, 3 = Exit
  int edittype; // 0 = bool, 1 = int, 2 = unsigned nit, 3 = ON/OFF, 4 = FWD/REV
  int itemmin;  // min value
  int itemmax;  // max value
  myi mvalue;   // value
  int vsize;    // size of value 0 = b, 1 = w, 2 = l, 3 = f
  int level;    // what level
  int encodergain;    // what level
  
  int (*myfunc)(int); // function called on select
} myitem;


// define menu structures
struct menu{
  char title[40]; // title of page
  int numitems; // number of items
  myitem m[16]; // total number of items per menu page
} mymenu[6];  // six menus total


volatile   int A, B, C;


// SPI interrupt routine
void SPI_INT(void){
  uint8_t c = 0;
  c = SPDR;
  Serial.printf("%d ",c);
}

// disable the GALIL for input --- if error too high
volatile bool galil_err;
void doGALILError()
{
    int err;
    err = digitalRead(GALIL_ERRn);
    if(err == 0){ 
      detachInterrupt(digitalPinToInterrupt(GALIL_ERRn));
      galil_err = true;
    }
}

// re-enables the GALIL for input
void chkGALILError()
{   
  int err;
  err = digitalRead(GALIL_ERRn);
  if(err == 1){ 
    attachInterrupt(digitalPinToInterrupt(GALIL_ERRn), doGALILError, LOW); 
    galil_err = false;
  }
}

void doEncoder()
{
  A = digitalRead(encoder0PinA);
  B = digitalRead(encoder0PinB);
  Serial.printf("rotary: a = %d, b = %d", A, B);
  RotaryFlag = true;  
}

volatile   int sA, sB, sC;
void doStrutEncoderA()
{
  int r_sw = 0;
  sA = digitalRead(GALIL_A);
  sB = digitalRead(GALIL_B);

  if(sA==0 && sB==0)
      r_sw = 0;
  else if (sA==1 && sB==0)
      r_sw = 1;
  else if (sA==0 && sB==1)
      r_sw = 2;    
  else if (sA==1 && sB==1)
      r_sw = 3; 

           
  if(r_sw == 1||r_sw == 2){
    //CW;
    APC--;
    //Serial.println("CW");
  } else if (r_sw == 0||r_sw == 3){
    //CCW
    APC++;
    //Serial.println("CCW");
  }  
  mymenu[GALIL].m[APCREG].mvalue.mval.l = APC;
  //Serial.printf("a=%d, b=%d, r_sw= %d, APC= %d", sA, sB, r_sw, APC);
  //Serial.println("");
  //DrawMenus(pagenum);
}

void doStrutEncoderB()
{
  int r_sw = 0;
  sA = digitalRead(GALIL_A);
  sB = digitalRead(GALIL_B);

  if(sA==0 && sB==0)
      r_sw = 0;
  else if (sA==1 && sB==0)
      r_sw = 1;
  else if (sA==0 && sB==1)
      r_sw = 2;    
  else if (sA==1 && sB==1)
      r_sw = 3; 

           
  if(r_sw == 1||r_sw == 2){
    //CW;
    APC++;
    //Serial.println("CCW");
  } else if (r_sw == 0||r_sw == 3){
    //CCW
    APC--;
    //Serial.println("CW");
  }  
  mymenu[GALIL].m[APCREG].mvalue.mval.l = APC;

  //Serial.printf("a=%d, b=%d, r_sw= %d, APC= %d", sA, sB, r_sw, APC);
  //Serial.println("");
  //DrawMenus(pagenum);
}


volatile bool foundHome = false;
void doHome()
{
  foundHome = true;
  Serial.println("HIT Home");
  detachInterrupt(digitalPinToInterrupt(GALIL_HOM));
}

volatile bool foundIndex = false;
void doIndex()
{
  foundIndex = true;
  Serial.println("HIT Index");
  detachInterrupt(digitalPinToInterrupt(GALIL_IDX));
}

volatile bool foundcpIndex = false;
void docpIndex()
{
  foundcpIndex = true;
  Serial.println("HIT Cypress Index");
  detachInterrupt(digitalPinToInterrupt(Cypress_IDX));
}

volatile bool foundcpHome = false;
void docpHome()
{
  foundcpHome = true;
  Serial.println("HIT Cypress Home");
  detachInterrupt(digitalPinToInterrupt(Cypress_HOM));
}

void WriteCurrentData(char * path)
{
  
  file = SD.open(path, FILE_WRITE);
  if(!file) {
    Serial.println("Failed to open file for appending");
    return;
  }

  file.write(i2s_buff.chars, bufptr*2);
  file.close();
  //delay(1);
}



// Write to the SD card (DON'T MODIFY THIS FUNCTION)
//void writeFile(fs::FS &fs, const char * path, const char * message) {
void writeFile(const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);

  file = SD.open(path, FILE_WRITE);
  if(!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

// Append data to the SD card (DON'T MODIFY THIS FUNCTION)
//void appendFile(fs::FS &fs, const char * path, const char * message) {
void appendFile(const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);

  file = SD.open(path, FILE_WRITE);
  if(!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if(file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}

// Append data to the SD card (DON'T MODIFY THIS FUNCTION)
//void recordFile(fs::FS &fs, const char * path) {
void recordFile(const char * path) {
  
  file = SD.open(path, FILE_WRITE);
  if(!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
      
  dataMessage.getBytes(datamsg, dataMessage.length());
  file.write(datamsg, dataMessage.length());

  file.close();
  //delay(1);
}





void DrawMenus(int level){ // level = menu number
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
  tft.drawRect(0,0,WIDTH, HEIGHT-1, TFT_GREEN);
  tft.setCursor(10, 5);

  tft.setTextColor(TFT_ORANGE,TFT_BLACK);
  strcpy(Teststr,mymenu[level].title);
  
  Serial.printf("%d, %s", level, Teststr); 
  Serial.println("");
  
  tft.printf("%s", Teststr);
  tft.println("");

  if(level==GALIL){ // update values
    if(abs(mymenu[GALIL].m[CYCLES].mvalue.mval.l) >= 1)
      mymenu[GALIL].m[TOTAL].mvalue.mval.l = mymenu[GALIL].m[STEPS].mvalue.mval.l * (int)mymenu[GALIL].m[CYCLES].mvalue.mval.b;
    else
      mymenu[GALIL].m[TOTAL].mvalue.mval.l = mymenu[GALIL].m[STEPS].mvalue.mval.l;

    myerror = readGALILError();
    mymenu[GALIL].m[ERR].mvalue.mval.b = myerror;
    Serial.printf("Count: %d,TOTAL %d", (int)mymenu[GALIL].m[CYCLES].mvalue.mval.b, (int)mymenu[GALIL].m[TOTAL].mvalue.mval.l); 
    Serial.println("");
  }

  if(level==CYPRESS){ // update values

    if(abs(mymenu[CYPRESS].m[CYCLES].mvalue.mval.l) >= 1)
      mymenu[CYPRESS].m[TOTAL].mvalue.mval.l = (int)mymenu[CYPRESS].m[STEPS].mvalue.mval.l * (int)mymenu[CYPRESS].m[CYCLES].mvalue.mval.b;
    else
      mymenu[CYPRESS].m[TOTAL].mvalue.mval.l = (int)mymenu[CYPRESS].m[STEPS].mvalue.mval.b;
      
    Serial.printf("Count: %d,TOTAL %d", (int)mymenu[CYPRESS].m[CYCLES].mvalue.mval.b, (int)mymenu[CYPRESS].m[TOTAL].mvalue.mval.l); 
    Serial.println("");

  }
  

  index = 1;
  for(i=0; i<mymenu[level].numitems; i++)
  {
    tft.setCursor(Xoffset, Yoffset + Yincrement*index);
    if(i==menuitem){
        if(processmenuitem == true)
          tft.setTextColor(TFT_ORANGE,TFT_BLACK); 
        else
          tft.setTextColor(TFT_GREEN,TFT_BLACK);
        if(mymenu[level].m[i].itemtype == editable || mymenu[level].m[i].itemtype == noneditable ){
          if(mymenu[level].m[i].vsize == 3){
            tft.printf("%s: %d",mymenu[level].m[i].menuname, (int)mymenu[level].m[i].mvalue.mval.l); 
            tft.println("");   
            //GALIL_MTRPUL =  mymenu[1].m[1].mvalue.mval.l * mymenu[1].m[6].mvalue.mval.l;
            //mymenu[1].m[TOTAL].mvalue.mval.l = GALIL_MTRPUL;
          }else{
            tft.printf("%s: %d",mymenu[level].m[i].menuname, (int)(mymenu[level].m[i].mvalue.mval.b)); 
            tft.println("");   
            //GALIL_MTRPUL =  mymenu[1].m[1].mvalue.mval.b * mymenu[1].m[6].mvalue.mval.b;
            //mymenu[1].m[TOTAL].mvalue.mval.b = GALIL_MTRPUL;            
          }

          
        }else{
          tft.printf("%s",mymenu[level].m[i].menuname);  
          tft.println("");   
        }
    }else{
      tft.setTextColor(TFT_LIGHTGREY,TFT_BLACK); 
        if(mymenu[level].m[i].itemtype == editable || mymenu[level].m[i].itemtype == noneditable ){
          if((level==GALIL || level==CYPRESS) && i==ELAPSED){
            etime = (float)(mymenu[level].m[ELAPSED].mvalue.mval.l * 0.000001);
            tft.printf("%s: %f",mymenu[level].m[i].menuname, etime);
          }else if (level==CYPREPLY && i==9){
            tft.printf("%s: %08d",mymenu[level].m[i].menuname, mymenu[level].m[i].mvalue.mval.l);
          }else{
            if(mymenu[level].m[i].vsize == 3){
              tft.printf("%s: %d",mymenu[level].m[i].menuname, mymenu[level].m[i].mvalue.mval.l); 
              tft.println(""); 
            }else{
              tft.printf("%s: %d",mymenu[level].m[i].menuname, mymenu[level].m[i].mvalue.mval.b); 
              tft.println("");               
            }
          }  

        }else{
          tft.printf("%s",mymenu[level].m[i].menuname);  
          tft.println("");
        }      
    }  

    index++; 
    Serial.printf("i: %d, mval: %d",i, mymenu[level].m[i].mvalue.mval.l);
    Serial.println("");
    tft.updateScreen(); 
  }


//  if(level==CYPRESS){
//    FillinCypressResponse(level);
//    CypressStatus();
//  }


}









uint16_t posData = 0;
int j=0;
int item_changed = 1; // draw it the first time

void CheckMenu(){
  int ncount = 0;

  if (!(buttonState = digitalRead(buttonSelectPin)))
    {
      Serial.println("ButtonSelect");
      menu = true;
      //Serial.printf("%d,", menuitem);
      //Serial.println("Menu Select");
      if(mymenu[pagenum].m[menuitem].itemtype == funcall){  // go to function
        if( mymenu[pagenum].m[menuitem].myfunc(0) == NULL)
          ncount++;
        else
          mymenu[pagenum].m[menuitem].myfunc(3);
      } else if(mymenu[pagenum].m[menuitem].itemtype == selectable){ // go to next menu
          pagenum = menuitem+1;
      } else if (mymenu[pagenum].m[menuitem].itemtype == myexit){ //exit
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
    if(menuitem<0)
      menuitem = mymenu[pagenum].numitems-1;  // point at the top of the list
    Serial.printf("%d,", menuitem);
    Serial.println("menuitem");
    delay(100);
    while(!(buttonState = digitalRead(buttonUpPin)));
    item_changed = 1;
    lastValRotary = 0;
    valRotary = 0;;
    tft.fillScreen(TFT_BLACK);
    //DrawMenus(pagenum);
  }
  else if (!(buttonState = digitalRead(buttonDownPin)))
  {
    Serial.println("buttonDownPin");
    menuitem++;
    if(menuitem>mymenu[pagenum].numitems-1) // point at the bottom of the list
      menuitem = 0;
    Serial.printf("%d,", menuitem);
    Serial.println("menuitem");
    delay(100);
    while(!(buttonState = digitalRead(buttonUpPin)));
    item_changed = 1;
    lastValRotary = 0;
    valRotary = 0;;
    tft.fillScreen(TFT_BLACK);
    //DrawMenus(pagenum);
  }
  if(item_changed==1){ // from interrupt Button B
      Serial.printf("%d,", menuitem);
      Serial.println("Menu Select");
      //menuitem = 0;
      DrawMenus(pagenum);
      //CheckSW();
      item_changed = 0;
  }
}



void CheckSW()
{
  while(menu==true){
    //M5.update();
    if (!(buttonState = digitalRead(buttonDownPin)))
    {
      if(menuitem<mymenu[pagenum].numitems)
        menuitem++;
      Serial.printf("%d,", menuitem);
      Serial.println("Btn A");
      DrawMenus(pagenum);      
      if (menuitem==mymenu[pagenum].numitems+1){
        menu = false;
        firsttime = 1;  // reset the Flow Meter Page, rev 0.1.2
        tft.fillScreen(TFT_BLACK);
      }

      delay(100);
      while(!(buttonState = digitalRead(buttonDownPin)));      
    }
    else if (!(buttonState = digitalRead(buttonSelectPin)))
    {
      Serial.printf("%d,", menuitem);
      Serial.println("Btn B");
      processmenuitem = true;
      DrawMenus(pagenum);
      //ProcessMenus(pagenum);
      delay(100);
      while(!(buttonState = digitalRead(buttonSelectPin)));

    } else if (!(buttonState = digitalRead(buttonUpPin))){
      if(menuitem>0)
        menuitem--;
      Serial.printf("%d,", menuitem);
      Serial.println("Btn C");
      DrawMenus(pagenum);
      delay(100);
      while(!(buttonState = digitalRead(buttonUpPin)));
    }
  }
}


void bumpFilename(void){
  filenum++;
  sprintf(filelabel,"%04d",filenum);
  strcpy(filename, filetag);
  strcat(filename, filelabel);
  strcat(filename,".txt");
}



void toggleLED(void){
  if(ledToggle>1){
    leds[0] = CRGB(50,0,0);
    FastLED.show();
  }else{
    leds[0] = CRGB(0,50,50);
    FastLED.show();
  }
  if(ledToggle>=2)
    ledToggle = 0;
  else
    ledToggle++;
}


void configmenu(void){

  char Teststr[40];
  // TOP LEVEL
  strcpy(mymenu[0].title,"KECK ACS CONTROLS");
  strcpy(Teststr,mymenu[0].title);
  Serial.printf("%s",Teststr); 
  Serial.println("");
  mymenu[0].numitems = 6;
  strcpy(mymenu[0].m[0].menuname, "GALIL CONTROLS");
  mymenu[0].m[0].itemtype = selectable;
  mymenu[0].m[0].level = 0;
  mymenu[0].m[0].myfunc = 0;
  
  strcpy(mymenu[0].m[1].menuname, "CYPRESS CONTROLS");
  mymenu[0].m[1].itemtype = selectable;
  mymenu[0].m[1].level = 0;
  mymenu[0].m[1].myfunc = NULL; 
  
  strcpy(mymenu[0].m[2].menuname, "CYPRESS STATUS");
  mymenu[0].m[2].itemtype = label;
  mymenu[0].m[2].level = 0;
  mymenu[0].m[2].myfunc = NULL;
  
  strcpy(mymenu[0].m[3].menuname, "CHANGE SSD");
  mymenu[0].m[3].itemtype = funcall;
  mymenu[0].m[3].level = 0;
  mymenu[0].m[3].myfunc = &ChangeSSD; 
  
  strcpy(mymenu[0].m[4].menuname, "GALIL PARAMS");
  mymenu[0].m[4].itemtype = label;
  mymenu[0].m[4].level = 0;
  mymenu[0].m[4].myfunc = (int (*)(int)) -1;   
  
  strcpy(mymenu[0].m[5].menuname, "CYPRESS RESPONSE");
  mymenu[0].m[5].itemtype = selectable;
  mymenu[0].m[5].level = 0;
  mymenu[0].m[5].myfunc = (int (*)(int)) -1;  


  
  strcpy(mymenu[GALIL].title, "GALIL CONTROLS");
  mymenu[GALIL].numitems = 12;
  
  strcpy(mymenu[GALIL].m[HOME].menuname, "HOME");
  mymenu[GALIL].m[HOME].itemtype = funcall;
  mymenu[GALIL].m[HOME].level = 0;
  mymenu[GALIL].m[HOME].myfunc = &GALILHome;
  
  strcpy(mymenu[GALIL].m[STEPS].menuname, "STEPS");
  mymenu[GALIL].m[STEPS].encodergain = 10;
  mymenu[GALIL].m[STEPS].itemtype = editable;
  mymenu[GALIL].m[STEPS].level = 0;
  mymenu[GALIL].m[STEPS].myfunc = NULL;
  mymenu[GALIL].m[STEPS].vsize = 3;
  
  strcpy(mymenu[GALIL].m[TOTAL].menuname, "TOTAL");
  mymenu[GALIL].m[TOTAL].itemtype = noneditable;
  mymenu[GALIL].m[TOTAL].level = 0;
  mymenu[GALIL].m[TOTAL].vsize = 3;
  mymenu[GALIL].m[TOTAL].myfunc = NULL;
  
  strcpy(mymenu[GALIL].m[MAX].menuname, "MAX MOVE");
  mymenu[GALIL].m[MAX].itemtype = funcall;
  mymenu[GALIL].m[MAX].level = (int) NULL;
  mymenu[GALIL].m[MAX].myfunc = &GALILMax;  
  
  strcpy(mymenu[GALIL].m[CLEAR].menuname, "CLEAR STEPS");
  mymenu[GALIL].m[CLEAR].itemtype = funcall;
  mymenu[GALIL].m[CLEAR].level = (int) NULL;
  mymenu[GALIL].m[CLEAR].myfunc = &GALILClear;   
  
  strcpy(mymenu[GALIL].m[CYCLES].menuname, "CYCLES");
  mymenu[GALIL].m[CYCLES].encodergain = 1;
  mymenu[GALIL].m[CYCLES].itemtype = editable;
  mymenu[GALIL].m[CYCLES].level = 0;
  mymenu[GALIL].m[CYCLES].mvalue.mval.w = 1;
  mymenu[GALIL].m[CYCLES].myfunc = NULL;
  mymenu[GALIL].m[CYCLES].vsize = 1;
  
  strcpy(mymenu[GALIL].m[ELAPSED].menuname, "ETIME");
  mymenu[GALIL].m[ELAPSED].itemtype = noneditable;
  mymenu[GALIL].m[ELAPSED].level = 0;
  mymenu[GALIL].m[ELAPSED].myfunc = 0;
  
  strcpy(mymenu[GALIL].m[ERR].menuname, "ERROR");
  mymenu[GALIL].m[ERR].itemtype = noneditable;
  mymenu[GALIL].m[ERR].level = 0;
  mymenu[GALIL].m[ERR].myfunc = NULL;
     
  strcpy(mymenu[GALIL].m[APCREG].menuname, "APC");
  mymenu[GALIL].m[APCREG].itemtype = noneditable;
  mymenu[GALIL].m[APCREG].level = 0;
  mymenu[GALIL].m[APCREG].myfunc = NULL;
  mymenu[GALIL].m[APCREG].vsize = 3;
  
  strcpy(mymenu[GALIL].m[RECORD].menuname, "RECORD");
  mymenu[GALIL].m[RECORD].itemtype = editable;
  mymenu[GALIL].m[RECORD].level = 0;
  mymenu[GALIL].m[RECORD].myfunc = NULL; 
  
  strcpy(mymenu[GALIL].m[MGO].menuname, "GO");
  mymenu[GALIL].m[MGO].itemtype = funcall;
  mymenu[GALIL].m[MGO].level = 0;
  mymenu[GALIL].m[MGO].myfunc = &GALILGo; 

  strcpy(mymenu[GALIL].m[MEXIT].menuname, "EXIT");
  mymenu[GALIL].m[MEXIT].itemtype = myexit;
  mymenu[GALIL].m[MEXIT].level = 0;
  mymenu[GALIL].m[MEXIT].myfunc = 0; 



  strcpy(mymenu[CYPRESS].title, "CYPRESS CONTROLS");
  mymenu[CYPRESS].numitems = 12;
  
  strcpy(mymenu[CYPRESS].m[HOME].menuname, "HOME");
  mymenu[CYPRESS].m[HOME].itemtype = funcall;
  mymenu[CYPRESS].m[HOME].level = 0;
  mymenu[CYPRESS].m[HOME].myfunc = &CypressHome;
   
  strcpy(mymenu[CYPRESS].m[STEPS].menuname, "STEPS");
  mymenu[CYPRESS].m[STEPS].encodergain = 10;
  mymenu[CYPRESS].m[STEPS].itemtype = editable;
  mymenu[CYPRESS].m[STEPS].level = 0;
  mymenu[CYPRESS].m[STEPS].myfunc = NULL; //&drawTopPage;
  
  strcpy(mymenu[CYPRESS].m[TOTAL].menuname, "TOTAL");
  mymenu[CYPRESS].m[TOTAL].itemtype = noneditable;
  mymenu[CYPRESS].m[TOTAL].level = 0;
  mymenu[CYPRESS].m[TOTAL].myfunc = NULL;
  mymenu[CYPRESS].m[TOTAL].vsize = 3;
  
  strcpy(mymenu[CYPRESS].m[MAX].menuname, "MAX MOVE");
  mymenu[CYPRESS].m[MAX].itemtype = funcall;
  mymenu[CYPRESS].m[MAX].level = 0;
  mymenu[CYPRESS].m[MAX].myfunc = &CypressMax;
    
  strcpy(mymenu[CYPRESS].m[CLEAR].menuname, "CLEAR STEPS");
  mymenu[CYPRESS].m[CLEAR].itemtype = funcall;
  mymenu[CYPRESS].m[CLEAR].level = 0;
  mymenu[CYPRESS].m[CLEAR].myfunc = &CypressClear; 
  
  strcpy(mymenu[CYPRESS].m[CYCLES].menuname, "CYCLES");
  mymenu[CYPRESS].m[CYCLES].encodergain = 1;
  mymenu[CYPRESS].m[CYCLES].itemtype = editable;
  mymenu[CYPRESS].m[CYCLES].level = 0;
  mymenu[CYPRESS].m[CYCLES].mvalue.mval.w = 1;
  mymenu[CYPRESS].m[CYCLES].myfunc = NULL;
  mymenu[CYPRESS].m[CYCLES].vsize = 1;
      
  strcpy(mymenu[CYPRESS].m[ELAPSED].menuname, "ELAPSED");
  mymenu[CYPRESS].m[ELAPSED].itemtype = noneditable;
  mymenu[CYPRESS].m[ELAPSED].level = 0;
  mymenu[CYPRESS].m[ELAPSED].myfunc = NULL;
  
  strcpy(mymenu[CYPRESS].m[ERR].menuname, "ERROR");
  mymenu[CYPRESS].m[ERR].itemtype = noneditable;
  mymenu[CYPRESS].m[ERR].level = 0;
  mymenu[CYPRESS].m[ERR].myfunc = NULL;
  
  strcpy(mymenu[CYPRESS].m[APCREG].menuname, "APC");
  mymenu[CYPRESS].m[APCREG].itemtype = noneditable;
  mymenu[CYPRESS].m[APCREG].level = 0;
  mymenu[CYPRESS].m[APCREG].vsize = 3;
  mymenu[CYPRESS].m[APCREG].myfunc = NULL;   

  strcpy(mymenu[CYPRESS].m[RECORD].menuname, "RECORD");
  mymenu[CYPRESS].m[RECORD].itemtype = noneditable;
  mymenu[CYPRESS].m[RECORD].level = 0;
  mymenu[CYPRESS].m[RECORD].myfunc = NULL;   
  
  strcpy(mymenu[CYPRESS].m[MGO].menuname, "GO");
  mymenu[CYPRESS].m[MGO].itemtype = funcall;
  mymenu[CYPRESS].m[MGO].level = 0;
  mymenu[CYPRESS].m[MGO].myfunc = &CypressGo; 
  
  strcpy(mymenu[CYPRESS].m[MEXIT].menuname, "EXIT");
  mymenu[CYPRESS].m[MEXIT].itemtype = myexit;
  mymenu[CYPRESS].m[MEXIT].level = 0;
  mymenu[CYPRESS].m[MEXIT].myfunc = NULL; 




  strcpy(mymenu[3].title, "CYPRESS RESPONSE");
  mymenu[3].numitems = 12;
  
  strcpy(mymenu[3].m[0].menuname, "CHECKSUM");
  mymenu[3].m[0].itemtype = noneditable;
  mymenu[3].m[0].level = 0;
  mymenu[3].m[0].myfunc = NULL; 
  
  strcpy(mymenu[3].m[1].menuname, "VERSION");
  mymenu[3].m[1].encodergain = 10;
  mymenu[3].m[1].itemtype = noneditable;
  mymenu[3].m[1].level = 0;
  mymenu[3].m[1].myfunc = NULL; 
  
  strcpy(mymenu[3].m[2].menuname, "MSG SIZE");
  mymenu[3].m[2].itemtype = noneditable;
  mymenu[3].m[2].level = 0;
  mymenu[3].m[2].myfunc = NULL;
  
  strcpy(mymenu[3].m[3].menuname, "OPCODE");
  mymenu[3].m[3].itemtype = noneditable;
  mymenu[3].m[3].level = 0;
  mymenu[3].m[3].myfunc = NULL; 
   
  strcpy(mymenu[3].m[4].menuname, "STATE");
  mymenu[3].m[4].itemtype = noneditable;
  mymenu[3].m[4].level = 0;
  mymenu[3].m[4].myfunc = NULL;
   
  strcpy(mymenu[3].m[5].menuname, "FAULT");
  mymenu[3].m[5].encodergain = 1;
  mymenu[3].m[5].itemtype = editable;
  mymenu[3].m[5].level = 0;
  mymenu[3].m[5].myfunc = NULL; 
     
  strcpy(mymenu[3].m[6].menuname, "SEQUENCE");
  mymenu[3].m[6].itemtype = noneditable;
  mymenu[3].m[6].level = 0;
  mymenu[3].m[6].myfunc = NULL;
  
  strcpy(mymenu[3].m[7].menuname, "NUM CHKSUM");
  mymenu[3].m[7].itemtype = noneditable;
  mymenu[3].m[7].level = 0;
  mymenu[3].m[7].myfunc = NULL;
  
  strcpy(mymenu[3].m[8].menuname, "CURRENT");
  mymenu[3].m[8].itemtype = noneditable;
  mymenu[3].m[8].level = 0;
  mymenu[3].m[8].myfunc = NULL; 
    
  strcpy(mymenu[3].m[9].menuname, "POSITION");
  mymenu[3].m[9].itemtype = noneditable;
  mymenu[3].m[9].level = 0;
  mymenu[3].m[9].myfunc = &CypressGo;
   
  strcpy(mymenu[3].m[10].menuname, "PWM");
  mymenu[3].m[10].itemtype = noneditable;
  mymenu[3].m[10].level = 0;
  mymenu[3].m[10].myfunc = NULL; 
  
  strcpy(mymenu[3].m[11].menuname, "EXIT");
  mymenu[3].m[11].itemtype = myexit;
  mymenu[3].m[11].level = 0;
  mymenu[3].m[11].myfunc = NULL; 
  
}

int ChangeSSD(int x){
  if (!SD.begin(chipSelect)) 
  {
    Serial.println("SD initialization failed!");
    filestatus = 1;
  }
  else
  {
    Serial.println("initialization done.");
    // If the data.txt file doesn't exist
    // Create a file on the SD card and write the data labels
    file = SD.open(filename);
    if(!file) {
      Serial.println("File doens't exist");
      Serial.println("Creating file...");
      //writeFile(filename, "current\r\n");
      filestatus = 1;
    }
    else {
      Serial.println("File already exists");  
      filestatus = 1;
    }
    file.close();
  }

  return 0;
}

void checkRotary(void){
  int r_sw = 0;
  
  if(RotaryFlag==true){
    //Serial.println("RotaryFlag==true");
    if(A==0 && B==0)
        r_sw = 0;
    else if (A==1 && B==0)
        r_sw = 1;
    else if (A==0 && B==1)
        r_sw = 2;    
    else if (A==1 && B==1)
        r_sw = 3;    
  
    if(r_sw == 1||r_sw == 2){
      //CW;
      valRotary++;
      //Serial.println("CW");
    } else if (r_sw == 0||r_sw == 3){
      //CCW
      valRotary--;
      //Serial.println("CCW");
    }
  }
  RotaryFlag=false;
}



int ledState = LOW;
volatile unsigned long blinkCount = 0;

void HighFrequency() { // High Frequency rate group = 5KHz

  sequence++;

  if(galil_err == false && inmotion == true && Galil_SlowFlag == false){
    if(nsteps>15){
      nsteps -= 1;
      if(direction==CW){
        digitalWrite(GALIL_INC, LOW);
        delayMicroseconds(10);
        digitalWrite(GALIL_INC, HIGH);
        delayMicroseconds(10);
      }else{
        digitalWrite(GALIL_DEC, LOW);
        delayMicroseconds(10);
        digitalWrite(GALIL_DEC, HIGH);
        delayMicroseconds(10);        
      }
    }
    else
    {
      Galil_SlowFlag = true;  // enable the GALIL slow motion
      Serial.println("Galil Slow Enabled");
    }
  }

  switch(sequence){ //Scheduled Rate Groups
    case 1://2500
    case 3:
    case 5:
    case 7:
    case 9:
    case 11:
    case 13:
    case 15:
      chkGALILError();  // reset the GALIL input
      //Serial.println("RG 1");
      break;
    case 2://1250
    case 6:
    case 10:
    case 14:
      //Serial.println("RG 2");
      break;
    case 4://625
    case 12:
      //Serial.println("RG 3");
      break;
    case 8://312.5
      //Serial.println("RG 4");
      break;
      
    case 16://156.25
      //Serial.println("CRG");
      GALIL_Slow();
      sequence = 0;
      break;
  }
}


void setup() {

  pinMode(38, OUTPUT); // Timer2 status
  
  Serial.begin(115200);
  Serial.println("KECK ACS CONTROLS"); 
  Serial7.begin(9600);

  SPI1.begin();
  
  // init current sensors
  ina219g.begin();
  ina219g.setCalibration_32V_1A();
  ina219c.begin();
  ina219c.setCalibration_32V_1A();

  // Initialize the I2C port expander
  for(int i=0;i<8;i++) {
    pcf8574.pinMode(i, INPUT);
  }

  if (pcf8574.begin()){
    Serial.println("OK");
  } else {
    Serial.println("KO");
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
  digitalWrite(CypressCSPin,HIGH);
  pinMode(TFT_MISO, INPUT);

  smartDelay(100); 
  pinMode(PWM_DISABLE_MOT0, OUTPUT);
  digitalWrite(PWM_DISABLE_MOT0,LOW);
  
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
  attachInterrupt(digitalPinToInterrupt(GALIL_HOM), doHome, LOW);
  attachInterrupt(digitalPinToInterrupt(GALIL_IDX), doIndex, LOW);
  attachInterrupt(digitalPinToInterrupt(GALIL_A), doStrutEncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(GALIL_B), doStrutEncoderB, CHANGE);  
  attachInterrupt(digitalPinToInterrupt(GALIL_ERRn), doGALILError, LOW); 
  //attachInterrupt(digitalPinToInterrupt(Cypress_HOM), docpHome, LOW);
  //attachInterrupt(digitalPinToInterrupt(Cypress_IDX), docpIndex, HIGH);

  pinMode(backlight_EN, OUTPUT);
  digitalWrite(backlight_EN, HIGH);

  FastLED.addLeds<WS2812B,6,GRB>(leds, NUM_LEDS); 
  FastLED.setBrightness(255);
  
  // read diagnostics (optional but can help debug problems)
  
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); 
  
  tft.setRotation(2); //was 3
  tft.fillScreen(ILI9341_BLACK);
  

  SD.begin(BUILTIN_SDCARD);
  sprintf(filelabel,"%04d",filenum);
  strcpy(filename, filetag);
  strcat(filename, filelabel);
  strcat(filename,".txt");

  if (!SD.begin(chipSelect)) 
  {
    Serial.println("SD initialization failed!");
    filestatus = 1;
  }
  else
  {
    Serial.println("initialization done.");
    // If the data.txt file doesn't exist
    // Create a file on the SD card and write the data labels
    file = SD.open(filename);
    if(!file) {
      Serial.println("File doens't exist");
      Serial.println("Creating file...");
      //writeFile(filename, "current\r\n");
      filestatus = 1;
    }
    else {
      Serial.println("File already exists");  
      filestatus = 1;
    }
    file.close();
  }
  //Serial.println("Init Cypress");
  //strcpy(oldfilename, filename);
  
  //checkSettings();
  //smartDelay(100);

  //pinMode(SS, INPUT_PULLUP);
  //pinMode(MOSI, OUTPUT);
  //pinMode(SCK, INPUT);
  //SPCR |= _BV(SPE);
  //SPI.attachInterrupt();

  // initialize the PID constants
  kp = 0.08;
  ki = 1.0;
  kd = 0.002;
  Serial.println("Init Cypress");
  CypressInit();
  CypressStatus();
  DrawMenus(pagenum);
  Galil_SlowFlag = false;
  galil_err = false;
  inmotion = false;
  write_file = false;
  sequence = 0;
  myTimer.begin(HighFrequency, 100); // start the BRMS at 5KHz
}

int btn;
int myerror;
int lcnt = 0;
char SW_STATE;
int r_sw = 0;
void loop(void) {

  //btn = digitalRead(encoder0Btn);
  //Serial.print(btn);
  //Serial.print(" ");
  //Serial.print(valRotary);
  item_changed=0;
  checkRotary();

  if(valRotary>lastValRotary)
  {
    Serial.print("line1");
    //Serial.printf("mode %d", mode);
    if(mode == 1 || mode == 2){
      if(menuitem==RECORD){
        recording = true;
        mymenu[1].m[RECORD].mvalue.mval.b = recording;
      }else{
        mymenu[pagenum].m[menuitem].mvalue.mval.b = valRotary;
      }
      DrawMenus(pagenum);
    }
  }
  if(valRotary<lastValRotary)  {
    Serial.print("line2");
    //Serial.printf("mode %d", mode);
    if(mode == 1 || mode == 2){
      if(menuitem==RECORD){
        recording = false;
        mymenu[1].m[RECORD].mvalue.mval.b = recording;
      }else{
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
    
  CheckMenu();

  delay(10);

  if(recording==true  && inmotion == true){

    rawcurrent = ina219g.getCurrent_raw();
    i2s_buff.words[bufptr++] = rawcurrent;
    i2s_buff.words[bufptr++] = APC; 
    Serial.printf("bufptr: %d, Current: %d", bufptr, rawcurrent);
    Serial.println(""); 
    if(bufptr>=65530)
      recording = false;
  }

  if(write_file){
    Serial.printf("Write File bufptr: %d", bufptr);
    Serial.println("Write to SD card");
    WriteCurrentData(filename);  // send the data to the diskdrive
    bumpFilename(); // create the next filename
    DrawMenus(pagenum);
    write_file = false;
  }

  toggleLED();
  if(pagenum==0 && menuitem == 0) // set the mode if on the first page
    mode = 1;
  if(pagenum==0 && menuitem == 1) // set the mode if on the first page
    mode = 2;
  if(pagenum==0 && menuitem == 2){
    CypressStatus();
    FillinCypressResponse();
    DrawMenus(3);
    smartDelay(1000);
  }
  
  //Serial.printf("Page: %d, Menuitem: %d, Mode: %d",pagenum, menuitem, mode);
  //Serial.println("");
  lcnt++; // loop counter
}


String mystr;
static void smartDelay(unsigned long ms)
{
  mystr = "";
  char c = '\0';
  unsigned long start = millis(); 
  do 
  {
    while (Serial7.available()){
      //gps.encode(c=Serial7.read());
      Serial.printf("%c",c);
    }
    //Serial.print(mystr);
 
  } while (millis() - start < ms);
  //Serial.println("+");
}




#pragma message "---------- BUILDING MAIN SKETCH - DONE ----------"
