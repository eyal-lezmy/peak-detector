#include "PeakDetector.h"


PeakDetector::PeakDetector() :
valueIndex(0),
lastValue(0),
currentVectorIndex(0),
maxPeakIntensity(0),
lastMaxPeakIntensityIndex(0),
currentFrontLength(0),
frontIncreased(false) {
  resetVector();
  resetlastMaxPeakIntensity();
}

PeakDetector::~PeakDetector() {
}

bool PeakDetector::addValue(int value) {
  int diffValue = value - lastValue;
  lastValue = value;

  //Serial.print("diff ");
  //Serial.println(diffValue);
  updateVector(diffValue);

  if (valueIndex < VECTOR_SIZE) {
    valueIndex++;
    return false;
  }

  int vector = getVector();
  //Serial.print("Vector ");
  //Serial.println(vector);
  updateCurrentPeakIntensity(vector);
  updateFrontLength(vector);

  return checkPeak();
}

void PeakDetector::resetVector() {
  //Serial.println("resetVector");
  for (int i=0; i<VECTOR_SIZE; i++) {
    currentVector[i] = 0;
  }
  for (int i=0; i<FRONT_LENGTH_THRESHOLD; i++) {
    currentPeakIntensity[i] = 0;
  }
  currentVectorIndex = 0;
  valueIndex = 0;
  frontIncreased = false;
}

void PeakDetector::resetlastMaxPeakIntensity() {
  //Serial.println("resetlastMaxPeakIntensity");
  for (int i=0; i<LAST_MAX_VECTORS_SIZE; i++) {
    lastMaxPeakIntensity[i] = 0;
  }
  lastMaxPeakIntensityIndex = 0;
}

int PeakDetector::getVector() {
  int vector = 0;
  for (int i=0; i<VECTOR_SIZE; i++) {
    vector += currentVector[i];
  }
  return vector;
}

int PeakDetector::getCurrentPeakIntensity() {
  int intensity = 0;
  for (int i=0; i<FRONT_LENGTH_THRESHOLD; i++) {
    intensity += currentPeakIntensity[i];
  }
  return intensity;
}

void PeakDetector::updateFrontLength(int vector) {
  // If the vector is not enough big to be considered, we ignore it
  if (abs(vector) < MINIMUM_VECTOR_SIZE) {
    //Serial.println("vector too small");
    return;
  }
  // If the vector has a different sign than the currentFrontLength, we reset the length
  if (vector*currentFrontLength < 0) {
    //Serial.println("vector and frontLength not same sign, we reset the length");
    currentFrontLength = 0;
    // On frontIncreased mode, we want to keep the maxPeakIntensity to add it later
    // to updatelastMaxPeakIntensitys if a peak is detected
    if (!frontIncreased) {
      maxPeakIntensity = 0;
    }
    return;
  }

  // Update the currentFrontLength according to the vector value
  if (vector > 0) {
    currentFrontLength++;
    maxPeakIntensity = max(getCurrentPeakIntensity(), maxPeakIntensity);
    //Serial.print("Increase length, maxPeakIntensity ");
    //Serial.println(maxPeakIntensity);
  } else if (vector < 0) {
    currentFrontLength--;
    //Serial.print("Decrease length");
    //Serial.println(currentFrontLength);
  }
}

void PeakDetector::updateCurrentPeakIntensity(int vector) {
  currentPeakIntensity[currentPeakIntensityIndex] = vector;
  currentPeakIntensityIndex = (currentPeakIntensityIndex + 1) % FRONT_LENGTH_THRESHOLD;
}

void PeakDetector::updateVector(int value) {
  currentVector[currentVectorIndex] = value;
  currentVectorIndex = (currentVectorIndex + 1) % VECTOR_SIZE;
}

bool PeakDetector::checkPeak() {
  if (frontIncreased && (currentFrontLength <= -FRONT_LENGTH_THRESHOLD)) {
    // PEAK!
    //Serial.println("Peak detected");
    updatelastMaxPeakIntensity(maxPeakIntensity);
    resetVector();
    return true;
  }

  if (currentFrontLength >= FRONT_LENGTH_THRESHOLD) {
    if (isMaxPeakIntensityBigEnough()) {
      frontIncreased = true;
      //Serial.println("front increased");
    } else {
      //Serial.println("Vector not big enough");
    }
  }
  return false;
}

void PeakDetector::updatelastMaxPeakIntensity(int value) {
  lastMaxPeakIntensity[lastMaxPeakIntensityIndex] = value;
  lastMaxPeakIntensityIndex = (lastMaxPeakIntensityIndex + 1) % VECTOR_SIZE;
}

int PeakDetector::getlastMaxPeakIntensityAverage() {
  //Serial.print("getlastMaxPeakIntensitysAverage ");
  int vectorSum = 0;
  int vectorCount = 0;
  for (int i=0; i<LAST_MAX_VECTORS_SIZE; i++) {
    if (lastMaxPeakIntensity[i] > 0) {
      //Serial.print(lastMaxPeakIntensity[i]);
      //Serial.print(" ");
      vectorSum += lastMaxPeakIntensity[i];
      vectorCount++;
    }
  }
  //Serial.println(" ");
  if (vectorCount == 0) {
    return 0;
  }

  return vectorSum/vectorCount;
}

bool PeakDetector::isMaxPeakIntensityBigEnough() {
  int maxPeakIntensityAverage = getlastMaxPeakIntensityAverage();
  //Serial.print("isMaxPeakIntensityBigEnough ");
  //Serial.print(maxPeakIntensity);
  //Serial.print(" compared to ");
  //Serial.println(maxPeakIntensityAverage * MAX_PEAK_INTENSITY_THRESHOLD_RATIO);
  return maxPeakIntensity > (maxPeakIntensityAverage * MAX_PEAK_INTENSITY_THRESHOLD_RATIO);
}
