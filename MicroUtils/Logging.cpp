#include "Logging.h"
#include <cstdarg>

constexpr uint32_t MAX_LOG_BUFFER_SIZE = 256;

Print* Logging::s_output;

void Logging::Begin(Print* output) {
  s_output = output;
}

void Logging::LogLevel(ELogLevel level, const char* format, ...) {
  if (s_output == nullptr) return;
  va_list args;
  va_start(args, format);
#if MICRO_PLATFORM
  
  char buffer[MAX_LOG_BUFFER_SIZE];
  vsprintf(buffer, format, args);
  s_output->print(buffer);
#else
  
  vfprintf(s_output, format, args);    

#endif  
  va_end(args);
}




