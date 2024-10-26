#include "Logging.h"
#include <cstdarg>
#include <cstring>

constexpr uint32_t MAX_LOG_BUFFER_SIZE = 256;

constexpr uint32_t MAX_FORMAT_BUFFER_SIZE = 200;

Print *Logging::s_output;

void Logging::Begin(Print *output) { s_output = output; }

void Logging::LogLevel(ELogLevel level, const char *format, ...) {
  if (s_output == nullptr)
    return;
  va_list args;
  va_start(args, format);
  char formatBuffer[MAX_FORMAT_BUFFER_SIZE] = "";
  char printBuffer[MAX_LOG_BUFFER_SIZE];

  switch (level) {
  case Info:
    strncat(formatBuffer, "[Info] - ", MAX_LOG_BUFFER_SIZE);
    break;
  case Debug:
    strncat(formatBuffer, "[Debug] - ", MAX_LOG_BUFFER_SIZE);
    break;
  case Error:
    strncat(formatBuffer, "[Error] ", MAX_LOG_BUFFER_SIZE);
    break;
  case Warn:
    strncat(formatBuffer, "[Warn] - ", MAX_LOG_BUFFER_SIZE);
    break;
  }

  strncat(formatBuffer, format, MAX_LOG_BUFFER_SIZE)

#if MICRO_PLATFORM
      vsprintf(printBuffer, formatBuffer, args);
  s_output->print(printBuffer);
#else

      vfprintf(s_output, formatBuffer, args);

#endif
  va_end(args);
}

void Logging::DebugLine(const char *format, ...) {
  va_list args;
  va_start(args, format);
  Logging::LogLevel(ELogLevel::Debug, format, args);
  va_end(args);
  SimplePrint("\n");
}

void Logging::InfoLine(const char *format, ...) {
  va_list args;
  va_start(args, format);
  Logging::LogLevel(ELogLevel::Info, format, args);
  va_end(args);
  SimplePrint("\n");
}

void Logging::WarnLine(const char *format, ...) {
  va_list args;
  va_start(args, format);
  Logging::LogLevel(ELogLevel::Warn, format, args);
  va_end(args);
  SimplePrint("\n");
}

void Logging::ErrorLine(const char *format, ...) {
  va_list args;
  va_start(args, format);
  Logging::LogLevel(ELogLevel::Error, format, args);
  va_end(args);
  SimplePrint("\n");
}

void Logging::SimplePrint(const char *message) {
#if MICRO_PLATFORM
  s_output->print(message);
#else
  fprintf(s_output, "%s", message);
#endif
}
