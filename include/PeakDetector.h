#ifndef __PEAK_DETECTOR_H__
#define __PEAK_DETECTOR_H__

#include "UniversalArduino.h"

#define VECTOR_SIZE 5
#define LAST_MAX_VECTORS_SIZE 5
#define FRONT_LENGTH_THRESHOLD 3 // The minimum threshold to consider a front as ascending or descending
#define MINIMUM_VECTOR_SIZE 2 // Minimum size unless we ignore the vector
#define MAX_PEAK_INTENSITY_THRESHOLD_RATIO 0.5f //Minimum ratio of the value maxVector/maxVectorAverage of a vector to be considered as a front increase

class PeakDetector {

//TODO good results, check the micro peak handling in 205 as it seems to signal it as a peak, but it ignore the big peak coming right after in 211

public:
  PeakDetector();
  ~PeakDetector();

  bool addValue(int value);

private:
  byte valueIndex; // Variable used to dismiss analysis until the dataset reached a mimum size
  int lastValue;
  int currentVector[VECTOR_SIZE]; // The last 5 sensor values
  byte currentVectorIndex; // The position of the last sensor value added into the vector

  int maxPeakIntensity; // The maximum vector size for the current ascending front
  int currentPeakIntensity[FRONT_LENGTH_THRESHOLD]; // The sum of the last 3 vectors value
  int currentPeakIntensityIndex;

  int lastMaxPeakIntensity[LAST_MAX_VECTORS_SIZE]; // Maximum vector during the last 5 ascending fronts
  byte lastMaxPeakIntensityIndex; // The position of the last sensor value added into the vector

  int currentFrontLength; // The size of the current front, represents the number of times we observe the value increasing or decreasing
  bool frontIncreased;

  void resetVector();
  void resetlastMaxPeakIntensity();
  int getVector();
  void updateFrontLength(int vector);
  void updateVector(int value);
  bool checkPeak();
  int getCurrentPeakIntensity();
  void updateCurrentPeakIntensity(int vector);
  void updatelastMaxPeakIntensity(int value);
  int getlastMaxPeakIntensityAverage();
  bool isMaxPeakIntensityBigEnough();
  void peak();

};

#endif // __PEAK_DETECTOR_H__
