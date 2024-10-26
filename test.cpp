#include "MicroUtils/MicroStringUtils.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main(int argc, char** argv) {
  int16_t number = atoi(argv[1]);
  
  char line[200] = "The number you just entered is: ";  

  MicroStringUtils::Append(line, number, strlen(line), 200);

  printf("%s\n", line);
  
  return 0;
}



