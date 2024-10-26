#include "MicroStringUtils.h"
#include "MicroMath.h"
#include <cstdint>
#include <cstdio>
#include <stdio.h>
#include <string.h>


void MicroStringUtils::Append(char* buffer, int16_t toAppend, uint32_t offset, uint32_t maxSize) {
  //Get the number of digits here
  uint8_t digitCount = MicroMath::DigitCount(toAppend);
  char appendBuffer[MAX_INT16_BUFFER_SIZE];
  sprintf(appendBuffer, "%d", toAppend);
  strncpy(buffer + offset, appendBuffer, strlen(appendBuffer));
}

char MicroStringUtils::ToChar(int16_t n) {
  return n + '0';
}

