#ifndef __PEAK_DETECTOR_H__
#define __PEAK_DETECTOR_H__

#include "UniversalArduino.h"

#define VECTOR_SIZE 5
#define LAST_MAX_VECTORS_SIZE 5
#define FRONT_LENGTH_THRESHOLD 3 // The minimum threshold to consider a front as ascending or descending
#define MINIMUM_VECTOR_SIZE 2 // Minimum size unless we ignore the vector


class PeakDetector {

public:
  PeakDetector();
  ~PeakDetector();

  void addValue(int value);

private:
  int lastValue;
  int currentVector[VECTOR_SIZE]; // The last 5 sensor values
  byte currentVectorIndex; // The position of the last sensor value added into the vector
  int maxVector; // The maximum vector size for the current ascending front

  int lastMaxVector[LAST_MAX_VECTORS_SIZE]; // Maximum vector during the last 5 ascending fronts
  byte lastMaxVectorIndex; // The position of the last sensor value added into the vector

  int currentFrontLength; // The size of the current front (ascending or descending)
  bool frontIncreased;

  void resetVector();
  void resetLastMaxVector();
  int getVector();
  void updateFrontLength(int vector);
  void updateVector(int value);
  void checkPeak();
  void updateLastMaxVectors(int value);
  int getLastMaxVectorsAverage();
  bool isVectorBigEnough();
  void peak();

};

#endif
