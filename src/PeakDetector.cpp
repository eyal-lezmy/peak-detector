#include "PeakDetector.h"


PeakDetector::PeakDetector() :
valueIndex(0),
lastValue(0),
currentVectorIndex(0),
maxVector(0),
lastMaxVectorIndex(0),
currentFrontLength(0),
frontIncreased(false) {
  resetVector();
  resetLastMaxVector();
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

  updateFrontLength(vector);

  return checkPeak();
}

void PeakDetector::resetVector() {
  //Serial.println("resetVector");
  for (int i=0; i<VECTOR_SIZE; i++) {
    currentVector[i] = 0;
  }
  currentVectorIndex = 0;
  valueIndex = 0;
  frontIncreased = false;
}

void PeakDetector::resetLastMaxVector() {
  //Serial.println("resetLastMaxVector");
  for (int i=0; i<LAST_MAX_VECTORS_SIZE; i++) {
    lastMaxVector[i] = 0;
  }
  lastMaxVectorIndex = 0;
}

int PeakDetector::getVector() {
  int vector = 0;
  for (int i=0; i<VECTOR_SIZE; i++) {
    vector += currentVector[i];
  }
  return vector;
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
    maxVector = 0;
    return;
  }

  // Update the currentFrontLength according to the vector value
  if (vector > 0) {
    currentFrontLength++;
    maxVector = max(vector, maxVector);
    //Serial.print("Increase length");
    //Serial.println(currentFrontLength);
  } else if (vector < 0) {
    currentFrontLength--;
    //Serial.print("Decrease length");
    //Serial.println(currentFrontLength);
  }
}

void PeakDetector::updateVector(int value) {
  currentVector[currentVectorIndex] = value;
  currentVectorIndex = (currentVectorIndex + 1) % VECTOR_SIZE;
}

bool PeakDetector::checkPeak() {
  if (frontIncreased && (currentFrontLength <= -FRONT_LENGTH_THRESHOLD)) {
    // PEAK!
    //Serial.println("Peak detected");
    updateLastMaxVectors(maxVector);
    resetVector();
    return true;
  }

  if (currentFrontLength >= FRONT_LENGTH_THRESHOLD) {
    if (isVectorBigEnough()) {
      frontIncreased = true;
      //Serial.println("front increased");
    } else {
      //Serial.print("vector not big enough, reseting");
      //Serial.println(maxVector);
      resetVector();
    }
  }
  return false;
}

void PeakDetector::updateLastMaxVectors(int value) {
  lastMaxVector[lastMaxVectorIndex] = value;
  lastMaxVectorIndex = (lastMaxVectorIndex + 1) % VECTOR_SIZE;
}

int PeakDetector::getLastMaxVectorsAverage() {
  int vectorSum = 0;
  int vectorCount = 0;
  for (int i=0; i<LAST_MAX_VECTORS_SIZE; i++) {
    if (lastMaxVector[i] > 0) {
      vectorSum += lastMaxVector[i];
      vectorCount++;
    }
  }

  if (vectorCount == 0) {
    return 0;
  }

  return vectorSum/vectorCount;
}

bool PeakDetector::isVectorBigEnough() {
  return maxVector > (getLastMaxVectorsAverage() * MAX_VECTOR_THRESHOLD_RATIO);
}
