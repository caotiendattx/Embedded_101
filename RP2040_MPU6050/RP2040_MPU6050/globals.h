#ifndef _MPU6050_I2C_GLOBAL_H
#define _MPU6050_I2C_GLOBAL_H
/* various global variables, defines, etc */
#define FW_VERSION_MAJOR 1
#define FW_VERSION_MINOR 0

#define DEFAULT_I2C_ADDRESS 0x54

//Statuses
#define STATUS_ON        0

// I2C register bank
#define REG_SIZE32 57 //size of register bank, in 4-byte (32 bit) units
#define RW_REGISTERS 190 //number of RW registers (in bytes)
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
#define REG_ENABLE                      0
#define REG_SAMPLE_RATE                 1
#define REG_GYROSCOPE_MISALIGNMENT      3
#define REG_GYROSCOPE_SENSITIVITY       39
#define REG_GYROSCOPE_OFFSET            51
#define REG_ACCELEROMETER_MISALIGNMENT  63
#define REG_ACCELEROMETER_SENSITIVITY   99
#define REG_ACCELEROMETER_OFFSET        111
#define REG_SOFTIRON_MATRIX             123
#define REG_HARD_IRON_OFFSET            159
#define REG_FUSION_CONVENTION           171
#define REG_GAIN                        172
#define REG_GYROSCOPE_RANGE             176
#define REG_ACCELERATION_REJECTION      180
#define REG_MAGNETIC_REJECTION          184
#define REG_RECOVERY_TRIGGER_PERIOD_A   188
#define REG_REVERSE                     189

//Read Only
#define REG_FW_VERSION      190
#define REG_WHO_AM_I        191
#define REG_Roll            192
#define REG_Pitch           196
#define REG_Yaw             200
#define REG_Gx              204
#define REG_Gy              208
#define REG_Gz              212
#define REG_Ax              216
#define REG_Ay              220
#define REG_Az              224


//                          228
/* **********************************************************************
 *  pointer/aliases - for direct access to registers. These are forward declarations,
 * the definitions are in regmap.cpp
 * *********************************************************************
 */
//RW
extern volatile uint8_t         * MPU6050_enable;
extern volatile uint16_t        * sample_rate;
extern volatile float           * gyroscopeMisalignment;
extern volatile float           * gyroscopeSensitivity;
extern volatile float           * gyroscopeOffset;
extern volatile float           * accelerometerMisalignment;
extern volatile float           * accelerometerSensitivity;
extern volatile float           * accelerometerOffset;
extern volatile float           * softIronMatrix;
extern volatile float           * hardIronOffset;
extern volatile uint8_t         * FusionConvention;
extern volatile float           * gain;
extern volatile float           * gyroscopeRange;
extern volatile float           * accelerationRejection;
extern volatile float           * magneticRejection;
extern volatile uint8_t         *recoveryTriggerPeriod_A;
extern volatile uint8_t         * reverse_config; //configurationd ata about motors and encoders - shoudl they be reversed?
/* *********************************************
 *  Read-only registers
 * *********************************************
 */
extern volatile uint8_t  * fw_version; //2-element array
extern volatile uint8_t  * who_am_i;
extern volatile float  * roll;
extern volatile float  * pitch;
extern volatile float  * yaw;
extern volatile float  * gx;
extern volatile float  * gy;
extern volatile float  * gz;
extern volatile float  * ax;
extern volatile float  * ay;
extern volatile float  * az;
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
