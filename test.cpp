#include "MicroUtils/Logging.h"
#include "MicroUtils/MicroStringUtils.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Vector3.h"

int main(int argc, char** argv) {
  Logging::Begin(stdout);

  Vector3 v;
  
  v.x = atoi(argv[1]);
  v.y = atoi(argv[2]);
  v.z = atoi(argv[3]);
  
  v.Print();
  
  Logging::LogLevel(ELogLevel::Info,"Magnitude: %f\n",v.GetMagnitude());
  return 0;
}


