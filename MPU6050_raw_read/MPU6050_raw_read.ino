#include "src/Vector3.h"
#include "src/MicroUtils/Logging.h"
#include "src/MpuSensor.h"

MpuSensor mpu;

void setup() {
  Serial.begin(115200); // Initializate Serial wo work well at 8MHz/16MHz
  Logging::Begin(&Serial);
  
  Logging::DebugLine("Initializing MPU6050");
  mpu.Initialize();
  /*Initialize device and check connection*/
  while (!mpu.TestConnection()) {
    Logging::ErrorLine("MPU6050 connection failed, please check wiring");
    delay(500);
  }
  Logging::InfoLine("MPU6050 connection successful");
  
  mpu.Calibrate();

  Logging::DebugLine("Printing a vector just because");
  mpu.GetAcceleration().Print();

  Serial.println("Waiting 5 seconds for good measure");
  delay(5000);
}

void loop() {
  mpu.UpdateSensor();
  const Vector3& acc = mpu.GetAcceleration();
  Logging::LogLevel(ELogLevel::Info, "Acceleration: ");
  acc.Print();
  const Vector3& rot = mpu.GetRotation();
  Logging::LogLevel(ELogLevel::Info, "Rotation: ");
  rot.Print();
  delay(100);
  
}
