/*
  MPU6050 Raw

  A code for obtaining raw data from the MPU6050 module with the option to
  modify the data output format.

  Find the full MPU6050 library documentation here:
  https://github.com/ElectronicCats/mpu6050/wiki
*/
#include "I2Cdev.h"
#include "MPU6050.h"

/* MPU6050 default I2C address is 0x68*/
MPU6050 mpu;
// MPU6050 mpu(0x69);         //Use for AD0 high
// MPU6050 mpu(0x68, &Wire1); //Use for AD0 low, but 2nd Wire (TWI/I2C) object.

/* OUTPUT FORMAT
DEFINITION----------------------------------------------------------------------------------
- Use "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated list of the
accel X/Y/Z and gyro X/Y/Z values in decimal. Easy to read, but not so easy to
parse, and slower over UART.

- Use "OUTPUT_BINARY_ACCELGYRO" to send all 6 axes of data as 16-bit binary, one
right after the other. As fast as possible without compression or data loss,
easy to parse, but impossible to read for a human. This output format is used as
an output.
--------------------------------------------------------------------------------------------------------------*/
#define OUTPUT_READABLE_ACCELGYRO
// #define OUTPUT_BINARY_ACCELGYRO

int16_t prevGx, prevGy, prevGz;
int16_t gx, gy, gz;
bool blinkState;

void setup() {
/*--Start I2C interface--*/
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  Serial.begin(115200); // Initializate Serial wo work well at 8MHz/16MHz

  /*Initialize device and check connection*/
  Serial.println("Initializing MPU...");
  mpu.initialize();
  Serial.println("Testing MPU6050 connection...");
  while (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed, please check wiring");
    delay(500);
  }

  Serial.println("MPU6050 connection successful");

  /* Use the code below to change accel/gyro offset values. Use MPU6050_Zero to
   * obtain the recommended offsets */
  Serial.println("Updating internal sensor offsets...\n");
  mpu.setXAccelOffset(0); // Set your accelerometer offset for axis X
  mpu.setYAccelOffset(0); // Set your accelerometer offset for axis Y
  mpu.setZAccelOffset(0); // Set your accelerometer offset for axis Z
  mpu.setXGyroOffset(0);  // Set your gyro offset for axis X
  mpu.setYGyroOffset(0);  // Set your gyro offset for axis Y
  mpu.setZGyroOffset(0);  // Set your gyro offset for axis Z
  /*Print the defined offsets*/
  Serial.print("\t");
  Serial.print(mpu.getXAccelOffset());
  Serial.print("\t");
  Serial.print(mpu.getYAccelOffset());
  Serial.print("\t");
  Serial.print(mpu.getZAccelOffset());
  Serial.print("\t");
  Serial.print(mpu.getXGyroOffset());
  Serial.print("\t");
  Serial.print(mpu.getYGyroOffset());
  Serial.print("\t");
  Serial.print(mpu.getZGyroOffset());
  Serial.print("\n");

  calibrate();
  
  Serial.println("Waiting 5 seconds for good measure");
  delay(5000);
}

 /*
    PID tuning (actually PI) works like this: changing the offset in the MPU6050
    gives instant results, allowing us to use the Proportional and Integral
    parts of the PID to find the ideal offsets. The Integral uses the error from
    the set point (which is zero) and adds a fraction of this error to the
    integral value. Each reading reduces the error towards the desired offset.
    The greater the error, the more we adjust the integral value.

                The Proportional part helps by filtering out noise from the
    integral calculation. The Derivative part is not used due to noise and the
    sensor being stationary. With the noise removed, the integral value
    stabilizes after about 600 readings. At the end of each set of 100 readings,
    the integral value is used for the actual offsets, and the last proportional
    reading is ignored because it reacts to any noise.                      */

void calibrate() {
  Serial.println("\nXAccel\t\tYAccel\t\tZAccel\t\tXGyro\t\tYGyro\t\tZGyro");
  mpu.CalibrateAccel(6);
  mpu.CalibrateGyro(6);
  Serial.println("\n600 Readings");
  mpu.PrintActiveOffsets();
  mpu.CalibrateAccel(1);
  mpu.CalibrateGyro(1);
  Serial.println("700 Total Readings");
  mpu.PrintActiveOffsets();
  mpu.CalibrateAccel(1);
  mpu.CalibrateGyro(1);
  Serial.println("800 Total Readings");
  mpu.PrintActiveOffsets();
  mpu.CalibrateAccel(1);
  mpu.CalibrateGyro(1);
  Serial.println("900 Total Readings");
  mpu.PrintActiveOffsets();
  mpu.CalibrateAccel(1);
  mpu.CalibrateGyro(1);
  Serial.println("1000 Total Readings");
  mpu.PrintActiveOffsets();
  Serial.println("\nAny of the above offsets will work nicely \n\nProving the "
                 "PID with other method:");
}

void loop() {
  /* Read raw accel/gyro data from the module. Other methods commented*/
  mpu.getRotation(&gx, &gy, &gz);
  // mpu.getRotation(&gx, &gy, &gz);
  Serial.print("(");
  Serial.print(gx);
  Serial.print(", ");
  Serial.print(gy);
  Serial.print(", ");
  Serial.print(gz);
  Serial.println(")");
}
