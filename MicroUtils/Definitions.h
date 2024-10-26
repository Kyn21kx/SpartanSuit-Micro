#pragma once

#if defined(ESP8266) || defined(ESP32)
  #define MICRO_PLATFORM 1
  #define PC_PLATFORM 0
#else
  #define MICRO_PLATFORM 0
  #define PC_PLATFORM 1
#endif


