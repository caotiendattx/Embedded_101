#include "pins.h"
#include "globals.h"
#include "i2c.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "Fusion/Fusion.h"
#include "mpu6050.h"


#define FUSION_UPDATE_INTERVAL 40000 //how frequently should speed be computed? in microseconds

uint32_t last_fusion_update  = micros();
#define SAMPLE_RATE (100) // replace this with actual sample rate

FusionVector gyroscope = {0.0f, 0.0f, 0.0f}; // replace this with actual gyroscope data in degrees/s
FusionVector accelerometer = {0.0f, 0.0f, 1.0f}; // replace this with actual accelerometer data in g

FusionAhrs ahrs;
const FusionAhrsSettings settings = {
        .convention = FusionConventionNwu,
        .gain = 0.5f,
        .gyroscopeRange = 2000.0f, /* replace this with actual gyroscope range in degrees/s */
        .accelerationRejection = 10.0f,
        .magneticRejection = 10.0f,
        .recoveryTriggerPeriod = 5 * SAMPLE_RATE, /* 5 seconds */
};
void setup(){
    pins_init();    //set up pin directions
    globals_init(); // initialize global variables and register bank
    i2c_begin();    //start i2c bus on Wire, as a slave
    delay(100);
    FusionAhrsInitialise(&ahrs);
    FusionAhrsSetSettings(&ahrs, &settings);
}
    
void loop(){
     if (micros()-last_fusion_update > FUSION_UPDATE_INTERVAL) {
        last_fusion_update = micros();
        fetchData();
        gyroscope.axis.x = getGyroX();
        *gx = gyroscope.axis.x;
        gyroscope.axis.y = getGyroY();
        *gy = gyroscope.axis.y;
        gyroscope.axis.z = getGyroZ();
        *gz = gyroscope.axis.z;
        
        accelerometer.axis.x = getAccX();
        *ax = accelerometer.axis.x;
        accelerometer.axis.y = getAccY();
        *ay = accelerometer.axis.y;
        accelerometer.axis.z = getAccZ();
        *az = accelerometer.axis.z;

        FusionAhrsUpdateNoMagnetometer(&ahrs, gyroscope, accelerometer, SAMPLE_PERIOD);
        const FusionEuler euler = FusionQuaternionToEuler(FusionAhrsGetQuaternion(&ahrs));
        *roll = euler.angle.roll;
        *pitch = euler.angle.pitch;
        *yaw = euler.angle.yaw;
    }
}
