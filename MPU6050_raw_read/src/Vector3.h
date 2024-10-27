#pragma once

#include "MicroUtils/Definitions.h"

#include <cstdint>

struct [[nodiscard]] Vector3 {
  union {
    struct {
      int16_t x, y, z;
    };
  };

  Vector3();

  Vector3(int16_t x, int16_t y, int16_t z);

  static inline Vector3 Zero() { return Vector3(0, 0, 0); }

  static inline Vector3 One() { return Vector3(1, 1, 1); }

  void ToCString(char* buffer, uint32_t capacity) const;  
  
  void Print() const;

  float GetMagnitude() const;
  
};
