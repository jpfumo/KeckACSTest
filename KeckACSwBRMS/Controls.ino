#pragma message "---------- BUILDING CONTROLS ----------"

#include "KeckACS.h"



/* =========================================================================================================== */
/* SERIAL PORT CLI / CONTROL */
/* =========================================================================================================== */

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
  sender->GetSerial()->println("  help  [none]       Display this help message");
  sender->GetSerial()->println("");
  sender->GetSerial()->println("Galil control commands are: ");
  sender->GetSerial()->println("  CMD   PARAMS       Description");
  sender->GetSerial()->println("  gh    [none]       Home the actuator under Galil control");
  sender->GetSerial()->println("");
  sender->GetSerial()->println("Cypress control commands are: ");
  sender->GetSerial()->println("  CMD   PARAMS       Description");
  sender->GetSerial()->println("  ch    [none]       Home the actuator under Cypress control");
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
void cmd_galil(SerialCommands* sender) {
  sender->GetSerial()->println("GALIL COMMAND: ");
}
SerialCommand cmd_galil_("g", cmd_galil);


/* ----------------------------------------------------------------------------------------------------------- */
void cmd_galilhome(SerialCommands* sender) {
  sender->GetSerial()->println(">>> Galil homing start");
  // Show the Galil status menu


  // Start homing
  GALILHome(0);
  sender->GetSerial()->println(">>> Galil homing complete");
}
SerialCommand cmd_galilhome_("gh", cmd_galilhome);


/* ----------------------------------------------------------------------------------------------------------- */
void cmd_write(SerialCommands* sender) {
  sender->GetSerial()->println("WRITING TO SD");
}
SerialCommand cmd_write_("w", cmd_write);


/* ----------------------------------------------------------------------------------------------------------- */
void SetupControls(void) {

  serial_commands_.SetDefaultHandler(&cmd_unrecognized);
  serial_commands_.AddCommand(&cmd_help_);
  serial_commands_.AddCommand(&cmd_hello_);
  serial_commands_.AddCommand(&cmd_stop_);
  serial_commands_.AddCommand(&cmd_galil_);
  serial_commands_.AddCommand(&cmd_galilhome_);
  serial_commands_.AddCommand(&cmd_write_);

}





/* END OF SERIAL CONTROL */
/* ----------------------------------------------------------------------------------------------------------- */



#pragma message "---------- BUILDING CONTROLS - DONE ----------"
