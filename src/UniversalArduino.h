#ifndef __UNIVERSAL_ARDUINO_H__
#define __UNIVERSAL_ARDUINO_H__


#if defined(_WIN32) || defined(__APPLE__) || defined(__linux__) // Computer
#include <stdio.h>

typedef unsigned char byte;

class Serial {

public:
  static void print(const char *message) {
    printf("%s", message);
  }

  static void println(const char *message) {
    printf("%s\n", message);
  }
  static void print(int value) {
    printf("%d", value);
  }

  static void println(int value) {
    printf("%d\n", value);
  }


};

#endif //defined(_WIN32) || defined(__APPLE__) || defined(__linux__)

#endif //__UNIVERSAL_ARDUINO_H__
