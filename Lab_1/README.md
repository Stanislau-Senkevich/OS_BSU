# Lab 1

This project demonstrates a multi-threaded application using C++ and the Windows API. It includes unit tests using Google Test.

## Project Structure

```plaintext
├── CMakeLists.txt          # CMake configuration file
├── docs
│   └── Task.pdf            # Task
├── googletest              # Google Test source code
├── include
│   └── employee.h          # Header files
├── README.md               # Project README file
├── src
│   ├── creator.cpp         # Source file for creator component
│   ├── main.cpp            # Main source file
│   └── reporter.cpp        # Source file for reporter component
└── tests
    ├── CMakeLists.txt      # CMake configuration for tests
    └── tests.cpp           # Unit tests
```

## Building the Project

1. **Clone the repository:**
    ```bash
    git clone https://github.com/Stanislau-Senkevich/OS_BSU.git
    cd Lab_1
    ```

2. **Create a build directory:**
    ```bash
    mkdir build
    cd build
    ```

3. **Configure the project using CMake:**
    ```bash
    cmake ..
    ```

4. **Build the project:**
    ```bash
    cmake --build .
    ```

## Running the Tests

1. **Run the tests using CTest:**
    ```bash
    ctest
    ```

2. **Alternatively, you can run the test executable directly:**
    ```bash
    ./tests/runUnitTests
    ```

## Project Components

### Source Files

- `src/creator.cpp`: Contains the implementation for the creator component.
- `src/main.cpp`: The main entry point for the application.
- `src/reporter.cpp`: Contains the implementation for the reporter component.

### Header Files

- `include/employee.h`: Header file defining structures and functions related to employee records.

### Tests

- `tests/tests.cpp`: Contains the unit tests for the project using Google Test.

### Documentation

- `docs/01-Lab Report.pdf`: Contains detailed documentation and lab report for the project.

## Dependencies

- **CMake**: Used for project configuration and build management.
- **Google Test**: Used for unit testing the project.

## Notes

- Ensure you have the necessary development tools installed, such as a C++ compiler, CMake, and Google Test.
- The project assumes a Windows environment due to the usage of Windows-specific APIs (e.g., `CreateEvent`, `CreateThread`).