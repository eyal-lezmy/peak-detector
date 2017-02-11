project(PeakDetector)

set(LIBRARY_OUTPUT_PATH lib/)

include_directories(
  peak-detector/
  universal-arduino/include
)

file(
  GLOB_RECURSE
  source_files
  peak-detector/*
  universal-arduino/*
)

add_library(
  PeakDetector
  STATIC
  ${source_files}
)
