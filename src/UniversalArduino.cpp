#include "UniversalArduino.h"

#if defined(_WIN32) || defined(__APPLE__) || defined(__linux__) // Computer

Serial_ Serial;

int abs(int value) {
    return value >= 0 ? value : -value;
}

int max(int value1, int value2) {
    return value1 > value2 ? value1 : value2;
}

#endif
