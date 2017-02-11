#ifndef __UNIVERSAL_ARDUINO_H__
#define __UNIVERSAL_ARDUINO_H__


#if defined(_WIN32) || defined(__APPLE__) || defined(__linux__) // Computer
#include <stdio.h>

typedef unsigned char byte;

class Serial_ {

public:
  void print(const char *message) {
    printf("%s", message);
  }

  void println(const char *message) {
    printf("%s\n", message);
  }

  void print(int value) {
    printf("%d", value);
  }

  void println(int value) {
    printf("%d\n", value);
  }

};

extern Serial_ Serial;

int abs(int value);
int max(int value1, int value2);

#endif //defined(_WIN32) || defined(__APPLE__) || defined(__linux__)

#endif //__UNIVERSAL_ARDUINO_H__
