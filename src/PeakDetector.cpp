#include "PeakDetector.h"


PeakDetector::PeakDetector() :
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
  Serial.println(diffValue);

  updateVector(diffValue);

  int vector = getVector();
  updateFrontLength(vector);

  return checkPeak();
}

void PeakDetector::resetVector() {
  Serial.println("resetVector");
  for (int i=0; i<VECTOR_SIZE; i++) {
    currentVector[i] = 0;
  }
}

void PeakDetector::resetLastMaxVector() {
  Serial.println("resetVector");
  for (int i=0; i<VECTOR_SIZE; i++) {
    currentVector[i] = 0;
  }
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
    return;
  }
  // If the vector has a different sign than the currentFrontLength, we reset the length
  if (vector*currentFrontLength > 0) {
    currentFrontLength = 0;
    maxVector = 0;
    return;
  }

  // Update the currentFrontLength according to the vector value
  if (vector > 0) {
    currentFrontLength++;
    maxVector = max(vector, maxVector);
    Serial.println("Increase length");
    Serial.println(currentFrontLength);
  } else if (vector < 0) {
    currentFrontLength--;
    Serial.println("Decrease length");
    Serial.println(currentFrontLength);
  }
}

void PeakDetector::updateVector(int value) {
  currentVector[currentVectorIndex] = value;
  currentVectorIndex = (currentVectorIndex + 1) % VECTOR_SIZE;
}

bool PeakDetector::checkPeak() {
  if (frontIncreased && currentFrontLength <= -FRONT_LENGTH_THRESHOLD) {
    // PEAK!
    Serial.println("Peak detected");
    updateLastMaxVectors(maxVector);
    resetVector();
    return true;
  }

  if (currentFrontLength >= FRONT_LENGTH_THRESHOLD) {
    if (isVectorBigEnough()) {
      frontIncreased = true;
      Serial.println("front increased");
    } else {
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
  return vectorSum/vectorCount;
}

bool PeakDetector::isVectorBigEnough() {
  return maxVector > (getLastMaxVectorsAverage() / 2);
}
