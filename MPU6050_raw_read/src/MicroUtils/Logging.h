#pragma once

#include <cstdint>

#include "Definitions.h"

#if MICRO_PLATFORM
#include "Arduino.h"
#else
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

  static void DebugLine(const char* format, ...);
  
  static void InfoLine(const char* format, ...);

  static void WarnLine(const char* format, ...);

  static void ErrorLine(const char* format, ...);
  
private:

  static void SimplePrint(const char* message);
  
  static Print* s_output;
  
};

