#include "Vector3.h"
#include "MicroUtils/Logging.h"
#include "MicroUtils/MicroStringUtils.h"

#if PC_PLATFORM
#include <cstdio>
#include <cmath>
#else 
#include "Arduino.h"
#endif

/// @brief 3 * int16_t for each comp + 5 for the commas and parentheses
constexpr uint32_t REQUIRED_BUFF_SIZE = (MAX_INT16_BUFFER_SIZE * 3) + 5;

void Vector3::ToCString(char* buffer, uint32_t capacity) const {
	if (capacity < REQUIRED_BUFF_SIZE) {
		Logging::LogLevel(ELogLevel::Error, "Required buffer size is %d, got %d instead!", REQUIRED_BUFF_SIZE, capacity);
		return;		
	}
	sprintf(buffer, "(%d,%d,%d)", this->x, this->y, this->z);
}

void Vector3::Print() const {
	Logging::LogLevel(ELogLevel::Info, "(%d,%d,%d)\n", this->x, this->y, this->z);
}

float Vector3::GetMagnitude() const {
	float xSqr = this->x * this->x;
	float ySqr = this->y * this->y;
	float zSqr = this->z * this->z;
	return sqrtf(xSqr + ySqr + zSqr);
}
    
