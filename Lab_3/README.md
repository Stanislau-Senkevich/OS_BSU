# Lab 3

This project consists of three files: `worker.h`, `worker.cpp`, and `main.cpp`, which collectively implements a solution for the third lab work.

## Files

- `worker.h`: Contains the declaration of the `Worker` class along with its configuration struct and member functions.
- `worker.cpp`: Implements the member functions declared in `worker.h`, including thread initialization and marker function.
- `main.cpp`: Contains the `main()` function where the multithreading scenario is orchestrated.

## Compilation and Execution

To compile the project, ensure you have a C++ compiler set up along with the Windows SDK for accessing the Windows API functions.

```bash
$ g++ main.cpp worker.cpp -o Lab_3 -lkernel32 -luser32 -lgdi32
```

After compilation, execute the program:

```bash
$ ./Lab_3
```

## Functionality

- The program prompts the user to input the size of the array and the number of threads to spawn.
- Threads are initialized and started, each responsible for marking elements in the array with their respective thread numbers.
- The main thread waits for events from each worker thread, prints the array state, and prompts the user to stop a specific thread.
- Once a thread is marked for termination, its flag is set, and the thread finishes its execution.
- All threads are joined, resources are cleaned up, and the program exits.

## Dependencies

- This project depends on the Windows API for thread management (`windows.h`).
- It is written in standard C++11.

