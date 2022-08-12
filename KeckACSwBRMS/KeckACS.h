// Main header file for project
#ifndef _KECK_ACS_H
#define _KECK_ACS_H

// Switches to turn on certain debug messaging
//#define DEBUG_MENUS 
//#define DEBUG_GALIL
//#define DEBUG_CYPRESS 
//#define DEBUG_SWITCHES

// SD

// CLI
//Create a 32 bytes static buffer to be used exclusive by SerialCommands object.
//The size should accomodate command token, arguments, termination sequence and string delimeter \0 char.
char serial_command_buffer_[32];

//Creates SerialCommands object attached to Serial
//working buffer = serial_command_buffer_
//command delimeter: Cr & Lf
//argument delimeter: SPACE
SerialCommands serial_commands_(&Serial, serial_command_buffer_, sizeof(serial_command_buffer_), "\n", " ");




typedef enum {
  CW, 
  CCW
  } dtype_t;

typedef enum {
  PAGE_TOP, 
  PAGE_GALIL, 
  PAGE_CYPRESS, 
  PAGE_CYPREPLY
  } ptype_t;

typedef enum {
  HOME, 
  STEPS, 
  TOTAL, 
  MAX, 
  CLEAR, 
  CYCLES, 
  ELAPSED, 
  ERR, 
  APCREG, 
  RECORD, 
  MGO, 
  MEXIT
  } mtype_t;
  
typedef enum {
  label = -1, 
  funcall, 
  selectable, 
  editable, 
  noneditable, 
  myexit
  } itype_t;

// label, static label, does nothing
// funcall, goto this function &function_name
// selectable, Goto to this menu
// editable, Can change the value of this item, used to create an input value
// noneditable, cannot change the value, used to display a value
// myexit, indicates the menu exit point (pagenum =0, itemnum = 0)



#define NUM_LEDS 1

// Pin definitions
#define TFT_DC          9
#define TFT_CS          10
#define TFT_MOSI        11
#define TFT_CLK         13
#define TFT_RST         8
#define TFT_MISO        12
#define buttonUpPin     33
#define buttonDownPin   36
#define buttonSelectPin 37
#define backlight_EN    34
#define encoder0PinA    15
#define encoder0PinB    14
#define encoder0Btn     16
#define CypressCSPin    28

#define GALIL_RST       17
#define GALIL_CLK       0
#define GALIL_DEC       21
#define GALIL_INC       22
#define GALIL_IDX       39
#define GALIL_HOM       25
#define GALIL_B         24
#define GALIL_A         23
#define GALIL_ERRn      20

#define PROBE           35

#define Cypress_RSTn 35
#define Cypress_HOM 40
#define Cypress_IDX 41
#define PWM_DISABLE_MOT0 3


// GALIL
#define GALIL_MAX_STEP 2048

static float current_mA = 0;
static int16_t rawcurrent;
volatile bool galil_err;

// CYPRESS
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


#endif
