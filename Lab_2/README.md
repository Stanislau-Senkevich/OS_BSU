# Lab 2

This lab demonstrates multi-threaded array operations using C++ on Windows. The program calculates the minimum, maximum, and average of an array of integers concurrently using separate threads.

## Files

- `parameters.h`: Header file containing struct definitions for parameter passing.
- `main.cpp`: Main C++ source code file implementing multi-threaded array operations.

## Requirements

- Windows operating system.
- C++ compiler that supports C++11 standard.

## How to Run

1. Compile the `main.cpp` file using a C++ compiler.
2. Run the compiled executable.

## Description

### `parameters.h`

Contains struct definitions for parameter passing between threads.

- `minMaxParameters`: Struct holding parameters for calculating minimum and maximum values.
- `sumParameters`: Struct holding parameters for calculating the average.

### `main.cpp`

- Includes necessary headers.
- Defines global constants for sleep durations.
- Implements `min_max` function for calculating minimum and maximum values concurrently.
- Implements `average` function for calculating the average concurrently.
- Defines `updateArray` function to update the array based on calculated values.
- Implements `main` function:
    - Prompts the user to enter the size of the array and the integers.
    - Creates threads for calculating minimum and maximum values (`min_max`) and the average (`average`).
    - Waits for threads to finish execution.
    - Updates the array with calculated values.
    - Prints the original and updated arrays.
