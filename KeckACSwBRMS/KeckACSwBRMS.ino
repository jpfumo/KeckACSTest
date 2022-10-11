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
// 0.3.4  10/11/22  JPF RE-wrote GALIL control law to look at the APC (actual motion) instead of GALIL count

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
#include "Adafruit_ILI9341.h"
#include "arduinoFFT.h"
#include <TinyGPS++.h>
//#include <Preferences.h>
#include <HardwareSerial.h>
#include <TFT_eSPI.h>
//#include <Button2.h>
#include <Wire.h>
#include <MPU6050.h>
#include <PCF8574.h> 
#include <Adafruit_INA219.h>
#include "ILI9341_t3n.h"

#include <ADC.h>
#include <ADC_util.h>
#include <FastLED.h>
#define NUM_LEDS 1

//#include <avr/interrupt.h>
//#include "TeensyTimerTool.h"

//using namespace TeensyTimerTool;


//Timer t1(TCK);  // Tick-Timer does not use any hardware timer (20 32bit channels)
//Timer t2(TMR1); // First channel on TMR1 aka QUAD timer module. (TMR1 - TMR4, four 16bit channels each)
//Timer t3(GPT1); // GPT1 module (one 32bit channel per module)
//Timer t4(TMR1); // Second channel on TMR1

#define CENTER ILI9341_t3n::CENTER
DMAMEM uint16_t fb1[320 * 240];
DMAMEM uint16_t fb2[320 * 240];

#define SAMPLINGFREQUENCY 40000
#define SAMPLING_TIME_US     ( 1000000UL/SAMPLINGFREQUENCY )

CRGB leds[1];

// Set i2c address
PCF8574 pcf8574(0x38); //pcf8574A addr = 0x70

Adafruit_INA219 ina219g(0x44);
Adafruit_INA219 ina219c(0x40);
uint32_t gcurrent;

static const uint32_t GPSBaud = 9600;
int ptype;
int mtype;
int itype;

//int rindex = 0;

enum ptype {TOP, GALIL, CYPRESS, CYPREPLY};
enum mtype{HOME, STEPS, TOTAL, MAX, CLEAR, CYCLES, ELAPSED, ERR, APCREG , RECORD, MGO, MEXIT};
enum itype{label = -1, funcall, selectable, editable, noneditable, myexit};

// label, static label, does nothing
// funcall, goto this function &function_name
// selectable, Goto to this menu
// editable, Can change the value of this item, used to create an input value
// noneditable, cannot change the value, used to display a value
// myexit, indicates the menu exit point (pagenum =0, itemnum = 0)

#define SIGNAL_LENGTH 512
double oldSignal[SIGNAL_LENGTH];
double adcBuffer[SIGNAL_LENGTH];

#define MEM_LEN 256
char databuf[MEM_LEN];

double AdcMeanValue = 0;
  int n;
  uint32_t nextTime = 0;

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10
#define TFT_MOSI 11
#define TFT_CLK 13
#define TFT_RST 8
#define TFT_MISO 12
#define PIN            6
#define NUMPIXELS      1

#define buttonUpPin 33
#define buttonDownPin 36
#define buttonSelectPin 37
#define backlight_EN 34

#define encoder0PinA 15
#define encoder0PinB 14
#define encoder0Btn 16


#define CypressCSPin 28


/* --------------------------------------------------------------------- 
 * SPI MESSAGING
 * --------------------------------------------------------------------- */
/* V2 protocol 

   1) Messages have opcodes (configuration, position, get status)
   2) Messages are validated by a checksum instead of an arbitrary signature pattern.
   3) Transfer the max message size every time, regardless of all bytes used or not.
*/
    
/* Set this to match the size of the status response message, 18 bytes */    
#define MAX_MESSAGE_SIZE 21//30
    
/* Remember the last time a message came in so we can timeout moves if the node box stops 
   talking.  1000 ticks is 1 second of not talking. */
#define MAX_LAST_MESSAGE_TIME_TICKS 1000
uint32_t LastMessageTimeTick;

/* Opcodes that can come from the node box software */
typedef enum {
    opUNDEFINED = 0,
    opConfig    = 1,
    opStatus    = 2,
    opSetEnc    = 3,
    opMAX       
} txMessage_opcodes_t;    

/* Sanity check for opcodes */
#define txMessageOpcodeValid(op) ( ((txMessage_opcodes_t) op > opUNDEFINED) && ((txMessage_opcodes_t) op < opMAX) )

typedef struct { 
    uint8_t checksum;        
    uint8_t size;       /* Size of the message bytes, including opcode and size and checksum */
    uint8_t opcode;     /* Operation (generic overlay for previewing opcode value) */
} __attribute__ ((__packed__)) txMessage_overlay_t;

/* Configuration message, 19 bytes */
typedef struct {
    uint8_t checksum;        
    uint8_t size;       /* Size of the message bytes, including opcode and size and checksum */
    uint8_t opcode;     /* Operation: 01 == config */        
    uint8_t sequence;   /* Configuration message sequence number */
    float Kp;         /* PID constants to be used in calculation */
    float Ki;
    float Kd;
    uint8_t limit_Total;/* Total drive output limit, +/- percentage */
    uint8_t limit_ITerm;/* PID I term output limit, also +/- percentage */
    uint8_t effsetdelta;/* PID effective setpoint increment delta, nominally 25 steps */
} __attribute__ ((__packed__)) txMessage_config_t;

/* Status message, contains desired position and such values, 12 bytes */
typedef struct {
    uint8_t  checksum;        
    uint8_t  size;       /* Size of the message bytes, including opcode and size and checksum */
    uint8_t  opcode;     /* Operation: 02 == status */
    uint8_t  enable;     /* Enable/disable PID algorithm */
    int32_t  setpoint;   /* Setpoint (desired actuator position) */
    uint8_t   jog;        /* Jog value, to manually move the motor; valid range -100 to 100 */ 
    uint8_t  clearfaults;/* Set to nonzero to clear all the current faults */
} __attribute__ ((__packed__)) txMessage_status_t;
   
/* Clear message, contains new encoder position, 7 bytes */
typedef struct {
    uint8_t  checksum;        
    uint8_t  size;       /* Size of the message bytes, including opcode and size and checksum */
    uint8_t  opcode;     /* Operation: 03 == set encoders */
    uint32_t  setpoint;   /* Setpoint (force an actuator logical position) */
} __attribute__ ((__packed__)) txMessage_setenc_t;


/* Wrap the message with an array of bytes */
union {
    uint8_t               buf[MAX_MESSAGE_SIZE];
    txMessage_overlay_t overlay;
    txMessage_config_t  config;
    txMessage_status_t  status;  
    txMessage_setenc_t  setenc;
} txMessage;

/* Message back to the BBB, watch out for alignment here by packing the structure (should be 18 bytes) */
typedef struct  {  
    uint8_t  checksum;   /* Message checksum */    
    uint8_t  version0;   /* Version byte 0 */ 
    uint8_t  version1;   /* Version byte 1 */
    uint8_t  version2;   /* Version byte 2 */
    uint8_t  size;       /* Size of the message bytes, including opcode and size and checksum */
    uint8_t  opcode;     /* Echo back of the opcode this response is for, operation: 02 == status */
    uint8_t  state;      /* Enum value for current device configuration state */ 
    uint8_t  fault;      /* Bit encoded fields for current fault status */
    uint8_t  sequence;   /* Echo back the config sequence number currently set */
    uint16_t checksum_errors; /* Count of checksum errors */
    int16_t current;     /* Motor current consumption (mA) */
    int32_t position;    /* Actual actuator position, signed value */ 
    float pwm;         /* PWM value the motor is moving at */     
} __attribute__ ((__packed__)) rxMessage_t;

/* Wrap the message with an array of bytes */
union {    
    uint8_t       buf[MAX_MESSAGE_SIZE];
    rxMessage_t msg;
} rxMessage;

