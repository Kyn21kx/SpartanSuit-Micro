#include "MpuSensor.h"
#include "MicroUtils/Logging.h"

void MpuSensor::Initialize() {
/*--Start I2C interface--*/
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif
  this->m_sensor.initialize();
}

bool MpuSensor::TestConnection() { return this->m_sensor.testConnection(); }

void MpuSensor::Calibrate() {

  m_sensor.setXAccelOffset(0); // Set your accelerometer offset for axis X
  m_sensor.setYAccelOffset(0); // Set your accelerometer offset for axis Y
  m_sensor.setZAccelOffset(0); // Set your accelerometer offset for axis Z
  m_sensor.setXGyroOffset(0);  // Set your gyro offset for axis X
  m_sensor.setYGyroOffset(0);  // Set your gyro offset for axis Y
  m_sensor.setZGyroOffset(0);  // Set your gyro offset for axis Z

  m_sensor.CalibrateAccel(6);
  m_sensor.CalibrateGyro(6);
  m_sensor.PrintActiveOffsets();
  m_sensor.CalibrateAccel(1);
  m_sensor.CalibrateGyro(1);
  m_sensor.PrintActiveOffsets();
  m_sensor.CalibrateAccel(1);
  m_sensor.CalibrateGyro(1);
  m_sensor.PrintActiveOffsets();
  m_sensor.CalibrateAccel(1);
  m_sensor.CalibrateGyro(1);
  m_sensor.PrintActiveOffsets();
  m_sensor.CalibrateAccel(1);
  m_sensor.CalibrateGyro(1);
  m_sensor.PrintActiveOffsets();
  Logging::InfoLine("\nAny of the above offsets will work nicely \n\nProving "
                    "the PID with other method:");
}

void MpuSensor::UpdateSensor() {
  this->m_sensor.getRotation(&this->m_rotation.x, &this->m_rotation.y, &this->m_rotation.z);
  this->m_sensor.getAcceleration(&this->m_acceleration.x, &this->m_acceleration.y, &this->m_acceleration.z);
}

const Vector3& MpuSensor::GetRotation() const {
  return this->m_rotation;
}

const Vector3& MpuSensor::GetAcceleration() const {
    return this->m_acceleration;
}

