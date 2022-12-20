#pragma message "---------- BUILDING GALIL ----------"

#include "KeckACS.h"

#define CLK5K0 100
#define CLK625H0 400
#define CLK156H25 800
#define DigitalInput byte


// disable the GALIL for input --- if error too high
void doGALILError(void)
{
  int err;
  err = digitalRead(GALIL_ERRn);
  if (err == 0) {
    detachInterrupt(digitalPinToInterrupt(GALIL_ERRn));
    galil_err = true;
  }
}

// re-enables the GALIL for input
int chkGALILError(void)
{
  int err;
  err = digitalRead(GALIL_ERRn);
  if(err == 1) // invert, error when signal is low (not)
    err = 0;
  else
    err = 1;
  return(err);
}

int  readGALILError(void) {
  int temp;
  DigitalInput  val = pcf8574.digitalReadAll();
  temp = (int)val;
  if (temp >= 127)
    temp = temp - 256; // make it signed
  return temp;
}

volatile bool foundGalilHome = false;
void doGalilHome(void)
{
  foundGalilHome = true;
  Serial.println(">>> Found Galil home");
  detachInterrupt(digitalPinToInterrupt(GALIL_HOM));
}

volatile bool foundGalilIndex = false;
void doGalilIndex(void)
{
  foundGalilIndex = true;
  Serial.println(">>> Found Galil index");
  detachInterrupt(digitalPinToInterrupt(GALIL_IDX));
}

uint16_t readGALILcurrent(void) {
  //shuntvoltage = ina219g.getShuntVoltage_mV();
  //busvoltage = ina219g.getBusVoltage_V();
  //current_mA = ina219g.getCurrent_mA();
  rawcurrent = ina219g.getCurrent_raw();
  //power_mW = ina219g.getPower_mW();
  //loadvoltage = busvoltage + (shuntvoltage / 1000);
  Serial.print("Current:       "); Serial.print(rawcurrent); Serial.println(" mA");
  return (current_mA);
}


int GALILGo(int k) {

  int remain = 0;
  int steps;
  int n = 0;

  bufptr = 0;

  // set the direction based on the sign of the steps
  //if (mymenu[PAGE_GALIL].m[TOTAL].mvalue.mval.l > 0) {
  //  direction = CCW;
  //}
  //else {
  //  direction = CW;
  //}

  steps = mymenu[PAGE_GALIL].m[TOTAL].mvalue.mval.l;
  NEWAPC = APC + steps; // calculate the new APC value
  //Serial.printf("steps: %d", steps);
  //Serial.println("");
  //nsteps = (abs)(steps);
  GalilStartTime = micros();
  

  Serial.printf("APC: %d,   steps: %d,  r= %d", APC, steps); 
  Serial.println("");

  //galil_err = false; // enable the motion
  inmotion = true;
  Galil_SlowFlag = false;
  write_file = false;
  GalilEnable = true;
  LastRecord = false;
  return (0);

}

void GALILpulse(int steps, int direction, int pulsedelay) {
  int i;
  if (direction == CW) { // CW = 0, positive = CW
    for (i = 0; i < steps; i++) {
      digitalWrite(GALIL_DEC, LOW);
      delayMicroseconds(pulsedelay);
      digitalWrite(GALIL_DEC, HIGH);
      delayMicroseconds(pulsedelay);
      
      if (recording == true) {
        SDAppendMotionGalil(APC, rawcurrent);
      }
      
    }
  } else {
    for (i = 0; i < steps; i++) { // CW = 1, negative = CCW
      digitalWrite(GALIL_INC, LOW);
      delayMicroseconds(pulsedelay);
      digitalWrite(GALIL_INC, HIGH);
      delayMicroseconds(pulsedelay);
      
      if (recording == true) {
        SDAppendMotionGalil(APC, rawcurrent);
      }
      
    }
  }
}

void GALILReset(void) {
  digitalWrite(GALIL_RST, HIGH);
  delay(50);
  digitalWrite(GALIL_RST, LOW);
  delay(50);
  digitalWrite(GALIL_RST, HIGH);
  delay(50);

}

void GALILHold(void) {
  digitalWrite(GALIL_RST, HIGH);
  delay(50);
  digitalWrite(GALIL_RST, LOW);
  delay(50);
}

void GALILRelease(void) {
  digitalWrite(GALIL_RST, HIGH);
  delay(50);
}

