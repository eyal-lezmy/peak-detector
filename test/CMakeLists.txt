project(PeakDetectorTest)

set(EXECUTABLE_OUTPUT_PATH bin/)

include_directories(
  ../peak-detector
  ../universal-arduino/include
)

link_directories(../lib)

add_executable(
  peak-detector-test
  main.cpp
)

target_link_libraries(
  peak-detector-test
  PeakDetector
)
