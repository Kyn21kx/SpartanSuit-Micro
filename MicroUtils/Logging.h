#pragma once

#include <cstdint>
#include <random>


#include "Definitions.h"

#if PC_PLATFORM
#include <cstdio>
// We're probably in a computer, so, you know, just use FILE* instead of Print*
using Print = FILE;
#endif

enum LogLevel : uint16_t {
  Debug,
  Info,
  Warn,
  Err
};

class Logging {
public:
  static void Begin(Print* output);

  static void Log(const char* format, ...);
  
private:
  static Print* s_output;
  
};

