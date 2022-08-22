#pragma message "---------- BUILDING CONTROLS ----------"

#include "KeckACS.h"



/* =========================================================================================================== 
 * SERIAL PORT CLI / CONTROL 
 * 
 *  Based on: https://github.com/ppedro74/Arduino-SerialCommands
 *
  =========================================================================================================== */


/* ----------------------------------------------------------------------------------------------------------- */
void cmd_unrecognized(SerialCommands* sender, const char* cmd) {

  sender->GetSerial()->print("ERROR: Unrecognized command [");
  sender->GetSerial()->print(cmd);
  sender->GetSerial()->println("]");
}


/* ----------------------------------------------------------------------------------------------------------- */
void cmd_help(SerialCommands* sender) {

  sender->GetSerial()->println("");
  sender->GetSerial()->println("General commands are: ");
  sender->GetSerial()->println("  CMD   PARAMS       Description");
  sender->GetSerial()->println("  help  (none)       Display this help message");
  sender->GetSerial()->println("  w     (none)       Test writing to the SD card");
  sender->GetSerial()->println("");
  sender->GetSerial()->println("Galil control commands are: ");
  sender->GetSerial()->println("  CMD   PARAMS       Description");
  sender->GetSerial()->println("  gh    (none)       Home the actuator under Galil control");
  sender->GetSerial()->println("  gm    delta  [r]   Move the actuator under Galil control by the indicated delta value, specify r to record to SD card");
  sender->GetSerial()->println("");
  sender->GetSerial()->println("Cypress control commands are: ");
  sender->GetSerial()->println("  CMD   PARAMS       Description");
  sender->GetSerial()->println("  ch    (none)       Home the actuator under Cypress control     [TBD]");
  sender->GetSerial()->println("  cm    delta  [r]   Move the actuator under Cypress control by the indicated delta value, specify r to record to SD card");
  sender->GetSerial()->println("  ca    pos    [r]   Send the Cypress to an absolute position, specify r to record to SD card");
  sender->GetSerial()->println("  cs    (none)       Stop the Cypress device and reinitialize it");
  sender->GetSerial()->println("");

}
SerialCommand cmd_help_("help", cmd_help);


/* ----------------------------------------------------------------------------------------------------------- */
void cmd_hello(SerialCommands* sender) {
  char *p1, *p2, *p3, *p4;

  //Do not use Serial.Print!
  //Use sender->GetSerial this allows sharing the callback method with multiple Serial Ports

  p1 = sender->Next();
  p2 = sender->Next();
  p3 = sender->Next();
  p4 = sender->Next();

  sender->GetSerial()->printf("hello %s %s %s %s\n", p1, p2, p3, p4);
}
SerialCommand cmd_hello_("hello", cmd_hello);


/* ----------------------------------------------------------------------------------------------------------- */
void cmd_stop(SerialCommands* sender) {
  sender->GetSerial()->println("STOP");
}
SerialCommand cmd_stop_("s", cmd_stop);


/* ----------------------------------------------------------------------------------------------------------- */
void cmd_galil_move(SerialCommands* sender) {

  int delta;
  bool record = false;
  char *p_delta;
  char *p_record;

  /* Get the parameters from the line of text */
  p_delta = sender->Next();
  p_record = sender->Next();

  /* Convert the delta into an integer, watch out for null values! */
  if ((p_delta == NULL) || (sscanf(p_delta, "%d", &delta) == 0)) {
    sender->GetSerial()->println("Error: gm command requires a numeric delta value");
    return;
  }

  /* Moves can only be so large */
  if ((delta > 2000) || (delta < -2000)) {
    sender->GetSerial()->println("Error: gm command delta must be no more than +/- 2000 counts");
    return;    
  }

  /* Look for the recording flag */
  if (p_record == NULL) {
    record = false;    
  } else if (p_record[0] == 'r') {
    record = true;
  }
  
  if (record) {
    sender->GetSerial()->printf(">>> Galil move %d counts (recorded)\n", delta);
    recording = true;
  } else {
    sender->GetSerial()->printf(">>> Galil move %d counts (not recorded)\n", delta);
    recording = false;
  }

  /* Now do the actual move */
  GalilEnable = true;

  // Show the Galil status menu
  pagenum = PAGE_GALIL;
  DrawMenus(PAGE_GALIL);

  /* Set the menu field for step count */
  mymenu[PAGE_GALIL].m[TOTAL].mvalue.mval.l = delta;
  
  GALILGo(0);

  
}
SerialCommand cmd_galil_move_("gm", cmd_galil_move);


/* ----------------------------------------------------------------------------------------------------------- */
void cmd_galil_home(SerialCommands* sender) {
  sender->GetSerial()->println(">>> Galil homing start");

  GalilEnable = true;

  // Show the Galil status menu
  pagenum = PAGE_GALIL;
  DrawMenus(PAGE_GALIL);
  //item_changed = 1;

  // Start homing
  GALILHome(0);
  sender->GetSerial()->println(">>> Galil homing complete");
}
SerialCommand cmd_galil_home_("gh", cmd_galil_home);


