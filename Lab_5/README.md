# Lab 5

## Project Structure

```
├── CMakeLists.txt
├── docs
│   └── Task.pdf
├── googletest
├── include
│   ├── command.h
│   └── employee.h
├── README.md
├── src
│   ├── client.cpp
│   ├── employee.cpp
│   └── server.cpp
└── tests
    ├── CMakeLists.txt
    └── tests.cpp
```

### Description of Directories and Key Files

- **CMakeLists.txt**: The CMake build script for the project.
- **docs/Task.pdf**: The task description and requirements for the project.
- **googletest/**: The Google Test framework for unit testing.
- **include/**: Directory containing header files:
    - `command.h`: Header file for command definitions and structures.
    - `employee.h`: Header file for the employee structure and related functions.
- **src/**: Directory containing source files:
    - `client.cpp`: Implementation of the client processes.
    - `employee.cpp`: Implementation of employee-related functions.
    - `server.cpp`: Implementation of the server process handling employee data.
- **tests/**: Directory containing unit tests:
    - `CMakeLists.txt`: The CMake build script for the tests.
    - `tests.cpp`: Unit tests for the project.

## Requirements

- CMake 3.10 or higher
- C++11 or higher
- Google Test

## Building the Project

1. Clone the repository:
    ```bash
    git clone https://github.com/Stanislau-Senkevich/OS_BSU.git
    cd Lab_5
    ```

2. Create a build directory and navigate to it:

   ```bash
   mkdir build
   cd build
   ```

3. Configure the project using CMake:

   ```bash
   cmake ..
   ```

4. Build the project:

   ```bash
   cmake --build .
   ```

## Running the Application

### Server

To start the server:

```bash
./server
```

### Client

To start a client:

```bash
./client <client_id>
```

Replace `<client_id>` with a unique identifier for each client.

## Running the Tests

1. Ensure you are in the `build` directory:

   ```sh
   cd build
   ```

2. Run the tests using CTest:

   ```sh
   ctest
   ```

This will execute all unit tests defined in `tests/tests.cpp` and display the results.
