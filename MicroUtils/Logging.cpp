#include "Logging.h"
#include <cstdarg>

constexpr uint32_t MAX_LOG_BUFFER_SIZE = 256;

void Logging::Begin(Print* output) {
  s_output = output;
}

void Logging::Log(const char* format, ...) {
  if (s_output == nullptr) return;
  va_list args;
  va_start(args, format);
#if MICRO_PLATFORM
  
  char buffer[MAX_LOG_BUFFER_SIZE];
  sprintf(buffer, format, args);
  s_output->print(buffer);
  
#else
  
  fprintf(s_output, format, args);    

#endif  
  va_end(args);
}




