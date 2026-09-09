#include "M5StickCPlus2.h"

void setup() {
    auto cfg = M5.config();
    StickCP2.begin(cfg);
    M5.Display.setBrightness(0);
    M5.Display.sleep();
    Serial.begin(9600); 
}

void loop(void) {
    auto imu_update = StickCP2.Imu.update();
    if (imu_update) {
        auto data = StickCP2.Imu.getImuData();

        // The data obtained by getImuData can be used as follows.
        // data.accel.x;      // accel x-axis value.
        // data.accel.y;      // accel y-axis value.
        // data.accel.z;      // accel z-axis value.
        // data.accel.value;  // accel 3values array [0]=x / [1]=y / [2]=z.

        // data.gyro.x;      // gyro x-axis value.
        // data.gyro.y;      // gyro y-axis value.
        // data.gyro.z;      // gyro z-axis value.
        // data.gyro.value;  // gyro 3values array [0]=x / [1]=y / [2]=z.

        Serial.printf("%f %f %f ",
                      data.accel.x, 
                      data.accel.y,
                      data.accel.z);
        Serial.printf("%f %f %f %lu\n", 
                      data.gyro.x, 
                      data.gyro.y,
                      data.gyro.z,
                      millis());

    }
}