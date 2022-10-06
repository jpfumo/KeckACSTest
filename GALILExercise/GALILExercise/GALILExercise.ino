#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "PCF8574.h"

// Pin definitions
#define GALIL_RST       17
#define GALIL_CLK       0
#define GALIL_DEC       21
#define GALIL_INC       22
#define GALIL_IDX       39
#define GALIL_HOM       25
#define GALIL_B         24
#define GALIL_A         23
#define GALIL_ERRn      20

#define PWM_DISABLE_MOT0 3

#define CLK5K0 100
#define CLK625H0 400
#define CLK156H25 800

// Set i2c address
PCF8574 pcf8574(0x38); //pcf8574A addr = 0x70

uint32_t steps = 0;
int32_t APC, oldAPC;

typedef enum {
  CW, 
  CCW
  } dtype_t;

dtype_t direction = CW;

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  while (millis() - start < ms) {};
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
    APC++;
    //Serial.printf("A CW %d\n", APC);
  } else if (r_sw == 0 || r_sw == 3) {
    //CCW
    APC--;
    //Serial.printf("A CCW %d\n", APC);
  }
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
    APC--;
    //Serial.printf("B CCW %d\n", APC);
  } else if (r_sw == 0 || r_sw == 3) {
    //CCW
    APC++;
    //Serial.printf("B CW %d\n", APC);
  }
}



void GALILpulse(int steps, int direction, int pulsedelay) {
  int i;
  if (direction == CW) { // CW = 0, positive = CW
    for (i = 0; i < steps; i++) {
      digitalWrite(GALIL_DEC, LOW);
      delayMicroseconds(pulsedelay);
      digitalWrite(GALIL_DEC, HIGH);
      delayMicroseconds(pulsedelay);
    }
  } else {
    for (i = 0; i < steps; i++) { // CW = 1, negative = CCW
      digitalWrite(GALIL_INC, LOW);
      delayMicroseconds(pulsedelay);
      digitalWrite(GALIL_INC, HIGH);
      delayMicroseconds(pulsedelay);
    }
  }
}

int32_t readGALILError(void) {
  
  int8_t temp;
  PCF8574::DigitalInput val;

  val = pcf8574.digitalReadAll();
  
  //temp = (int8_t) val;
  temp = (int8_t) ((val.p7 << 7) + (val.p6 << 6) + (val.p5 << 5) + (val.p4 << 4) + (val.p3 << 3) + (val.p2 << 2) + (val.p1 << 1) + (val.p0));
  //if (temp >= 127)
  //  temp = temp - 256; // make it signed
  return temp;

}

bool GALIL_Slow(void) {
  
  int32_t galil_error;

  /* If we still have steps to go.... */
  if (steps > 0) {

    if (direction == CW) {

      Serial.printf("Moving %d steps CW @ %d, ", steps, APC);

      digitalWrite(GALIL_INC, LOW);
      delayMicroseconds(10);
      
      digitalWrite(GALIL_INC, HIGH);
      delayMicroseconds(10);
      
    } else {

      Serial.printf("Moving %d steps CCW @ %d, ", steps, APC);

      digitalWrite(GALIL_DEC, LOW);
      delayMicroseconds(10);
      
      digitalWrite(GALIL_DEC, HIGH);
      delayMicroseconds(10);
    }

    steps -= 1;
  }


  /* If we don't think we have any steps left to send, check the Galil error and walk it in the final distance */
  if (steps == 0) {
    
    // Integrator---check to see in error term is <=2
    galil_error = readGALILError();

    if ((galil_error > 1) && (direction == CW)) {
      
      /* Overshot CW, walk it back */
      Serial.printf("overshot CW by %d\n", galil_error);
      direction = CCW;
      steps++;        

    } else if ((galil_error < -1) && (direction == CW)) {          
      
      /* Undershot CW, keep going same direction */
      Serial.printf("undershot CW by %d\n", galil_error);
      steps++;        

    } else if ((galil_error < -1) && (direction == CCW)) {
      
      /* Overshot CCW, walk it back */
      Serial.printf("overshot CCW by %d\n", galil_error);
      direction = CW;
      steps++;     
      
    } else if ((galil_error > 1) && (direction == CCW)) {
      
      /* Undershot CCW, keep going same direction */
      Serial.printf("undershot CW by %d\n", galil_error);
      steps++;     
      
    } else {

      /* Move is complete! */ 
      Serial.printf("move to %d is complete\n", APC);
      return true;
    }
    
  } else {
    Serial.printf("%d steps to go.\n", steps);
  }

  return false;
 
}




void setup() {

  Serial.begin(115200);


  // Initialize the I2C port expander
  for (int i = 0; i < 8; i++) {
    pcf8574.pinMode(i, INPUT);
  }

  if (pcf8574.begin()) {
    Serial.println(">>> PCF8574 OK");
  } else {
    Serial.println(">>> PCH8574 NOT OK");
  }

  
  Serial.println("Pulse train");
  
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

  smartDelay(100);
  pinMode(PWM_DISABLE_MOT0, OUTPUT);
  digitalWrite(PWM_DISABLE_MOT0, LOW);

  attachInterrupt(digitalPinToInterrupt(GALIL_A), doStrutEncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(GALIL_B), doStrutEncoderB, CHANGE);

  oldAPC = APC;

  delay(1000);
}

#define MOVESIZE 10
#define MOVEDIR CCW

void loop() {
  static uint32_t t;
  static uint32_t count;
  uint8_t err;

  t = millis();
  static bool first = false;

  /*
  GALILpulse(MOVESIZE, CCW, CLK156H25);//CLK5K0
  count += MOVESIZE;
  
  //delay(1000);

  err = readGALILError();
  
  if (oldAPC != APC) {
    oldAPC = APC;
    
    if (MOVEDIR == CW) 
      Serial.printf("Pulse %d: t = %d  APC = %d (delta %d, err %d)\n", count, t, APC, count-APC, err);
    else
      Serial.printf("Pulse %d: t = %d  APC = %d (delta %d, err %d)\n", count, t, APC, count-(-APC), err);
  }

  delay(500);
  */

  if (GALIL_Slow()) {

    Serial.printf("\n\nWaiting to do next move...\n");
    
    if (first) {
      delay(10000);      
    }
    first = true;

    direction = CW;
    steps = 100;
  } else {
    delay(10);
  }

  

}
