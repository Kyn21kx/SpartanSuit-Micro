#pragma once

#include "MicroUtils/MicroMath.h"

#ifdef _WIN32
#include <cstdint>
#endif

struct [[nodiscard]] Vector3 {
  union {
    struct {
      int16_t x, y, z;
    };
  };

  Vector3() = default;

  Vector3(int16_t x, int16_t y, int16_t z);

  static inline Vector3 Zero() { return Vector3{0, 0, 0}; }

  static inline Vector3 One() { return Vector3{1, 1, 1}; }

  void ToCString(char* buffer, uint32_t capacity);  
  
};
