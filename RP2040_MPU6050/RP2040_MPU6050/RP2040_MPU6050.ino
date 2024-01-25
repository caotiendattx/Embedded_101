#include "pins.h"
#include "globals.h"
#include "i2c.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "Fusion/Fusion.h"
#include "FusionAhrs.h"
#include "mpu6050.h"


#define PROJECT_DEBUG
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
MPU6050 mpu(Wire);

void setup(){
#ifdef PROJECT_DEBUG
    Serial.begin(9600);
#endif
    pins_init();    //set up pin directions
    globals_init(); // initialize global variables and register bank
    i2c_begin();    //start i2c bus on Wire, as a slave
    delay(100);
    mpu.begin();
    FusionAhrsInitialise(&ahrs);
    FusionAhrsSetSettings(&ahrs, &settings);
    Serial.print(F("Config: OK"));
}
    
void loop(){
  if (micros()-last_fusion_update > FUSION_UPDATE_INTERVAL) {
    last_fusion_update = micros();
    mpu.fetchData();
    gyroscope.axis.x = mpu.getGyroX();
    *gx = gyroscope.axis.x;
    gyroscope.axis.y = mpu.getGyroY();
    *gy = gyroscope.axis.y;
    gyroscope.axis.z = mpu.getGyroZ();
    *gz = gyroscope.axis.z;
    
    accelerometer.axis.x = mpu.getAccX();
    *ax = accelerometer.axis.x;
    accelerometer.axis.y = mpu.getAccY();
    *ay = accelerometer.axis.y;
    accelerometer.axis.z = mpu.getAccZ();
    *az = accelerometer.axis.z;

    FusionAhrsUpdateNoMagnetometer(&ahrs, gyroscope, accelerometer, FUSION_UPDATE_INTERVAL);
    const FusionEuler euler = FusionQuaternionToEuler(FusionAhrsGetQuaternion(&ahrs));
    *roll = euler.angle.roll;
    *pitch = euler.angle.pitch;
    *yaw = euler.angle.yaw;

    Serial.print(F("ANGLE     X: "));Serial.print(*roll);
    Serial.print("\tY: ");Serial.print(*pitch);
    Serial.print("\tZ: ");Serial.println(*yaw );
  }
}