/* ----------------------------------------------------------------------------------------------------------- */
void cmd_cypress_move(SerialCommands* sender) {

  int delta;
  bool record = false;
  char *p_delta;
  char *p_record;

  /* Get the parameters from the line of text */
  p_delta = sender->Next();
  p_record = sender->Next();

  /* Convert the delta into an integer, watch out for null values! */
  if ((p_delta == NULL) || (sscanf(p_delta, "%d", &delta) == 0)) {
    sender->GetSerial()->println("Error: cm command requires a numeric delta value");
    return;
  }

  /* Moves can only be so large */
  if ((delta > 2000) || (delta < -2000)) {
    sender->GetSerial()->println("Error: cm command delta must be no more than +/- 2000 counts");
    return;    
  }

  /* Look for the recording flag */
  if (p_record == NULL) {
    record = false;    
  } else if (p_record[0] == 'r') {
    record = true;
  }
  
  if (record) {
    sender->GetSerial()->printf(">>> Cypress move %d counts (recorded)\n", delta);
    CypressRecording = true;
  } else {
    sender->GetSerial()->printf(">>> Cypress move %d counts (not recorded)\n", delta);
    CypressRecording = false;
  }

  /* Now do the actual move */
  CypressSetEnable();

  // Show the Cypress status menu
  pagenum = PAGE_CYPRESS;
  DrawMenus(PAGE_CYPRESS);

  /* Set the menu field for step count */
  mymenu[PAGE_CYPRESS].m[TOTAL].mvalue.mval.l = delta;
  
  CypressMove(delta);
  
}
SerialCommand cmd_cypress_move_("cm", cmd_cypress_move);


/* ----------------------------------------------------------------------------------------------------------- */
void cmd_cypress_moveabs(SerialCommands* sender) {

  int pos;
  bool record = false;
  char *p_pos;
  char *p_record;

  /* Get the parameters from the line of text */
  p_pos = sender->Next();
  p_record = sender->Next();

  /* Convert the pos into an integer, watch out for null values! */
  if ((p_pos == NULL) || (sscanf(p_pos, "%d", &pos) == 0)) {
    sender->GetSerial()->println("Error: ca command requires a numeric position value");
    return;
  }

  /* Look for the recording flag */
  if (p_record == NULL) {
    record = false;    
  } else if (p_record[0] == 'r') {
    record = true;
  }
  
  if (record) {
    sender->GetSerial()->printf(">>> Cypress move to %d counts (recorded)\n", pos);
    CypressRecording = true;
  } else {
    sender->GetSerial()->printf(">>> Cypress move to %d counts (not recorded)\n", pos);
    CypressRecording = false;
  }

  /* Now do the actual move */
  CypressSetEnable();

  // Show the Cypress status menu
  pagenum = PAGE_CYPRESS;
  DrawMenus(PAGE_CYPRESS);

  /* Set the menu field for step count */
  //mymenu[PAGE_CYPRESS].m[TOTAL].mvalue.mval.l = delta;

  CypressMoveAbsolute(pos);

  
}
SerialCommand cmd_cypress_moveabs_("ca", cmd_cypress_moveabs);


/* ----------------------------------------------------------------------------------------------------------- */
void cmd_cypress_stop(SerialCommands* sender) {

  CypressSetEnable();
  CypressStop();
}
SerialCommand cmd_cypress_stop_("cs", cmd_cypress_stop);


/* ----------------------------------------------------------------------------------------------------------- */
void cmd_write(SerialCommands* sender) {

  #define file_tag "/ACS"
  char file_name[32];
  char file_label[32];
  int bytes_written;
  int file_number = 0;

  /* Use the global capture structure */
  samples_json["start"] = millis();

  sender->GetSerial()->println(">>> TEST WRITE TO SD");

  /* Init the SD card */
  if (!SD.begin(BUILTIN_SDCARD)) {
    sender->GetSerial()->println("SD initialization failed, cannot write a file!");
    return;
  }

  /* Get the last filename off the SD card */
  file_number = SDGetNextFilenumber("ACS");

  /* Build the new filename */
  strcpy(file_name, file_tag); // Start with the root dir and "ACS"
  
  sprintf(file_label, "%04d", file_number);  // Add the numeric value   
  strcat(file_name, file_label);  
  
  strcat(file_name, ".txt");  // Finally, the suffix

  // Open the file we want to write, remove anything already in there
  file = SD.open(file_name, FILE_WRITE);
  file.seek(0);
  file.truncate();
  
  if (!file) {
    sender->GetSerial()->printf("SD open failed, cannot write file '%s'", file_name);
    return;
  }
   
  /* Write the JSON out to the file */  
  bytes_written = serializeJson(samples_json, file);

  /* Done writing file */
  file.close();
  samples_json.clear();

  sender->GetSerial()->printf(">>> SD WRITE COMPLETE, %d BYTES WRITTEN TO %s\n", bytes_written, file_name);

}
SerialCommand cmd_write_("w", cmd_write);


/* ----------------------------------------------------------------------------------------------------------- */
void SetupControls(void) {

  serial_commands_.SetDefaultHandler(&cmd_unrecognized);
  serial_commands_.AddCommand(&cmd_help_);
  serial_commands_.AddCommand(&cmd_hello_);
  serial_commands_.AddCommand(&cmd_stop_);
  serial_commands_.AddCommand(&cmd_galil_move_);
  serial_commands_.AddCommand(&cmd_galil_home_);
  serial_commands_.AddCommand(&cmd_cypress_move_);
  serial_commands_.AddCommand(&cmd_cypress_moveabs_);
  serial_commands_.AddCommand(&cmd_cypress_stop_);
  serial_commands_.AddCommand(&cmd_write_);

}





/* END OF SERIAL CONTROL */
/* ----------------------------------------------------------------------------------------------------------- */



#pragma message "---------- BUILDING CONTROLS - DONE ----------"
