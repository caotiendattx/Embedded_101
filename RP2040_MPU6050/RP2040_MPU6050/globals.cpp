#include <Arduino.h>
#include "globals.h"

// main register bank
volatile int32_t REG32[REG_SIZE32];
//cast  as byte array
volatile byte * REGBANK = (byte *)REG32;


//create aliases for registers

//Read-only registers
volatile uint8_t  * fw_version        = (uint8_t *)&REGBANK[REG_FW_VERSION];//2-element array
volatile uint8_t  * who_am_i          = (uint8_t *)&REGBANK[REG_WHO_AM_I];

volatile bool have_i2c = false;



//function for initialization registers
void globals_init(){
    *who_am_i = DEFAULT_I2C_ADDRESS;
    fw_version[0]=FW_VERSION_MINOR;
    fw_version[1]=FW_VERSION_MAJOR;
}