/* State machine definition for transmit side of messaging */
typedef enum {
    rxmsClear,    /* Transmit message buffer is empty and needs loading */
    rxmsLoaded    /* Transmit message buffer has been loaded by the message thread for sending */
} rxMessageStates_t;

rxMessageStates_t rxMessageState;


volatile int8_t Jog, LastJog;
bool PID_Enabled, PID_Was_Enabled;
int32_t PID_Setpoint, PID_EffectiveSetpoint;
uint8_t PID_EffSetDelta;
uint32_t lastTime;
float Output;
float ITerm;
volatile int32_t Position, LastPosition;
float refKp, refKi, refKd;
float kp, ki, kd;
uint32_t refSampleTime = 5; // Default to 5ms
float outMax_Total, outMax_ITerm;
float pwmLimit, pwmMax, pwmMin;    
bool homingDone = true;
long steps=0;
int direction = 0;
long TimeIn, TimeOut;

//boolean motion = false;
boolean inmotion = false;

int encoder0Pos = 0;
int valRotary,lastValRotary;

const int readPin = A9; // ADC0
const int readPin2 = A2; // ADC1

int bufptr = 0;
int blockcnt = 0;
int delayval = 500; // delay for half a second
int ledToggle = 0;

int myaccx;
int myaccy;
int myaccz;

ADC *adc = new ADC(); // adc object;
arduinoFFT FFT = arduinoFFT(); /* Create FFT object */

File file;

unsigned long time_now = 0;

// Variables to save date and time
String formattedDate;
String dayStamp;
String timeStamp;
String dataMessage;
int Voltage; 
unsigned char datamsg[640];
// Define CS pin for the SD card module
const int chipSelect = BUILTIN_SDCARD;  // teensy4.1 internal SD slot!!!e


#define BUFF_SIZE 65536
#define B_MULT BUFF_SIZE/NUM_SAMPLES
bool stop_change = false;
const int ECHOSIZE = BUFF_SIZE;
const int FFTSIZE = 512; //This value MUST ALWAYS be a power of 2
const int NUMCHIPS =  12;
double vReal[FFTSIZE], vImag[FFTSIZE];
double rReal[FFTSIZE], rImag[FFTSIZE];
#define OVERLAP_SIZE 512
const int OVERLAP = FFTSIZE/OVERLAP_SIZE;

const int numbuf = ECHOSIZE/OVERLAP_SIZE - (OVERLAP-1);


union {
  uint32_t lwords[BUFF_SIZE];
  uint16_t words[BUFF_SIZE*2];
  unsigned char chars[BUFF_SIZE*4];
}i2s_buff;

double PeakValue;
double PeakLoc;
int PeakBin;

int unit_id = 0;
float humidity = 0;
float  temperature;
float previousDepth;
float welldepth;
float welldepthcor;
bool firstDepth = 1;
float MinDepth = 25;
float MaxDepth = 500;
float TubeDia = 1.0;
int Lora_Enable = 0;
bool Data_Enable = false;
bool Galil_SlowFlag = false;
unsigned int GainAmp = 1;
long ElapsedTime = 0;
int rgsequence = 0;

short Start = 1;
short menu = 19;
short sample = 0;       // index for double buffer
int amplitude = 0;
int amplitudeStep = 5;
uint8_t rotation = 0;
int buttonState = 0;
volatile bool RotaryFlag = false;

int TimeBetweenSamples = 1;  //seconds
int firsttime = 0;
int Filter_Enable = 1;
int Filter_FirstTime = 1;
int EngUnits = 0; // 0 = Imperial, 1 = Metric
bool processmenuflag = false;
bool processmenuitem = false;


#define GALIL_RST 17
#define GALIL_CLK 0
#define GALIL_DEC 21
#define GALIL_INC 22
#define GALIL_IDX 39
#define GALIL_HOM 25
#define GALIL_B 24
#define GALIL_A 23
#define GALIL_ERRn 20

#define PROBE 35

#define Cypress_RSTn 35
#define Cypress_HOM 40
#define Cypress_IDX 41
#define PWM_DISABLE_MOT0 3

#define GALIL_MAX_STEP 2048

int DataFiles = 0;
int ADCGain = 0;
//int Position = 0; 
int GALIL_Count = 0; 
int GALIL_MTRPUL = 0;
int Cypress_Count = 0; 
int mode = 0; // 0 = none, 1 = GALIL, 2 = Cypress
int MTRPUL = 0;
volatile long APC = 0;
volatile long NEWAPC;

int servorate = 0;

volatile long deltaapc;
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


int lastA, lastB; // A/B encoder last values;

float FlowRate = 0;

double avg_pf = 0.0;
char  mylat[64];
char  mylon[64];
char  myutc[64];

String latstr;
String lonstr;
String myutctime;
String myutcdate;

uint8_t mystring[64];
uint8_t tempstr1[64];
uint8_t tempstr2[64];
uint8_t tempstr3[64];
uint8_t tempdepth[12];
uint8_t myDATEUTC[64];
uint8_t myUTC[64];
uint8_t myDate[64];
uint8_t mystrlen;


float shuntvoltage = 0;
float busvoltage = 0;
float current_mA = 0;
uint16_t rawcurrent;
float loadvoltage = 0;
float power_mW = 0;


//Preferences preferences;

ILI9341_t3n tft = ILI9341_t3n(TFT_CS, TFT_DC, TFT_RST);

// Width and height of sprite
#define WIDTH  240  // was 320
#define HEIGHT 320  // was 240 

#define IWIDTH  240  // was 320
#define IHEIGHT 320  // was 240

#define ROWPLACE 20
#define ROWOFFSET 5
const int LCD_WIDTH = 320;
const int LCD_HEIGHT = 240;
const int SAMPLES = 320; // sets # samples and width of graph...

int menuitem = 0;
int topmenuitem = 0;
int pagenum = 0;

double mysamples[SAMPLES]; // keep twice of the number of channels to make it a double buffer
//double oldSignal[SAMPLES];
double mysamplesd[SAMPLES]; // keep twice of the number of channels to make it a double buffer
double oldSignald[SAMPLES];
double mysamplesf[SAMPLES]; // keep twice of the number of channels to make it a double buffer
double oldSignalf[SAMPLES];
double mysamplesh[SAMPLES]; // keep twice of the number of channels to make it a double buffer
double oldSignalh[SAMPLES];
double mysamplest[SAMPLES]; // keep twice of the number of channels to make it a double buffer
double oldSignalt[SAMPLES];

double vmin;
double vmax;
double cvmin;
double cvmax;
double hvmin;
double hvmax;
double tvmin;
double tvmax;

// Status Info
char lat[20] = "118.234567\0";
char lon[20] = "31.234567\0";
char utc[20] = "11.234567\0";
char hv[12] = "364.5\0";

char sz1[64];
char sz2[64];
char gcnts[10];

char s_temp1[10];
char s_temp2[10];
char s_temp3[10];

char label1[25];

#define OscopeLeft 0
#define OscopeRight 320
#define OscopeTop 0
#define OscopeWidth 320
#define OscopeBottom 240
#define OscopeHeight OscopeBottom-OscopeTop

#define dOscopeLeft 0
#define dOscopeRight 320
#define dOscopeTop 0
#define dOscopeWidth 320
#define dOscopeBottom 240
#define dOscopeHeight OscopeBottom-OscopeTop

#define hOscopeLeft 0
#define hOscopeRight 319
#define hOscopeTop 80
#define hOscopeWidth 257
#define hOscopeBottom 160
#define hOscopeHeight hOscopeBottom-hOscopeTop

#define tOscopeLeft 0
#define tOscopeRight 319
#define tOscopeTop 160
#define tOscopeWidth 257
#define tOscopeBottom LCD_HEIGHT
#define tOscopeHeight tOscopeBottom-tOscopeTop

