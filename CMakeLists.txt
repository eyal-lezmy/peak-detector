project(PeakDetector)

set(LIBRARY_OUTPUT_PATH lib/)

include_directories(include)

file(
  GLOB_RECURSE
  source_files
  src/*
  include/*
)

add_library(
  PeakDetector
  STATIC
  ${source_files}
)