int GALILHome(int i) {

// Just Clear the APC
/*
  attachInterrupt(digitalPinToInterrupt(GALIL_HOM), doGalilHome, LOW);
  attachInterrupt(digitalPinToInterrupt(GALIL_IDX), doGalilIndex, HIGH);

  foundGalilHome = false;
  //Serial.println("GALIL Home Command");
  while (foundGalilHome == false && (digitalRead(GALIL_HOM) == 1)) { // only excute if not home
    GALILpulse(1, CCW, CLK156H25);//CLK5K0
  }
  //delay(10);

  foundGalilIndex = false;
  while (foundGalilIndex == false && (digitalRead(GALIL_IDX) == 0)) { // only excute if not index
    //while(1){
    GALILpulse(1, CW, CLK156H25); //CLK156H25
    //delay(100);
  }
  delay(100);// WAIT FOR ROTOR TO SETTLE OUT BEFORE ZERO OF APC
  */
  leds[0] = CRGB(50, 0, 0);
  FastLED.show();
  MTRPUL = 0;   //reset the MTRPUL register
  APC = 0;      // reset the APC
  mymenu[PAGE_GALIL].m[APCREG].mvalue.mval.l = APC;
  DrawMenus(pagenum);
  return (0);
}

int GALILMax(int i) {

  GALIL_Count = GALIL_MAX_STEP;
  Serial.println("GALIL Max Command");
  Serial.printf("%d", GALIL_Count);
  Serial.println("");
  mymenu[1].m[1].vsize = 3; //long
  mymenu[1].m[1].mvalue.mval.l = (long)GALIL_Count;
  DrawMenus(pagenum);
  return (0);
}

int GALILClear(int i) {

  Serial.println("GALIL Clear Command");
  GALIL_Count = 0;
  mymenu[1].m[1].mvalue.mval.l = GALIL_Count;
  DrawMenus(pagenum);
  return (0);
}

void GALIL_Slow(void) {
  
  int galil_error;
  float ElapsedTime_ms;

  if (Galil_SlowFlag == true) {

    if (galil_err == false) {

      /* If we still have steps to go.... */
      if (nsteps > 0) {

        if (direction == CW) {
          #ifdef DEBUG_GALIL
          Serial.printf("Moving %d steps CW @ %d, ", nsteps, APC);
          #endif
          
          digitalWrite(GALIL_INC, LOW);
          delayMicroseconds(10);
          
          digitalWrite(GALIL_INC, HIGH);
          delayMicroseconds(10);
          
        } else {

          #ifdef DEBUG_GALIL
          Serial.printf("Moving %d steps CCW @ %d, ", nsteps, APC);
          #endif

          digitalWrite(GALIL_DEC, LOW);
          delayMicroseconds(10);
          
          digitalWrite(GALIL_DEC, HIGH);
          delayMicroseconds(10);
        }

        nsteps -= 1;
      }

      /* If we don't think we have any steps left to send, check the Galil error and walk it in the final distance */
      if (nsteps == 0) {
        
        // Integrator---check to see in error term is <=2
        galil_error = readGALILError();

        if ((galil_error > 1) && (direction == CW)) {
          
          /* Overshot CW, walk it back */
          #ifdef DEBUG_GALIL
          Serial.printf("overshot CW by %d\n", galil_error);
          #endif

          direction = CCW;
          nsteps++;        

        } else if ((galil_error < -1) && (direction == CW)) {          
          
          /* Undershot CW, keep going same direction */
          #ifdef DEBUG_GALIL
          Serial.printf("undershot CW by %d\n", galil_error);
          #endif
          
          nsteps++;        

        } else if ((galil_error < -1) && (direction == CCW)) {
          
          /* Overshot CCW, walk it back */
          #ifdef DEBUG_GALIL
          Serial.printf("overshot CCW by %d\n", galil_error);
          #endif
          
          direction = CW;
          nsteps++;     
          
        } else if ((galil_error > 1) && (direction == CCW)) {
          
          /* Undershot CCW, keep going same direction */
          #ifdef DEBUG_GALIL
          Serial.printf("undershot CW by %d\n", galil_error);
          #endif
          
          nsteps++;     
          
        } else {

          /* Move is complete! */ 
          inmotion = false;
          Galil_SlowFlag = false; // disable the galil_slow call
          
          GalilEnable = false; // Stop the BRMS from doing Galil ops
          
          GalilEndTime = micros();
          ElapsedTime = GalilEndTime - GalilStartTime;
          mymenu[PAGE_GALIL].m[ELAPSED].mvalue.mval.l = ElapsedTime;
          Serial.printf("move to %d is complete in %0.1f us\n", APC, ElapsedTime);

          SDSetTimes(GalilStartTime, GalilEndTime);
          
          /* Add 100ms of extra recording to the data */
          recording_oversample_time = millis() + 100;
          Serial.printf(">>> Starting oversample period at %d ms.\n", time_now);
          
          write_file = true;

        }
        
      } else {
        #ifdef DEBUG_GALIL
        Serial.printf("%d steps to go.\n", nsteps);
        #endif        
      }
    } else {
        Serial.printf("GALIL ERROR\n");
     
    }
  }
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


#pragma message "---------- BUILDING GALIL - DONE ----------"