const int DOTS_DIV = 16;
#define bits24 16777216
#define bits24by2 8388608

#define OscopeCenter OscopeTop+OscopeHeight/2
#define CH1COLOR YELLOW
#define CH2COLOR CYAN
#define GREY 0x7BEF


#define filetag "/ACS"
int filenum = 0;
char filename[15];
char oldfilename[15];
char filelabel[15];
int filestatus = 0;
int recnum = 0;




IntervalTimer myTimer;

int addnum(int y){
  int j;
  j=56*y;
  return(j);
}

int subnum(int k){
  int y;
  y=k*23;
  return(y);
}

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


void CypressWrite(byte xbuf[], int bufsize) {
  byte c;

  SPI1.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE2));
 
  digitalWrite(CypressCSPin,LOW);
  for(int i = 0; i<bufsize;i++){
    c = SPI1.transfer(xbuf[i]);
    Serial.printf("%d ",c);
    rxMessage.buf[i] = c;
  }
    //Serial.println("");
  digitalWrite(CypressCSPin,HIGH);
  SPI.endTransaction();
  for(int i = 0; i<bufsize;i++){
    Serial.printf("%d ", rxMessage.buf[i]);
  }
  Serial.println("");
}


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
    galil_err = false; // GALIL is fine 
  }
}

