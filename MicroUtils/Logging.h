#pragma once

#include <cstdint>

#include "Definitions.h"

#if PC_PLATFORM
#include <cstdio>
using Print = FILE;
#endif

enum ELogLevel : uint16_t {
  Debug,
  Info,
  Warn,
  Error
};

class Logging {
public:
  static void Begin(Print* output);

  static void LogLevel(ELogLevel level, const char* format, ...);
  
private:
  static Print* s_output;
  
};

