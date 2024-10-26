#pragma once

#include "Definitions.h"
#include <cmath>

#if PC_PLATFORM
#include <cstdint>

#endif

class MicroMath {  
public:
  static inline uint8_t DigitCount(int16_t n) {
    if (n == 0) return 1;
    int16_t absoluteN = abs(n);
    uint8_t digitCount = (uint8_t)log10f(absoluteN) + 1;
    return digitCount;
  } 

  static inline int16_t GetLastDigit(int16_t n) {
    float divResDec = n / 10.0f;
    int16_t divResInt = (int16_t)divResDec;
    return static_cast<int16_t>((divResDec - divResInt) * 10);
  }
  
};

