#pragma message "---------- BUILDING CYPRESS ----------"

#include "KeckACS.h"

/* ----------------------------------------------------------------------------------------------------------- */
bool CypressWrite(void) {

  uint8_t i, checksum, txlen, msglen;

  bool debug = false;
  //bool debug = true;

  /* Use the size of the rxMessage, which may be longer than the txMessage! */
  txlen = sizeof(rxMessage.msg);

  /* Checksum the message */
  msglen = txMessage.overlay.size;
  
  txMessage.buf[0] = 0;  // Zero out the checksum, in case it's already set
  for (i = 0, checksum = 0; i < msglen; i++)
    checksum += txMessage.buf[i]; 
    
  /* Take the 2's complement of the sum and put it back in the message */
  txMessage.overlay.checksum = ~checksum + 1;    

  if (debug) {
    
    /* Show the outgoing message buffer */
    Serial.printf("OUT >>> ");
    for (i = 0; i < msglen; i++) {
      Serial.printf("%02X ", txMessage.buf[i]);
    }
    Serial.println("");
  }

  /* The incoming bytes were written into the outgoing buffer, so copy them over to inbuf */
  bzero(txMessageCopy.buf, sizeof(txMessageCopy.buf));
  bcopy(txMessage.buf, txMessageCopy.buf, txlen);
  
  /* Begin the transfer */
  //SPI1.beginTransaction(SPISettings(3500000, MSBFIRST, SPI_MODE2));
  SPI1.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE2));

  /* Assert the Cypress chip select */
  digitalWrite(CypressCSPin, LOW);

  /* Transfer the entire buffer in one go. */
  SPI1.transfer(txMessageCopy.buf, txlen);

  /* Deassert the chip select */
  digitalWrite(CypressCSPin, HIGH);

  /* SPI transaction is done */
  SPI.endTransaction();

  /* The incoming bytes were written into the outgoing buffer, so copy them over to inbuf */
  bcopy(txMessageCopy.buf, rxMessage.buf, txlen);

  if (debug) {

    /* Show the response */
    Serial.printf("IN  >>> ");
    for (i = 0; i < txlen; i++) {
      Serial.printf("%02X ", rxMessage.buf[i]);
    }
    Serial.println("");
  }

  /* Verify the checksum */
  for (i = 0, checksum = 0; i < txlen; i++)  
    checksum += rxMessage.buf[i]; 
    
  if (checksum != 0) {    
    
    /* Show the response */
    Serial.printf("!!! Checksum failure: ");
    for (i = 0; i < txlen; i++) {
      Serial.printf("%02X ", rxMessage.buf[i]);
    }
    Serial.println("");
    
    return false;
    
  } else {

    /* The response is ALWAYS a status message, decode the fields into their globals */
    CypressPosition = rxMessage.msg.position;
    CypressState = rxMessage.msg.state;
    CypressPWM = rxMessage.msg.pwm;
    CypressCurrent = rxMessage.msg.current;
    
    mymenu[PAGE_CYPREPLY].m[0].mvalue.mval.b = rxMessage.msg.checksum;
    mymenu[PAGE_CYPREPLY].m[1].mvalue.mval.b = (rxMessage.msg.version0 << 16) | (rxMessage.msg.version1 << 8) | rxMessage.msg.version2;
    mymenu[PAGE_CYPREPLY].m[2].mvalue.mval.b = rxMessage.msg.size;
    mymenu[PAGE_CYPREPLY].m[3].mvalue.mval.b = rxMessage.msg.opcode;
    mymenu[PAGE_CYPREPLY].m[4].mvalue.mval.b = CypressState;
    mymenu[PAGE_CYPREPLY].m[5].mvalue.mval.b = rxMessage.msg.fault;
    mymenu[PAGE_CYPREPLY].m[6].mvalue.mval.b = rxMessage.msg.sequence;
    mymenu[PAGE_CYPREPLY].m[7].mvalue.mval.w = rxMessage.msg.checksum_errors;
    mymenu[PAGE_CYPREPLY].m[8].mvalue.mval.w = rxMessage.msg.current;
    mymenu[PAGE_CYPREPLY].m[9].mvalue.mval.l = CypressPosition;
    mymenu[PAGE_CYPREPLY].m[10].mvalue.mval.f = CypressPWM;
    
  }

  /* Checksum was good! */
  return true;  
}


/* ----------------------------------------------------------------------------------------------------------- */
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


/* ----------------------------------------------------------------------------------------------------------- */
int CypressClear(int i){

  Serial.println("Cypress Clear Command");
  Cypress_Count = 0;
  mymenu[2].m[1].mvalue.mval.l = Cypress_Count;
  DrawMenus(pagenum);
  return(0);
}


/* ----------------------------------------------------------------------------------------------------------- */
void CypressPulse(long steps, int direction, int pulsedelay) {
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
  
  ///Serial.printf("x: ");
  ///for(i=0; i<19; i++){
  ///  Serial.printf("%d ",txMessage.buf[i]);
  ///}
  ///Serial.println("");
  
  //write SetPosition to the Cypress over the SPI
  CypressWrite(); //txMessage.buf, 12); //sizeof(txMessage.buf));

}


/* ----------------------------------------------------------------------------------------------------------- */
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
  CypressWrite();//txMessage.buf, 12); //sizeof(txMessage.buf));

}


/* ----------------------------------------------------------------------------------------------------------- */
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
  CypressWrite(); //txMessage.buf, 12); //sizeof(txMessage.buf));

}






/* ----------------------------------------------------------------------------------------------------------- */
volatile bool foundCypressIndex = false;
void doCypressIndex()
{
  foundCypressIndex = true;
  Serial.println(">>> Found Cypress index");
  detachInterrupt(digitalPinToInterrupt(Cypress_IDX));
}


