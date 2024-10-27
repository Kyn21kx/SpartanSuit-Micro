#pragma once

#include "I2Cdev.h"
#include "MPU6050.h"
#include "Vector3.h"

class MpuSensor {

public:
  void Initialize();

  bool TestConnection();

  /*
      PID tuning (actually PI) works like this: changing the offset in the
     MPU6050 gives instant results, allowing us to use the Proportional and
     Integral parts of the PID to find the ideal offsets. The Integral uses the
     error from the set point (which is zero) and adds a fraction of this error
     to the integral value. Each reading reduces the error towards the desired
     offset. The greater the error, the more we adjust the integral value.

                                          The Proportional part helps by
     filtering out noise from the integral calculation. The Derivative part is
     not used due to noise and the sensor being stationary. With the noise
     removed, the integral value stabilizes after about 600 readings. At the end
     of each set of 100 readings, the integral value is used for the actual
     offsets, and the last proportional reading is ignored because it reacts to
     any noise.                      */

  void Calibrate();

  void UpdateSensor();

  const Vector3& GetRotation() const;  

  const Vector3& GetAcceleration() const;
  
private:
  Vector3 m_rotation;
  Vector3 m_acceleration;

  MPU6050 m_sensor;
};
