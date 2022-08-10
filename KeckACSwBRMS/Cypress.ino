#pragma message "---------- BUILDING CYPRESS ----------"

#include "KeckACS.h"

void CypressWrite(byte xbuf[], int bufsize) {
  byte c;

  SPI1.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE2));
 
  digitalWrite(CypressCSPin,LOW);
  for(int i = 0; i<bufsize;i++){
    c = SPI1.transfer(xbuf[i]);

    #ifdef DEBUG_CYPRESS
    Serial.printf("%d ",c);
    #endif 
    
    rxMessage.buf[i] = c;
  }

  digitalWrite(CypressCSPin,HIGH);
  SPI.endTransaction();

  #ifdef DEBUG_CYPRESS
  for(int i = 0; i<bufsize;i++){
    Serial.printf("%d ", rxMessage.buf[i]);
  }
  Serial.println("");
  #endif
}

void FillinCypressResponse(){

  uint32_t version, position;
  version = rxMessage.msg.version0<<16 | rxMessage.msg.version1<<8 | rxMessage.msg.version2;
  position = 0;
  position = (uint32_t)(rxMessage.buf[13]) | (rxMessage.buf[14]<<8) | (rxMessage.buf[15]<<16) | (rxMessage.buf[16]<<24);
  //Serial.println(ltos(position, buf, 10));
  //Serial.printf("p: %010d", position);
  //Serial.println("");
  
  mymenu[PAGE_CYPREPLY].m[0].mvalue.mval.b = rxMessage.msg.checksum;
  mymenu[PAGE_CYPREPLY].m[1].mvalue.mval.b = version;
  mymenu[PAGE_CYPREPLY].m[2].mvalue.mval.b = rxMessage.msg.size;
  mymenu[PAGE_CYPREPLY].m[3].mvalue.mval.b = rxMessage.msg.opcode;
  mymenu[PAGE_CYPREPLY].m[4].mvalue.mval.b = rxMessage.msg.state;
  mymenu[PAGE_CYPREPLY].m[5].mvalue.mval.b = rxMessage.msg.fault;
  mymenu[PAGE_CYPREPLY].m[6].mvalue.mval.b = rxMessage.msg.sequence;
  mymenu[PAGE_CYPREPLY].m[7].mvalue.mval.w = rxMessage.msg.checksum_errors;
  mymenu[PAGE_CYPREPLY].m[8].mvalue.mval.w = rxMessage.msg.current;
  mymenu[PAGE_CYPREPLY].m[9].mvalue.mval.l = (uint32_t)position;
  mymenu[PAGE_CYPREPLY].m[10].mvalue.mval.f = rxMessage.msg.pwm;
}

int CypressMax(int i){

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

  Serial.println("Cypress Clear Command");
  Cypress_Count = 0;
  mymenu[2].m[1].mvalue.mval.l = Cypress_Count;
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

  #ifdef DEBUG_CYPRESS
  Serial.println("Cypress Init");
  Serial.printf("MSG size: %d\n", 19);
  #endif
  
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

  #ifdef DEBUG_CYPRESS
  Serial.printf("x: ");
  for(i=0; i<19; i++){
    Serial.printf("%d ",txMessage.buf[i]);
  }
  Serial.println("");
  #endif
  
  //write configuration to the Cypress over the SPI
  CypressWrite(txMessage.buf, 19); //sizeof(txMessage.buf));

}


void CypressStatus(void){
  int checksum = 0;
  int i = 0;

  // clear out the buffer
  for (i = 0; i < MAX_MESSAGE_SIZE; i++)
    txMessage.buf[i] = 0; 
    
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

  #ifdef DEBUG_CYPRESS
  Serial.println("Cypress Status");

  Serial.printf("s: ");
  for(i=0; i<MAX_MESSAGE_SIZE; i++){
    Serial.printf("%d ",txMessage.buf[i]);
  }
  Serial.println("");
  #endif

  //write configuration to the Cypress over the SPI
  CypressWrite(txMessage.buf, MAX_MESSAGE_SIZE); //sizeof(txMessage.buf));
}

volatile bool foundCypressIndex = false;
void doCypressIndex()
{
  foundCypressIndex = true;
  Serial.println(">>> Found Cypress index");
  detachInterrupt(digitalPinToInterrupt(Cypress_IDX));
}

volatile bool foundCypressHome = false;
void doCypressHome()
{
  foundCypressHome = true;
  Serial.println(">>> Found Cypress home");
  detachInterrupt(digitalPinToInterrupt(Cypress_HOM));
}

int CypressHome(int i){

  #ifdef DEBUG_CYPRESS
  Serial.println("Cypress Home Command");
  #endif  

  attachInterrupt(digitalPinToInterrupt(Cypress_HOM), doCypressHome, LOW);
  attachInterrupt(digitalPinToInterrupt(Cypress_IDX), doCypressIndex, HIGH);

  foundCypressHome = false;
  while(foundCypressHome == false && (digitalRead(Cypress_HOM)==1)){ // only execute if not home
    CypressCCW(1000);
  }
  delay(10);
  
  foundCypressIndex = false;
  while(foundCypressIndex == false && (digitalRead(Cypress_IDX)==0)){ // only execute if not index
    CypressCW(100);
  }
  delay(10);// WAIT FOR ROTOR TO SETTLE OUT BEFORE ZERO OF APC
  
  APC = 0;      // reset the APC
  mymenu[PAGE_CYPRESS].m[APCREG].mvalue.mval.l = APC;
  DrawMenus(pagenum);
  return(0);
}

int CypressGo(int x){
  long TimeIn, TimeOut, ElapsedTime;
  
  TimeIn = micros();
  Serial.printf("TimeIn: %d ",TimeIn);
  Serial.println("");
  CypressPulse(mymenu[PAGE_CYPRESS].m[TOTAL].mvalue.mval.l, -1,0); // need to fix this....
  TimeOut = micros();
  Serial.printf("TimeOut: %d ",TimeOut);
  Serial.println("");
  ElapsedTime = TimeOut - TimeIn;
  Serial.printf("TimeElapsed: %d ",ElapsedTime);
  Serial.println("");
  mymenu[PAGE_CYPRESS].m[ELAPSED].mvalue.mval.l = ElapsedTime;

  return 0;
}



#pragma message "---------- BUILDING CYPRESS - DONE ----------"
