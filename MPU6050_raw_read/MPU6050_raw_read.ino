#include "Vector3.h"
#include "MicroUtils/Logging.h"
#include "MpuSensor.h"

MpuSensor mpu;

void setup() {
  Serial.begin(115200); // Initializate Serial wo work well at 8MHz/16MHz
  mpu.Initialize();
  /*Initialize device and check connection*/
  while (!mpu.TestConnection()) {
    Serial.println("MPU6050 connection failed, please check wiring");
    delay(500);
  }
  Serial.println("MPU6050 connection successful");
  
  mpu.Calibrate();

  Serial.println("Waiting 5 seconds for good measure");
  delay(5000);
}

void loop() {
  mpu.UpdateSensor();
  char accelerationStr[100];
  const Vector3& acc = mpu.GetAcceleration();
  acc.ToCString(accelerationStr, 100);
  Logging::InfoLine("Acceleration readings: %s", accelerationStr);
}
