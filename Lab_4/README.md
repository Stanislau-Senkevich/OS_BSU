# Lab 4

## Project Structure

```plaintext
.
├── CMakeLists.txt          # CMake configuration file
├── docs
│   └── Task.pdf            # Lab task documentation
├── googletest              # Google Test source code
├── include
│   └── sendMsg.h           # Header files
├── README.md               # Project README file
├── src
│   ├── receiver.cpp        # Receiver component source file
│   ├── sender.cpp          # Sender component source file
│   └── sendMsg.cpp         # Source file for sendMsg function
└── tests
    ├── CMakeLists.txt      # CMake configuration for tests
    └── tests.cpp           # Unit tests
```

## Building the Project

1. **Clone the repository:**
    ```bash
    git clone https://github.com/Stanislau-Senkevich/OS_BSU.git
    cd Lab_4
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

- `src/receiver.cpp`: Contains the implementation for the receiver component.
- `src/sender.cpp`: Contains the implementation for the sender component.
- `src/sendMsg.cpp`: Contains the implementation for the `sendMsg` function.

### Header Files

- `include/sendMsg.h`: Header file defining the `sendMsg` function.

### Tests

- `tests/tests.cpp`: Contains the unit tests for the project using Google Test.

### Documentation

- `docs/Task.pdf`: Contains detailed task description and requirements for the lab project.

## Dependencies

- **CMake**: Used for project configuration and build management.
- **Google Test**: Used for unit testing the project.

## Notes

- Ensure you have the necessary development tools installed, such as a C++ compiler, CMake, and Google Test.
- The project assumes a Windows environment due to the usage of Windows-specific APIs.