/* ----------------------------------------------------------------------------------------------------------- */
volatile bool foundCypressHome = false;
void doCypressHome()
{
  foundCypressHome = true;
  Serial.println(">>> Found Cypress home");
  detachInterrupt(digitalPinToInterrupt(Cypress_HOM));
}


/* ----------------------------------------------------------------------------------------------------------- */
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


/* ----------------------------------------------------------------------------------------------------------- */
void CypressMove(int32_t steps) {
  
  int32_t dest;
  uint8_t message_size = 0;
  bool result;

  // Where are we going?
  CypressDestination = CypressPosition + steps;
  CypressPIDEnable = 1;

  Serial.printf("Cypress move %d steps (from %d to %d)\n", steps, CypressPosition, CypressDestination);

  /* Start moving with a Status message */
  bzero(&txMessage, sizeof(txMessage));
  message_size = sizeof(txMessage_status_t);
    
  txMessage.status.size = message_size;
  txMessage.status.opcode = opStatus;
  txMessage.status.enable = CypressPIDEnable;
  txMessage.status.setpoint = CypressDestination;

  // Send the request to the Cypress device
  result = CypressWrite(); 

  if (!result) {
    Serial.printf(">>> Start move failure!\n");
  }

}

/* ----------------------------------------------------------------------------------------------------------- */
void CypressMoveAbsolute(int32_t pos) {

  int32_t dest;
  uint8_t message_size = 0;
  bool result;

  // Where are we going?
  CypressDestination = pos;
  CypressPIDEnable = 1;

  Serial.printf("Cypress move from %d to %d\n", CypressPosition, CypressDestination);

  /* Start moving with a Status message */
  bzero(&txMessage, sizeof(txMessage));
  message_size = sizeof(txMessage_status_t);
    
  txMessage.status.size = message_size;
  txMessage.status.opcode = opStatus;
  txMessage.status.enable = CypressPIDEnable;
  txMessage.status.setpoint = CypressDestination;

  // Send the request to the Cypress device
  result = CypressWrite(); 

  if (!result) {
    Serial.printf(">>> Start move failure!\n");
  }

}



/* ----------------------------------------------------------------------------------------------------------- */
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


/* ----------------------------------------------------------------------------------------------------------- */
void CypressStop(void) {

  CypressEnable = false;
  CypressPIDEnable = 0;
  CypressReinit = true;
}


/* ----------------------------------------------------------------------------------------------------------- */
void CypressStatus(void) {
  
  uint8_t checksum, calcsum = 0;
  uint8_t i = 0;
  int32_t pos;
  uint8_t message_size = 0;
  bool result = false;

  /* Send a status message */
  bzero(&txMessage, sizeof(txMessage));
  message_size = sizeof(txMessage_status_t);
    
  // fill in the status message
  txMessage.status.size = message_size;
  txMessage.status.opcode = opStatus;
  txMessage.status.enable = CypressPIDEnable;
  txMessage.status.setpoint = CypressDestination;

  // write status message to the Cypress over the SPI
  result = CypressWrite(); 

  if (!result) {
    //Serial.printf(">>> Status failure!\n");
  }
  
}


/* ----------------------------------------------------------------------------------------------------------- */
void CypressSetEnable(void) {
  
  /* Set the enable flag */
  CypressEnable = true;
}


/* ----------------------------------------------------------------------------------------------------------- */
void CypressInit(void) {
  
  uint8_t checksum = 0;
  uint8_t calcsum = 0;
  uint8_t i = 0;
  uint8_t message_size = 0;
  bool result = false;

  /* Send the initial configuration message */
  CypressSequence = 0x44;

  bzero(&txMessage, sizeof(txMessage));
  message_size = sizeof(txMessage_config_t);
  Serial.printf(">>> Configuring the Cypress (%d bytes)\n", message_size);

  txMessage.config.size = message_size;
  txMessage.config.opcode = opConfig;
  txMessage.config.sequence = CypressSequence;
  txMessage.config.Kp = CYPRESS_KP;
  txMessage.config.Ki = CYPRESS_KI;
  txMessage.config.Kd = CYPRESS_KD;
  txMessage.config.limit_Total = 100;
  txMessage.config.limit_ITerm = 100;
  txMessage.config.effsetdelta = 25;

  CypressPIDEnable = 0;
  CypressDestination = 0;

  // Write configuration to the Cypress over the SPI, do it twice to pick up the config state change
  result = CypressWrite(); 
  delay(300);
  result = CypressWrite(); 

  if (result) {

    /* Turn on the master enable if it reports configured */
    if (rxMessage.msg.state == 2) {
      Serial.printf("*** Cypress init success!\n");      
    } else {
      Serial.printf("!!! Cypress did not init, state = %d\n", rxMessage.msg.state);

    }
  } else {
    Serial.printf("!!! Cypress init failure\n");
  }

  /* Wait a moment before sending another message to the Cypress */
  delay(1000);

  /* Zero the encoder */
  Serial.printf(">>> Zeroing out Cypress encoder\n");

  bzero(&txMessage, sizeof(txMessage));
  message_size = sizeof(txMessage_setenc_t);

  txMessage.setenc.size = message_size;
  txMessage.setenc.opcode = opSetEnc;
  txMessage.setenc.setpoint = 0;

  // Send to Cypress
  result = CypressWrite(); 

  if (result) {
    Serial.printf("*** Cypress zeroing success\n");
  } else {
    Serial.printf("!!! Cypress zeroing failure\n");
  }
  
}


#pragma message "---------- BUILDING CYPRESS - DONE ----------"
