#include "Vector3.h"
#include "MicroUtils/MicroStringUtils.h"
#include <cstring>


/// @brief 3 * int16_t for each comp + 5 for the commas and parentheses
constexpr uint32_t REQUIRED_BUFF_SIZE = (MAX_INT16_BUFFER_SIZE * 3) + 5;

void Vector3::ToCString(char* buffer, uint32_t capacity) {
	if (capacity < REQUIRED_BUFF_SIZE) {
		
	}
}