void doEncoder()
{
  A = digitalRead(encoder0PinA);
  B = digitalRead(encoder0PinB);
  //Serial.printf("rotary: a = %d, b = %d", A, B);
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
  //detachInterrupt(digitalPinToInterrupt(GALIL_HOM));
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

//void WriteSonarData(fs::FS &fs, char * path)
void WriteCurrentData(char * path)
{
  
  int loop;
  
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
  int n = 0;
  
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

void findminmax(void){
  int loop;
  
  vmin = 100000000;
  vmax = -100000000;
  for (loop = 0; loop < SAMPLES-1; loop++)
    {

      if(vmin>vReal[loop])
        vmin = vReal[loop];
      if(vmax<vReal[loop])
        vmax = vReal[loop]; 
    }
    //Serial.printf("V Min %.9f\n\r", vmin);
    //Serial.printf("V Max %.9f\n\r", vmax);
}

void DrawGrid()
{
  for (int x = 0; x <= SAMPLES; x += 2) // Horizontal Line
  {
    for (int y = dOscopeTop; y <= dOscopeBottom; y += DOTS_DIV)
    {
      tft.drawPixel(x, y, TFT_DARKGREEN);
    }
  }
  for (int x = 0; x <= SAMPLES; x += DOTS_DIV) // Vertical Line
  {
    for (int y = dOscopeTop; y <= dOscopeBottom; y += 2)
    {
     tft.drawPixel(x, y, TFT_DARKGREEN);
    }
  }
}

int current_val;

void DisplayInfo(void){

  char temp[25];

  int i=1;
  tft.fillScreen(TFT_BLACK);
  //displayLatLonUTC(gps.location.lat(),gps.location.lng(), gps.date, gps.time );

  tft.drawRect(0,0,WIDTH, HEIGHT, TFT_ORANGE);
  tft.setTextSize(2);
  tft.setTextColor(TFT_ORANGE,TFT_BLACK);
  tft.setCursor(10, 10);
  tft.println("DATA DISPLAY");
  tft.setTextColor(TFT_LIGHTGREY,TFT_BLACK); 
  tft.setCursor(10, 15+15*i++);
  tft.println("UNIT ID: 02");
  tft.setCursor(10, 15+15*i++);
  tft.printf("LAT:%s", mylat);
  tft.setCursor(10, 15+15*i++);
  tft.printf("LON:%s", mylon);
  tft.setCursor(10, 15+15*i++);
  tft.printf("DAT: %s", myDate);
  tft.setCursor(10, 15+15*i++);
  tft.printf("UTC: %s", myUTC);
  tft.setCursor(10, 15+15*i++);
  sprintf(temp,"%d", myaccx);
  tft.printf("ACCX: %s", temp);
  tft.setCursor(10, 15+15*i++);
  sprintf(temp,"%d", myaccy);
  tft.printf("ACCY: %s", temp);
  tft.setCursor(10, 15+15*i++);
  sprintf(temp,"%d", myaccz);
  tft.printf("ACCZ: %s", temp);
  tft.setCursor(10, 15+15*i++);
  
}

char *ultos_recursive(unsigned long val, char *s, unsigned radix, int pos)
{
  int c;

  if (val >= radix)
    s = ultos_recursive(val / radix, s, radix, pos+1);
  c = val % radix;
  c += (c < 10 ? '0' : 'a' - 10);
  *s++ = c;
  if (pos % 3 == 0) *s++ = ',';
  return s;
}

char *ltos(long val, char *s, int radix)
{
  if (radix < 2 || radix > 36) {
    s[0] = 0;
  } else {
    char *p = s;
    if (radix == 10 && val < 0) {
      val = -val;
      *p++ = '-';
    }
    p = ultos_recursive(val, p, radix, 0) - 1;
    *p = 0;
  }
  return s;
}

void FillinCypressResponse(){

  uint32_t version, position;
  float pwm;
  char buf[32];
  version = rxMessage.msg.version0<<16 | rxMessage.msg.version1<<8 | rxMessage.msg.version2;
  position = 0;
  position = (uint32_t)(rxMessage.buf[13]) | (rxMessage.buf[14]<<8) | (rxMessage.buf[15]<<16) | (rxMessage.buf[16]<<24);
  //Serial.println(ltos(position, buf, 10));
  Serial.printf("p: %010d", position);
  //Serial.println("");
  
  mymenu[CYPREPLY].m[0].mvalue.mval.b = rxMessage.msg.checksum;
  mymenu[CYPREPLY].m[1].mvalue.mval.b = version;
  mymenu[CYPREPLY].m[2].mvalue.mval.b = rxMessage.msg.size;
  mymenu[CYPREPLY].m[3].mvalue.mval.b = rxMessage.msg.opcode;
  mymenu[CYPREPLY].m[4].mvalue.mval.b = rxMessage.msg.state;
  mymenu[CYPREPLY].m[5].mvalue.mval.b = rxMessage.msg.fault;
  mymenu[CYPREPLY].m[6].mvalue.mval.b = rxMessage.msg.sequence;
  mymenu[CYPREPLY].m[7].mvalue.mval.w = rxMessage.msg.checksum_errors;
  mymenu[CYPREPLY].m[8].mvalue.mval.w = rxMessage.msg.current;
  mymenu[CYPREPLY].m[9].mvalue.mval.l = (uint32_t)position;
  mymenu[CYPREPLY].m[10].mvalue.mval.f = rxMessage.msg.pwm;
}


void DrawMenus(int level){ // level = menu number
  String Dstr;
  String Tstr;
  char Teststr[40];
  int numitems = 0;
  int Xoffset = 10;
  int Yoffset = 25;
  int Yincrement = 20;
  int index = 1;
  int i;
  float etime;
  int myerror;
  int offset;

  float fmindepth, fmaxdepth, ftubesize;

  tft.setTextSize(2);
  Dstr = " ft";
  Tstr = " in";
  tft.fillScreen(TFT_BLACK); 
  tft.drawRect(0,0,WIDTH, HEIGHT-1, TFT_GREEN);
  tft.setCursor(10, 5);

  tft.setTextColor(TFT_ORANGE,TFT_BLACK);
  strcpy(Teststr,mymenu[level].title);
  
  //Serial.printf("%d, %s", level, Teststr); 
  //Serial.println("");
  
  tft.printf("%s", Teststr);
  tft.println("");

  if(level==GALIL){ // update values
    if(abs(mymenu[GALIL].m[CYCLES].mvalue.mval.l) >= 1)
      mymenu[GALIL].m[TOTAL].mvalue.mval.l = mymenu[GALIL].m[STEPS].mvalue.mval.l * (int)mymenu[GALIL].m[CYCLES].mvalue.mval.b;
    else
      mymenu[GALIL].m[TOTAL].mvalue.mval.l = mymenu[GALIL].m[STEPS].mvalue.mval.l;

    //myerror = readGALILError();
    offset = APC-NEWAPC;
    mymenu[GALIL].m[ERR].mvalue.mval.b = offset;
    //Serial.printf("Count: %d,TOTAL %d", (int)mymenu[GALIL].m[CYCLES].mvalue.mval.b, (int)mymenu[GALIL].m[TOTAL].mvalue.mval.l); 
    //Serial.println("");
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
    //Serial.printf("i: %d, mval: %d",i, mymenu[level].m[i].mvalue.mval.l);
    //Serial.println("");
    tft.updateScreen(); 
  }


//  if(level==CYPRESS){
//    FillinCypressResponse(level);
//    CypressStatus();
//  }


}


uint16_t readGALILcurrent(){
  //shuntvoltage = ina219g.getShuntVoltage_mV();
  //busvoltage = ina219g.getBusVoltage_V();
  //current_mA = ina219g.getCurrent_mA();
  rawcurrent = ina219g.getCurrent_raw();
  //power_mW = ina219g.getPower_mW();
  //loadvoltage = busvoltage + (shuntvoltage / 1000);
  Serial.print("Current:       "); Serial.print(rawcurrent); Serial.println(" mA");
  return(current_mA);
}


enum dtype{CW, CCW};
#define CLK5K0 100
#define CLK625H0 400
#define CLK156H25 800



int GALILGo(int k){

  int numloop =0;
  int remain = 0;
  int steps;
  int i, j, n = 0;
  int err;

  int term;
  int moresteps;
  int iloop = 0;

  bufptr = 0;
  for(i=0; i< BUFF_SIZE; i++)
    i2s_buff.words[i] = 0;
  
  steps = mymenu[GALIL].m[TOTAL].mvalue.mval.l;
  NEWAPC = APC+steps; // calculate the new APC value
  Serial.printf("NEWAPC: %d", NEWAPC);
  Serial.println("");
  nsteps = (abs)(steps);

  TimeIn = micros();
  galil_err = false; // enable the motion

  Galil_SlowFlag = false; 
  write_file = false;
  inmotion = true;
  return(0);
}

int GALILGoOLD(int k){

  int numloop =0;
  int remain = 0;
  int steps;
  int i, j, n = 0;
  int err;

  int term;
  int moresteps;
  int iloop = 0;

  bufptr = 0;
  
  // set the direction based on the sign of the steps
  if(mymenu[GALIL].m[TOTAL].mvalue.mval.l >0){
    direction = CCW;
  }
  else{
    direction = CW;
  }

  steps = mymenu[GALIL].m[TOTAL].mvalue.mval.l;
  Serial.printf("steps: %d", steps);
  Serial.println("");
  nsteps = (abs)(steps);

  Serial.printf("APC= %d, steps: %d, nsteps: %d, n= %d, r= %d, Dir= %d, Term= %d", APC, steps, nsteps,  n, remain, direction, term);
  Serial.println("");

  TimeIn = micros();
  galil_err = false; // enable the motion
  inmotion = true;
  Galil_SlowFlag = false; 
  write_file = false;

  /*
  //DrawMenus(pagenum);
  Serial.printf("Elapsed: %ld", ElapsedTime);
  Serial.println("");
  //i2s_buff.words[0] = bufptr;  // first value is the number of samples
  WriteCurrentData(filename);  // send the data to the diskdrive
  bumpFilename(); // create the next filename
  */
  return(0);
  
}

void GALILpulse(int steps, int direction, int pulsedelay){
  int i;
  if(direction == CW){  // CW = 0, positive = CW
    for(i=0; i<steps; i++){
      digitalWrite(GALIL_DEC, LOW);
      delayMicroseconds(pulsedelay);     
      digitalWrite(GALIL_DEC, HIGH);
      delayMicroseconds(pulsedelay);
      if(recording==true){
        rawcurrent = ina219g.getCurrent_raw();
        i2s_buff.words[bufptr++] = rawcurrent;
        i2s_buff.words[bufptr++] = APC;  
      }
    }
  }else{
    for(i=0; i<steps; i++){ // CW = 1, negative = CCW
      digitalWrite(GALIL_INC, LOW);
      delayMicroseconds(pulsedelay);
      digitalWrite(GALIL_INC, HIGH);
      delayMicroseconds(pulsedelay);
      if(recording==true){
        rawcurrent = ina219g.getCurrent_raw();
        i2s_buff.words[bufptr++] = rawcurrent;
        i2s_buff.words[bufptr++] = APC;  
      }
    }    
  }
  //Serial.println("GALIL Pulse");
}

void GALILReset(){
  digitalWrite(GALIL_RST, HIGH);
  delay(50);
  digitalWrite(GALIL_RST, LOW);
  delay(50);
  digitalWrite(GALIL_RST, HIGH);
  delay(50);

}

void GALILHold(){
  digitalWrite(GALIL_RST, HIGH);
  delay(50);
  digitalWrite(GALIL_RST, LOW);
  delay(50);
}

void GALILRelease(){
  digitalWrite(GALIL_RST, HIGH);
  delay(50);
}

int GALILHome(int i){

  char temp[25];
  int mval;

  attachInterrupt(digitalPinToInterrupt(GALIL_HOM), doHome, LOW);

  foundHome = false;
  //Serial.println("GALIL Home Command");
  while(foundHome == false && (digitalRead(GALIL_HOM)==1)){ // only excute if not home
    GALILpulse(1, CCW, CLK156H25);//CLK5K0
    //Serial.println("looking for Home");  
    
  }
  //delay(10);

  attachInterrupt(digitalPinToInterrupt(GALIL_IDX), doIndex, HIGH);

  foundIndex = false;
  while(foundIndex == false && (digitalRead(GALIL_IDX)==0)){ // only excute if not index
  //while(1){
    GALILpulse(1, CW, CLK156H25); //CLK156H25
    //Serial.println("looking for Index");
  }
  
  delay(100);// WAIT FOR ROTOR TO SETTLE OUT BEFORE ZERO OF APC
  MTRPUL = 0;   //reset the MTRPUL register
  APC = 0;      // reset the APC
  NEWAPC = 0;
  mymenu[GALIL].m[APCREG].mvalue.mval.l = APC;
  Serial.println("GALIL Home Complete");
  DrawMenus(pagenum);
  return(0);
}

int GALILMax(int i){

  char temp[25];
  GALIL_Count = GALIL_MAX_STEP; 
  Serial.println("GALIL Max Command");
  Serial.printf("%d",GALIL_Count);
  Serial.println("");
  mymenu[1].m[1].vsize = 3; //long
  mymenu[1].m[1].mvalue.mval.l = (long)GALIL_Count;
  DrawMenus(pagenum);
  return(0);
}

int GALILClear(int i){

  char temp[25];
 
  Serial.println("GALIL Clear Command");
  GALIL_Count = 0;
  mymenu[1].m[1].mvalue.mval.l = GALIL_Count;
  DrawMenus(pagenum);
  return(0);
}

void CypressPulse(long steps, int direction, int pulsedelay){
  int checksum = 0;
  int i;

  Serial.println("Cypress Pulse");
  Serial.printf("MSG size: %d", 12);
  Serial.println("");
  for(i=0; i<19; i++){
    txMessage.buf[i] = 0;
  }

  
  // fill in the SetPosition message
  txMessage.status.size = 12;
  txMessage.status.opcode = opStatus;
  txMessage.status.enable = 0;
  txMessage.status.setpoint = steps;
  txMessage.status.jog = 10 * direction;
  txMessage.status.clearfaults = 1;

  // Set the checksum in the packet
  for (i = 0, checksum = 0; i < 12; i++)
    checksum += txMessage.buf[i]; 
    
  // Take the 2's complement of the sum and put it back in the message    
  txMessage.setenc.checksum = ~checksum + 1;
  Serial.printf("x: ");
  for(i=0; i<19; i++){
    Serial.printf("%d ",txMessage.buf[i]);
  }
  Serial.println("");
  //write SetPosition to the Cypress over the SPI
  CypressWrite(txMessage.buf, 12); //sizeof(txMessage.buf));

}

void CypressCW(long steps){
  int checksum = 0;
  int i;

  Serial.println("Cypress CW");
  for(i=0; i<19; i++){
    txMessage.buf[i] = 0;
  }

  
  // fill in the SetPosition message
  txMessage.status.size = 12;
  txMessage.status.opcode = opStatus;
  txMessage.status.enable = 0;
  txMessage.status.setpoint = steps;
  txMessage.status.jog = 10;
  txMessage.status.clearfaults = 1;

  // Set the checksum in the packet
  for (i = 0, checksum = 0; i < 12; i++)
    checksum += txMessage.buf[i]; 
    
  // Take the 2's complement of the sum and put it back in the message    
  txMessage.setenc.checksum = ~checksum + 1;
  Serial.printf("x: ");
  for(i=0; i<19; i++){
    Serial.printf("%d ",txMessage.buf[i]);
  }
  Serial.println("");
  //write SetPosition to the Cypress over the SPI
  CypressWrite(txMessage.buf, 12); //sizeof(txMessage.buf));

}

void CypressCCW(long steps){
  int checksum = 0;
  int i;

  Serial.println("Cypress CCW");
  for(i=0; i<19; i++){
    txMessage.buf[i] = 0;
  }

  
  // fill in the SetPosition message
  txMessage.status.size = 12;
  txMessage.status.opcode = opStatus;
  txMessage.status.enable = 0;
  txMessage.status.setpoint = steps;
  txMessage.status.jog = -10;
  txMessage.status.clearfaults = 1;

  // Set the checksum in the packet
  for (i = 0, checksum = 0; i < 12; i++)
    checksum += txMessage.buf[i]; 
    
  // Take the 2's complement of the sum and put it back in the message    
  txMessage.setenc.checksum = ~checksum + 1;
  Serial.printf("x: ");
  for(i=0; i<19; i++){
    Serial.printf("%d ",txMessage.buf[i]);
  }
  Serial.println("");
  //write SetPosition to the Cypress over the SPI
  CypressWrite(txMessage.buf, 12); //sizeof(txMessage.buf));

}

void CypressInit(void){
  int checksum = 0;
  int i = 0;
  Serial.println("Cypress Init");
  Serial.printf("MSG size: %d", 19);
  Serial.println("");
  // fill in the configuration message
  txMessage.config.size = 19;
  txMessage.config.opcode = opConfig;
  txMessage.config.sequence = 0;
  txMessage.config.Kp = kp;
  txMessage.config.Ki = ki;
  txMessage.config.Kd = kd;
  txMessage.config.limit_Total = 100;
  txMessage.config.limit_ITerm = 100;
  txMessage.config.effsetdelta = 25;

  // Set the checksum in the packet
  for (i = 0, checksum = 0; i < 19; i++)
    checksum += txMessage.buf[i]; 
    
  // Take the 2's complement of the sum and put it back in the message    
  txMessage.config.checksum = ~checksum + 1;
  Serial.printf("x: ");
  for(i=0; i<19; i++){
    Serial.printf("%d ",txMessage.buf[i]);
  }
  Serial.println("");
  //write configuration to the Cypress over the SPI
  CypressWrite(txMessage.buf, 19); //sizeof(txMessage.buf));

}


void CypressStatus(void){
  int checksum = 0;
  int i = 0;

  // clear out the buffer
  for (i = 0; i < MAX_MESSAGE_SIZE; i++)
    txMessage.buf[i] = 0; 
  Serial.println("Cypress Status");
  // fill in the status message
  txMessage.status.checksum = 0;
  txMessage.status.size = 10;
  txMessage.status.opcode = opStatus;
  txMessage.status.enable = 0;
  txMessage.status.setpoint = 0;
  txMessage.status.jog = 0;
  txMessage.status.clearfaults = 1;


  // Set the checksum in the packet
  checksum = 0;
  for (i = 0; i < MAX_MESSAGE_SIZE; i++)
    checksum += txMessage.buf[i]; 
    
  // Take the 2's complement of the sum and put it back in the message    
  txMessage.status.checksum = ~checksum+1;

  Serial.printf("s: ");
  for(i=0; i<MAX_MESSAGE_SIZE; i++){
    Serial.printf("%d ",txMessage.buf[i]);
  }
  Serial.println("");

  //write configuration to the Cypress over the SPI
  CypressWrite(txMessage.buf, MAX_MESSAGE_SIZE); //sizeof(txMessage.buf));
}

int CypressHome(int i){

  char temp[25]; 
  int mval;
  Serial.println("Cypress Home Command");

  attachInterrupt(digitalPinToInterrupt(Cypress_HOM), docpHome, LOW);
  attachInterrupt(digitalPinToInterrupt(Cypress_IDX), docpIndex, HIGH);

  foundcpHome = false;
  while(foundcpHome == false && (digitalRead(Cypress_HOM)==1)){ // only execute if not home
    CypressCCW(1000);
  }
  delay(10);
  
  foundcpIndex = false;
  while(foundcpIndex == false && (digitalRead(Cypress_IDX)==0)){ // only execute if not index
    CypressCW(100);
  }
  delay(10);// WAIT FOR ROTOR TO SETTLE OUT BEFORE ZERO OF APC
  
  APC = 0;      // reset the APC
  mymenu[CYPRESS].m[APCREG].mvalue.mval.l = APC;
  DrawMenus(pagenum);
  return(0);
}

int CypressMax(int i){

  char temp[25];
 
  Cypress_Count = 2048;
  Serial.println("Cypress Max Command");
  Serial.printf("%d",Cypress_Count);
  Serial.println("");
  mymenu[2].m[1].vsize = 3; //long
  mymenu[2].m[1].mvalue.mval.l = Cypress_Count;
  DrawMenus(pagenum);
  return(0);
}

int CypressClear(int i){

  char temp[25];
 
  Serial.println("Cypress Clear Command");
  Cypress_Count = 0;
  mymenu[2].m[1].mvalue.mval.l = Cypress_Count;
  DrawMenus(pagenum);
  return(0);
}

void CypressGo(void){
  long TimeIn, TimeOut, ElapsedTime;
  int i;
  
  for(i=0; i< BUFF_SIZE; i++)
  i2s_buff.words[i] = 0;
  
  TimeIn = micros();
  Serial.printf("TimeIn: %d ",TimeIn);
  Serial.println("");
  CypressPulse(mymenu[CYPRESS].m[TOTAL].mvalue.mval.l, -1,0); // need to fix this....
  TimeOut = micros();
  Serial.printf("TimeOut: %d ",TimeOut);
  Serial.println("");
  ElapsedTime = TimeOut - TimeIn;
  Serial.printf("TimeElapsed: %d ",ElapsedTime);
  Serial.println("");
  mymenu[CYPRESS].m[ELAPSED].mvalue.mval.l = ElapsedTime;
}

int initGALILError(void){

  int target = 0x70;
  databuf[0] = 0xff;
  Wire.beginTransmission(target);   // Slave address
  Wire.write(databuf,1); // Write string to I2C Tx buffer (incl. string null at end)
  Wire.endTransmission();           // Transmit to Slave
}
#define DigitalInput byte
//#define PCF8574_LOW_MEMORY
int  readGALILError(void){
  int temp;
  DigitalInput  val = pcf8574.digitalReadAll();
  temp = (int)val;
  if(temp>=127) 
    temp = temp-256;  // make it signed
  return temp;
}
 

void draw_channel1(void) {
  uint32_t samplesperpixel, index;
  int32_t avg = 0, oldy, old_index;
  int32_t maxpixel, span, myval;

  
  //screen wave drawing
  // find the min and max values in the sample buffer
  int32_t max_val = -1000000000;
  int32_t min_val = 10000000000;

  float avg_val, y_thresh, y_avg, y_val, x_val;
  int mylen;
  bool peak_start = false;
  

  int bufmax = 0;

  tft.fillScreen(TFT_BLACK); 
  tft.drawRect(0,0,WIDTH, HEIGHT-1, TFT_GREEN);
  tft.setCursor(50, 5);
  tft.setTextSize(2);
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.println(" OSCILLOSCOPE ");


 // x_val = (OVERLAP_SIZE * PeakBin)+(PeakLoc);
 tft.drawRect(0,0,WIDTH, HEIGHT, TFT_GREEN);

  
  //CPM=0; // reset the counts per minute
  // find min, max, avg
  avg_val=0;
    
  // Find the Max and Min value for the entire buffer
  for (int j = 0; j < BUFF_SIZE; j++) {
    current_val = i2s_buff.words[j];
    if (current_val > max_val)
      max_val = current_val;
    else if (current_val < min_val)
      min_val = current_val; 
      avg_val += current_val;
  }
  avg_val = avg_val/BUFF_SIZE;
  span = max_val-min_val;

  
  //Serial.println("Avg Span");
  Serial.printf("Min, %d, Max, %d, Avg  %f, Span %d",min_val, max_val, avg_val, span);
  Serial.println();  
  
  oldy = (int)120;
  //Serial.printf("%d, %d", max_val, min_val);
  //Serial.println();
  samplesperpixel = ((BUFF_SIZE)/WIDTH)-1;
  
  for (int i = 0; i < WIDTH; i++) { 
    maxpixel=0;
    
    for(int k=0; k<samplesperpixel; k++){
      current_val = i2s_buff.words[i*samplesperpixel+k]; 
      if(maxpixel<current_val)
        maxpixel = current_val;
    }
    
    if(span>0){
      myval = (float)(120.0-((float)(maxpixel-min_val)/(float)span)*100);
    }
     else
      myval = 120;

   tft.drawLine(i - 1, (int)(oldy), i, (int)(myval), TFT_CYAN);
   
    oldy = (int)myval;
    old_index = index;
  }
  // draw RED line at start of pulse
 
  //Serial.printf("y_val %f ", y_val);
  //Serial.println("");
  //spr.drawLine(bufindex/samplesperpixel, 0, bufindex/samplesperpixel, 120, TFT_RED);
  //spr.drawLine(x_val/samplesperpixel, 0, x_val/samplesperpixel, 120, TFT_RED);
  //tft.drawString("START: " + String(x_val),  215, 10);
  //spr.drawString("BIN: " + String((int)PeakBin),  215, 25);
  //spr.drawString("DIST: " + String(welldepth), 215, 40);
}


void draw_channel2(void) {
  uint32_t samplesperpixel, index;
  uint32_t avg = 0, oldy, old_index;
  uint32_t maxpixel, span;
  float pixely, myval;
  int maxp;
  int i;
  
  //screen wave drawing
  // find the min and max values in the sample buffer
  uint32_t max_val = 0;
  uint32_t min_val = 100000000;
  float avg_val;
  int binpeak;

 tft.drawRect(0,0,WIDTH, HEIGHT, TFT_GREEN);

  tft.setCursor(50, 5);
  tft.setTextSize(2);
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.println(" SPECTRUM ANALYZER  ");


  //CPM=0; // reset the counts per minute
  avg_val=0;
  for (int j = 0; j < FFTSIZE; j++) {
    if (vReal[j] > max_val)
      max_val = vReal[j];
    else if (vReal[j] < min_val)
      min_val = vReal[j]; 
      avg_val += vReal[j];
  }
  avg_val = avg_val/(float)FFTSIZE;
  
  span = max_val-min_val;
  
  //avg_val = (float)(avg_val-min_val)/(span*120.0)+60.0;
  //Serial.printf("NumBuf: %d",numbuf);
  //Serial.println();  
  oldy = (int)avg_val+120;
  //Serial.printf("avg_val: %f",avg_val);
  //Serial.println();    
  //Serial.printf("span: %d",span);
  //Serial.println();    
  //span = 1000;
  //pixely = 320.0/(float)(max_val-min_val);
  //Serial.printf("%d, %d", max_val, min_val);
  //Serial.println();
  //samplesperpixel = FFTSIZE/WIDTH-1;

  index = 0;
  old_index = 0;
  for (i = 0; i < WIDTH; i++) { 
    //Serial.printf("Index: %d",index);
    //Serial.println(); 
    //myval = (float)(60.0-(vReal[i]-min_val)/span*60.0)+60.0;//+30.0;
    if(span>0)
      myval = (float)(120.0-(60.0*(vReal[i]-min_val)/span))+120;//+30.0;
    else
      myval = (float)(120.0-(60.0*(vReal[i]-min_val)))+120;//+30.0;
    //Serial.printf("myval: %f",myval);
    //Serial.println();    
    //index+=WIDTH/numbuf;
    //Serial.printf("Index2: %d",index);
    //Serial.println();     
    if(myval>0.0)
     tft.drawLine(old_index, (int)oldy,     index, (int)myval, TFT_CYAN);
    oldy = (int)myval;
    old_index = index;

  }

 //tft.drawString("PEAK VAL: " + String(PeakValue),  175, 120+15);
 //tft.drawString("PEAK LOC: " + String(PeakLoc),  175, 120+30);
 //tft.drawString("PEAK BIN: " + String((int)PeakBin),  175, 120+45);
  //cor.setTextSize(2);
  //welldepthcor = (samplerate*OVERLAP_SIZE*PeakBin + samplerate*PeakLoc + BLANKING_DELAY*0.001)/2.0*SpeedofSoundinAir;
  //cor.drawString("DISTANCE: " + String(welldepthcor),  215, 100);
  //cor.setTextSize(1);

    //Serial.printf("%d",maxp);
   //Serial.println("done ch2");
}

void findflowminmax(void){
  int loop;
  
  vmin = 100000000;
  vmax = -100000000;
  for (loop = 0; loop < SAMPLES-1; loop++)
    {

      if(vmin>i2s_buff.words[loop])
        vmin = i2s_buff.words[loop];
      if(vmax<i2s_buff.words[loop])
        vmax = i2s_buff.words[loop]; 
    }
    //Serial.printf("V Min %.9f\n\r", vmin);
    //Serial.printf("V Max %.9f\n\r", vmax);
}

void ColorBar()
{
    float color_r, color_g, color_b;

    color_r = 0;
    color_g = 0;
    color_b = 255;

    for (int i = 0; i < 320; i=i+4)
    {
        if (i < 128)
        {
            color_r = i * 2;
            color_g = 0;
            color_b = 255 - (i * 2);
        }
        else if ((i >= 128) && (i < 256))
        {
            color_r = 255 - ((i - 128) * 2);
            color_g = (i - 128) * 2;
            color_b = 0;
        }
        else if ((i >= 256) && (i < 384))
        {
            color_r = 0;
            color_g = 255 - ((i - 256) * 2);
            ;
            color_b = (i - 256) * 2;
            ;
        }
        tft.fillRect(0, 0, 240, 135, tft.color565(color_r, color_g, color_b));

    }

    for (int i = 0; i < 4; i++)
    {
        switch (i)
        {
        case 0:
            color_r = 0;
            color_g = 0;
            color_b = 0;
            break;
        case 1:
            color_r = 255;
            color_g = 0;
            color_b = 0;
            break;
        case 2:
            color_r = 0;
            color_g = 255;
            color_b = 0;
            break;
        case 3:
            color_r = 0;
            color_g = 0;
            color_b = 255;
            break;
        }
        for (int n = 0; n < 240; n++)
        {
            color_r = (color_r < 255) ? color_r + 1.0625 : 255U;
            color_g = (color_g < 255) ? color_g + 1.0625 : 255U;
            color_b = (color_b < 255) ? color_b + 1.0625 : 255U;
            tft.drawLine(n, i * 33.75, n, (i + 1) * 33.75, tft.color565(color_r, color_g, color_b));
        }
    }

    for (int i = 0; i < 4; i++)
    {
        switch (i)
        {
        case 0:
            color_r = 255;
            color_g = 255;
            color_b = 255;
            break;
        case 1:
            color_r = 255;
            color_g = 0;
            color_b = 0;
            break;
        case 2:
            color_r = 0;
            color_g = 255;
            color_b = 0;
            break;
        case 3:
            color_r = 0;
            color_g = 0;
            color_b = 255;
            break;
        }
        for (int n = 0; n < 240; n++)
        {
            color_r = (color_r > 2) ? color_r - 1.0625 : 0U;
            color_g = (color_g > 2) ? color_g - 1.0625 : 0U;
            color_b = (color_b > 2) ? color_b - 1.0625 : 0U;
            tft.drawLine(239 - n, i * 33.75, 239 - n, (i + 1) * 33.75, tft.color565(color_r, color_g, color_b));
        }
    }
}

uint16_t posData = 0;
int j=0;
int item_changed = 1; // draw it the first time

void CheckMenu(){
  int temp, ncount = 0;
  int * myint;
  //M5.update();

  if (!(buttonState = digitalRead(buttonSelectPin)))
    {
      //Serial.println("ButtonSelect");
      menu = true;
      //Serial.printf("%d,", menuitem);
      //Serial.println("Menu Select");
      if(mymenu[pagenum].m[menuitem].itemtype == funcall){  // go to function
        if( mymenu[pagenum].m[menuitem].myfunc == NULL)
          ncount++;
        else
          temp = mymenu[pagenum].m[menuitem].myfunc(3);
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
    //Serial.println("buttonUpPin");
    menuitem--;
    if(menuitem<0)
      menuitem = mymenu[pagenum].numitems-1;  // point at the top of the list
    //Serial.printf("%d,", menuitem);
    //Serial.println("menuitem");
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
    //Serial.println("buttonDownPin");
    menuitem++;
    if(menuitem>mymenu[pagenum].numitems-1) // point at the bottom of the list
      menuitem = 0;
    //Serial.printf("%d,", menuitem);
    //Serial.println("menuitem");
    delay(100);
    while(!(buttonState = digitalRead(buttonUpPin)));
    item_changed = 1;
    lastValRotary = 0;
    valRotary = 0;;
    tft.fillScreen(TFT_BLACK);
    //DrawMenus(pagenum);
  }
  if(item_changed==1){ // from interrupt Button B
      //Serial.printf("%d,", menuitem);
      //Serial.println("Menu Select");
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
      //Serial.printf("%d,", menuitem);
      //Serial.println("Btn A");
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
      //Serial.printf("%d,", menuitem);
      //Serial.println("Btn B");
      processmenuitem = true;
      DrawMenus(pagenum);
      //ProcessMenus(pagenum);
      delay(100);
      while(!(buttonState = digitalRead(buttonSelectPin)));

    } else if (!(buttonState = digitalRead(buttonUpPin))){
      if(menuitem>0)
        menuitem--;
      //Serial.printf("%d,", menuitem);
      //Serial.println("Btn C");
      DrawMenus(pagenum);
      delay(100);
      while(!(buttonState = digitalRead(buttonUpPin)));
    }
  }
}

// #########################################################################
// Return a 16 bit rainbow colour
// #########################################################################
unsigned int rainbow(byte value)
{
  // Value is expected to be in range 0-127
  // The value is converted to a spectrum colour from 0 = red through to 127 = blue

  byte red   = 0; // Red is the top 5 bits of a 16 bit colour value
  byte green = 0;// Green is the middle 6 bits
  byte blue  = 0; // Blue is the bottom 5 bits

  byte sector = value >> 5;
  byte amplit = value & 0x1F;

  switch (sector)
  {
    case 0:
      red   = 0x1F;
      green = amplit;
      blue  = 0;
      break;
    case 1:
      red   = 0x1F - amplit;
      green = 0x1F;
      blue  = 0;
      break;
    case 2:
      red   = 0;
      green = 0x1F;
      blue  = amplit;
      break;
    case 3:
      red   = 0;
      green = 0x1F - amplit;
      blue  = 0x1F;
      break;
  }

  return red << 11 | green << 6 | blue;
}




void GetSamples(void){
  long loop;

  time_now = micros();
  
  for(loop = 0; loop<BUFF_SIZE; loop++){
     i2s_buff.words[loop] = analogRead(0);; // read a new value, will return ADC_ERROR_VALUE if the comparison is false.
  }
  time_now = micros() - time_now;
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

//enum itype{label = -1, funcall, selectable, editable, myexit};
//enum mtype{HOME, STEPS, TOTAL, MAX, CLEAR, CYCLES, ELAPSED, ERR, APCREG , RECORD, MGO, MEXIT};


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
  mymenu[0].m[4].myfunc = -1;   
  
  strcpy(mymenu[0].m[5].menuname, "CYPRESS RESPONSE");
  mymenu[0].m[5].itemtype = selectable;
  mymenu[0].m[5].level = 0;
  mymenu[0].m[5].myfunc = -1;  


  
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
  mymenu[GALIL].m[MAX].level = NULL;
  mymenu[GALIL].m[MAX].myfunc = &GALILMax;  
  
  strcpy(mymenu[GALIL].m[CLEAR].menuname, "CLEAR STEPS");
  mymenu[GALIL].m[CLEAR].itemtype = funcall;
  mymenu[GALIL].m[CLEAR].level = NULL;
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
  
  strcpy(mymenu[GALIL].m[ERR].menuname, "DELTA");
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

  //enum mtype{HOME, STEPS, TOTAL, MAX, CLEAR, CYCLES, ELAPSED, ERR, APCREG , RECORD, MGO, MEXIT};

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

void ChangeSSD(void){
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
}

void checkRotary(void){
  int r_sw;
  
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


int GALIL_Slow(void){
  int myerror;

  //if(galil_err == 0) // check to see if the GALIL needs to catch up
  //    return -2;
  //Serial.println("Galil Routine");
  if (inmotion == true)
  {
    Serial.println("Galil Slow");
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
      //Serial.printf("Galil Slow APC: %d",deltaapc);
      //Serial.println("");
  }
  
  return 0;
}

void GALIL_Slow_OLD(void){
  int myerror;
  
  if(Galil_SlowFlag == true){
    Serial.println("Galil Slow");
    if(galil_err == false){
      //Serial.println("Motion True");

      if(nsteps>0){
        nsteps -= 1;
        Serial.printf("nSteps: %d",nsteps);
        Serial.println("");
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
      
      if(nsteps==0){
        // Integrator---check to see in error term is <=2
        myerror = readGALILError();
        if(abs(myerror)>=5){
          Serial.println("int...");
          myerror = readGALILError();
          nsteps++;
          direction ^= direction;
        }

        if(abs(nsteps)>0)
          Serial.println("int+++");
        else{
          Serial.println("Galil Stop");
          inmotion = false;
          Galil_SlowFlag = false; // disable the galil_slow call
          TimeOut = micros();
          ElapsedTime = TimeOut - TimeIn;
          mymenu[GALIL].m[ELAPSED].mvalue.mval.l = ElapsedTime;
          write_file = true;
        }
      }
    }
  }
}

//storage variables
boolean toggle0 = 0;
boolean toggle1 = 0;
boolean toggle2 = 0;


myitem mitem[6];  // simple test

int ledState = LOW;
volatile unsigned long blinkCount = 0;
int returned = 0;

int HighFrequency() { // High Frequency rate group = 5KHz
  rgsequence++;
  deltaapc = NEWAPC - APC;  // calculate the difference in position
  chkGALILError();  // reset the GALIL input

  if (inmotion == false)
    return -3;
  if (deltaapc == 0  && inmotion == true){  // look to see if we are done;

    inmotion = false;
    Galil_SlowFlag = false; // disable the galil_slow call
    TimeOut = micros();
    ElapsedTime = TimeOut - TimeIn;
    mymenu[GALIL].m[ELAPSED].mvalue.mval.l = ElapsedTime;
    write_file = true;

    servorate = 2;
    //Serial.println("Galil move complete");
    
    return -1;
  }

  // determine how fast to send the pulses to the GALIL
  if(abs(deltaapc) > 15 && inmotion == true)
    servorate  = 0;
  else{
    servorate = 1;
  }

  if(deltaapc >= 0)
    direction = CCW;
  else
    direction = CW;

  if (galil_err == 1)
    return -2;        // wait for the galil to catch up
  
  if (servorate == 0 && inmotion == true)
  {
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
      //Serial.printf("Galil Fast APC: %d",deltaapc);
      //Serial.println("");
  }

  switch(rgsequence){ //Scheduled Rate Groups
    case 1://2500
    case 3:
    case 5:
    case 7:
    case 9:
    case 11:
    case 13:
    case 15:
      //chkGALILError();  // reset the GALIL input
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
      if(recording==true  && inmotion == true){
        rawcurrent = ina219g.getCurrent_raw();
        i2s_buff.lwords[bufptr++] = (long)APC; 
        i2s_buff.lwords[bufptr++] = (long)deltaapc;
        i2s_buff.lwords[bufptr++] = (long)rawcurrent; 
        //Serial.printf("bufptr: %d, Current: %d", bufptr, rawcurrent);
        //Serial.println(""); 
        if(bufptr>=65530)
        recording = false;
      }
      break;
      
    case 16://156.25
       //Serial.println("RG Last");
       //Serial.printf("Servo Rate = %d", servorate);
       //Serial.println("");
       
        if (servorate == 1 )
        {
          //Serial.println("Galil Slow...");
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
            //Serial.printf("Galil Slow APC: %d",deltaapc);
            //Serial.println("");
        }
        rgsequence = 0;
        break;
        
      default: 
            //Serial.printf("rgSeq: %d",rgsequence);
            //Serial.println("");
            rgsequence = 0;
            break;
  }
}

void HighFrequencyOLD() { // High Frequency rate group = 5KHz
  rgsequence++;
  //if (ledState == LOW) {
  //  ledState = HIGH;
  //  blinkCount = blinkCount + 1;  // increase when LED turns on
  //} else {
  //  ledState = LOW;
  //}
  //digitalWrite(38, ledState);
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
      //Serial.println("Galil Slow Enabled");
    }
  }

  switch(rgsequence){ //Scheduled Rate Groups
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
      rgsequence = 0;
      break;
  }
}


void setup() {
  int mynum;


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

  //tft.setFrameBuffer(fb1);
  //tft.useFrameBuffer(true);

  //GPSSerial.begin(9600); 
  // Initialize the I2C port expander
  for(int i=0;i<8;i++) {
    pcf8574.pinMode(i, INPUT);
  }

  if (pcf8574.begin()){
    Serial.println("OK");
  }else{
    Serial.println("KO");
  }

  tft.begin();


  configmenu();  //setup the control menus

  // test the function encapsulation...
  mitem[0].itemtype = 0;
  mitem[0].level = 0;
  mitem[0].myfunc = &addnum;

  mynum = mitem[0].myfunc(2);
  Serial.printf("My Num %d",mynum);
  Serial.println("");

  mitem[0].myfunc = &subnum;
  
  mynum = mitem[0].myfunc(3);
  Serial.printf("My Num %d",mynum);
  Serial.println("");
  
  //auto spr = tft.createSprite(320,240,1);



  

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
 
  pinMode(readPin, INPUT);
  pinMode(readPin2, INPUT);

  pinMode(backlight_EN, OUTPUT);
 

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
  rgsequence = 0;
  servorate = 0;
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
    //Serial.print("line1");
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
    //Serial.print("line2");
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
/*
  if(recording==true  && inmotion == true){

    rawcurrent = ina219g.getCurrent_raw();
    i2s_buff.lwords[bufptr++] = (long)APC; 
    i2s_buff.lwords[bufptr++] = (long)deltaapc;
    i2s_buff.lwords[bufptr++] = (long)rawcurrent; 
    //Serial.printf("bufptr: %d, Current: %d", bufptr, rawcurrent);
    //Serial.println(""); 
    if(bufptr>=65530)
      recording = false;
  }
*/
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


// If you enable interrupts make sure to call readSingle() to clear the interrupt.
void adc0_isr() {
        adc->adc0->readSingle();
}

String mystr;
static void smartDelay(unsigned long ms)
{
  mystr = "";
  char c;
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

static void displayLatLonUTC(float val1, float val2, TinyGPSDate &d, TinyGPSTime &t)
{
    tft.setTextColor(TFT_GREEN); 
    tft.fillRect(0, 60, 240, 20, TFT_BLACK);  
    strcpy(mylat,"");
    sprintf(mylat, "%11.8f", val1);
    tft.setCursor(10,200);
    tft.print(String(val1)); 
    sprintf(mylon, "%11.8f", val2);
    tft.setCursor(10,220);
    tft.print(String(val2));

    sprintf(sz1, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    tft.setCursor(0,70);
    tft.print(sz1);
    sprintf(sz2, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    tft.setCursor(100,70);
    tft.print(sz2);
    strcpy((char *)myDate, sz1); // save for later
    strcpy((char *)myUTC, sz2); // save for later

    
    tft.setCursor(200,219);
    tft.print(gcnts);
    //sprintf(gcnts, "%6d", geiger_count*GMULT);
    //dataMessage = String(gcnts) + "," + lat + "," + lon + "," + sz1 + "," + sz2 + "\r\n";
    //recordFile(SD, filename);
}

static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.printf("*");
    Serial.printf(" ");
  }
  else
  {
    tft.print(val, prec);
    //Serial.printf("%11.8f", val);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      tft.print(" ");
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.printf(sz);
  smartDelay(0);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  if (!d.isValid())
  {
    //Serial.printf(F("********** "));
    Serial.printf("******** ");
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    Serial.printf(sz);
  }
  
  if (!t.isValid())
  {
    //Serial.printf(F("******** "));
    Serial.printf("******** ");
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serial.printf(sz);
  }

  printInt(d.age(), d.isValid(), 5);
  smartDelay(0);
}

static void printStr(const char *str, int len)
{
  int slen = strlen(str);
  //for (int i=0; i<len; ++i)
  //  Serial.printf(i<slen ? str[i] : " ");
  smartDelay(0);
}

    /**
     * Starts a new CRC8 calculation.
     * 
     * @param data      byte array
     * @param length    number of bytes
     * @return uint8_t  crc
     */

uint8_t seed = 0;
uint8_t calc(uint8_t *data, unsigned int length) {
    seed = 0;
    return update(data, length);
}

/**
 * Feed more data in the CRC calculation. calc() must
 * be called the first time, before using update()
 * multiple times.
 * 
 * @param data      byte array
 * @param length    number of bytes
 * @return uint8_t  crc
 */
uint8_t update(uint8_t *data, unsigned int length) {
    uint8_t crc = seed;
    uint8_t extract;
    uint8_t sum;

    for (unsigned int i = 0; i < length; i++) {
        extract = *data;

        for (char j = 8; j; j--) {
            sum = (crc ^ extract) & 0x01;
            crc >>= 1;
            if (sum) {
                crc ^= 0x8C;
            }
            extract >>= 1;
        }

        data++;
    }

    return crc;
}
