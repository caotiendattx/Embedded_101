#ifndef _MPU6050_I2C_GLOBAL_H
#define _MPU6050_I2C_GLOBAL_H
/* various global variables, defines, etc */
#define FW_VERSION_MAJOR 1
#define FW_VERSION_MINOR 0

#define DEFAULT_I2C_ADDRESS 0x54

//Statuses
#define STATUS_ON        0

// I2C register bank
#define REG_SIZE32 10 //size of register bank, in 4-byte (32 bit) units
#define RW_REGISTERS 24 //number of RW registers (in bytes)
//this will be defined in regmap.cpp
extern  volatile byte * REGBANK;

/* **********************************************************************
 *  Register definitions
 *  All multibyte registers  use little-endian byte order: thus, if
 * a uint16_t value is stored in registers N, N+1,
 * then register N is low byte, and register N+1 is high byte
 * so the full value is
 * (REGBANK[N+1]<<8)|REGBANK[N]
 * This allows directly addressing them as multibyte variables, e.g.
 * uint16_t * value =(uint16_t *) &REGBANK[N]; //pointer to variable
 * *value=25;
 * Yes, it is a bit hacky
 * *********************************************************************
 */
//R/W registers
#define REG_ENABLE              0
//Read Only
#define REG_FW_VERSION      24
#define REG_WHO_AM_I        26
#define REG_Roll            27
#define REG_Pitch           28
#define REG_Yaw             32
#define REG_Gx              36
#define REG_Gy              38
#define REG_Gz              36
#define REG_Ax              38
#define REG_Ay              36
#define REG_Az              38

/* **********************************************************************
 *  pointer/aliases - for direct access to registers. These are forward declarations,
 * the definitions are in regmap.cpp
 * *********************************************************************
 */

extern volatile uint8_t  * motor_enable;
//extern volatile byte     * encoder_reset;

/* *********************************************
 *  Read-only registers
 * *********************************************
 */
extern volatile uint8_t  * fw_version; //2-element array
extern volatile uint8_t  * who_am_i;
extern volatile int16_t  * roll;
extern volatile int16_t  * pitch;
extern volatile int16_t  * yaw;
extern volatile int16_t  * gx;
extern volatile int16_t  * gy;
extern volatile int16_t  * gz;
extern volatile int16_t  * ax;
extern volatile int16_t  * ay;
extern volatile int16_t  * az;
/*
 FLAGS
*/

/* other global variables */
extern volatile bool have_i2c;

/* *********************************************
 *  Function declaration
 * *********************************************
 */

void globals_init();


#endif
