#pragma message "---------- BUILDING GALIL ----------"

#include "KeckACS.h"

#define CLK5K0 100
#define CLK625H0 400
#define CLK156H25 800
#define DigitalInput byte


// disable the GALIL for input --- if error too high
void doGALILError()
{
  int err;
  err = digitalRead(GALIL_ERRn);
  if (err == 0) {
    detachInterrupt(digitalPinToInterrupt(GALIL_ERRn));
    galil_err = true;
  }
}

// re-enables the GALIL for input
void chkGALILError()
{
  int err;
  err = digitalRead(GALIL_ERRn);
  if (err == 1) {
    attachInterrupt(digitalPinToInterrupt(GALIL_ERRn), doGALILError, LOW);
    galil_err = false;
  }
}

int  readGALILError(void){
  int temp;
  DigitalInput  val = pcf8574.digitalReadAll();
  temp = (int)val;
  if(temp>=127) 
    temp = temp-256;  // make it signed
  return temp;
}

volatile bool foundGalilHome = false;
void doGalilHome()
{
  foundGalilHome = true;
  Serial.println(">>> Found Galil home");
  detachInterrupt(digitalPinToInterrupt(GALIL_HOM));
}

volatile bool foundGalilIndex = false;
void doGalilIndex()
{
  foundGalilIndex = true;
  Serial.println(">>> Found Galil index");
  detachInterrupt(digitalPinToInterrupt(GALIL_IDX));
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


int GALILGo(int k){

  int remain = 0;
  int steps;
  int n = 0;

  bufptr = 0;
  
  // set the direction based on the sign of the steps
  if(mymenu[PAGE_GALIL].m[TOTAL].mvalue.mval.l >0){
    direction = CCW;
  }
  else{
    direction = CW;
  }

  steps = mymenu[PAGE_GALIL].m[TOTAL].mvalue.mval.l;
  Serial.printf("steps: %d", steps);
  Serial.println("");
  nsteps = (abs)(steps);

  Serial.printf("APC= %d, steps: %d, nsteps: %d, n= %d, r= %d, Dir= %d", APC, steps, nsteps,  n, remain, direction);
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

  attachInterrupt(digitalPinToInterrupt(GALIL_HOM), doGalilHome, LOW);
  attachInterrupt(digitalPinToInterrupt(GALIL_IDX), doGalilIndex, HIGH);

  foundGalilHome = false;
  //Serial.println("GALIL Home Command");
  while(foundGalilHome == false && (digitalRead(GALIL_HOM)==1)){ // only excute if not home
    GALILpulse(1, CCW, CLK156H25);//CLK5K0
  }
  //delay(10);
  
  foundGalilIndex = false;
  while(foundGalilIndex == false && (digitalRead(GALIL_IDX)==0)){ // only excute if not index
  //while(1){
    GALILpulse(1, CW, CLK156H25); //CLK156H25
   //delay(100);
  }
  delay(100);// WAIT FOR ROTOR TO SETTLE OUT BEFORE ZERO OF APC
  MTRPUL = 0;   //reset the MTRPUL register
  APC = 0;      // reset the APC
  mymenu[PAGE_GALIL].m[APCREG].mvalue.mval.l = APC;
  DrawMenus(pagenum);
  return(0);
}

int GALILMax(int i){

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

  Serial.println("GALIL Clear Command");
  GALIL_Count = 0;
  mymenu[1].m[1].mvalue.mval.l = GALIL_Count;
  DrawMenus(pagenum);
  return(0);
}

void GALIL_Slow(void){
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
        if(abs(myerror)>=2){
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
          mymenu[PAGE_GALIL].m[ELAPSED].mvalue.mval.l = ElapsedTime;
          write_file = true;
        }
      }
    }
  }
}

#pragma message "---------- BUILDING GALIL - DONE ----------"
