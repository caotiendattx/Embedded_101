#include <Arduino.h>
#include "globals.h"

// main register bank
volatile int32_t REG32[REG_SIZE32];
//cast  as byte array
volatile byte * REGBANK = (byte *)REG32;

//create aliases for registers
volatile uint8_t         * MPU6050_enable               = (uint8_t *)&REGBANK[REG_ENABLE];
volatile uint16_t        * sample_rate                  = (float *)&REGBANK[REG_SAMPLE_RATE];
volatile float           * gyroscopeMisalignment        = (float *)&REGBANK[REG_GYROSCOPE_MISALIGNMENT];
volatile float           * gyroscopeSensitivity         = (float *)&REGBANK[REG_GYROSCOPE_SENSITIVITY];
volatile float           * gyroscopeOffset              = (float *)&REGBANK[REG_GYROSCOPE_OFFSET];
volatile float           * accelerometerMisalignment    = (float *)&REGBANK[REG_ACCELEROMETER_MISALIGNMENT];
volatile float           * accelerometerSensitivity     = (float *)&REGBANK[REG_ACCELEROMETER_SENSITIVITY];
volatile float           * accelerometerOffset          = (float *)&REGBANK[REG_ACCELEROMETER_OFFSET];
volatile float           * softIronMatrix               = (float *)&REGBANK[REG_SOFTIRON_MATRIX];
volatile float           * hardIronOffset               = (float *)&REGBANK[REG_HARD_IRON_OFFSET];
volatile uint8_t         * FusionConvention             = (float *)&REGBANK[REG_FUSION_CONVENTION];
volatile float           * gain                         = (float *)&REGBANK[REG_GAIN];
volatile float           * gyroscopeRange               = (float *)&REGBANK[REG_GYROSCOPE_RANGE];
volatile float           * accelerationRejection        = (float *)&REGBANK[REG_ACCELERATION_REJECTION];
volatile float           * magneticRejection            = (float *)&REGBANK[REG_MAGNETIC_REJECTION];
volatile uint8_t         *recoveryTriggerPeriod_A       = (float *)&REGBANK[REG_RECOVERY_TRIGGER_PERIOD_A];
volatile uint8_t         * reverse_config               = (float *)&REGBANK[REG_REVERSE]; //configurationd ata about motors and encoders - shoudl they be reversed?

//Read-only registers
volatile uint8_t  * fw_version        = (uint8_t *)&REGBANK[REG_FW_VERSION];//2-element array
volatile uint8_t  * who_am_i          = (uint8_t *)&REGBANK[REG_WHO_AM_I];
volatile float  * roll                = (float *)&REGBANK[REG_Roll];
volatile float  * pitch               = (float *)&REGBANK[REG_Pitch];
volatile float  * yaw                 = (float *)&REGBANK[REG_Yaw];
volatile float  * gx                  = (float *)&REGBANK[REG_Gx];
volatile float  * gy                  = (float *)&REGBANK[REG_Gy];
volatile float  * gz                  = (float *)&REGBANK[REG_Gz];
volatile float  * ax                  = (float *)&REGBANK[REG_Ax];
volatile float  * ay                  = (float *)&REGBANK[REG_Ay];
volatile float  * az                  = (float *)&REGBANK[REG_Az];
volatile bool have_i2c = false;

//function for initialization registers
void globals_init(){
    *who_am_i = DEFAULT_I2C_ADDRESS;
    fw_version[0]=FW_VERSION_MINOR;
    fw_version[1]=FW_VERSION_MAJOR;
}
