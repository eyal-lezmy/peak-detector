# PeakDetector library

## Description
Input: values from a signal.

The peak detector observes the variations of the signal (the differences between the 5 successive values), to determine if we watch an increasing or decreasing front.
The signal must increase 3 times in a row to be an increasing front. And decrease 3 times in a row to be decreasing.
The peak is validated only if its intensity is at least the half of the average of the previously observed peak intensities.

When the detector find an increasing front followed by a decreasing front, a peak is detected.

## Build the library

    cmake . -G"Unix Makefiles"
    make

## Compile the test

    cd test
    cmake . -G"Unix Makefiles"
    make

## Run the test
    cd test/bin
    ./peak-detector-test
