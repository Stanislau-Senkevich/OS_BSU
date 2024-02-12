# Lab 1

This repository contains a realization of first lab implemented in C++ using four files:
- `employee.h`: Header file defining the structure of an employee.
- `creator.cpp`: A program to create and store employee records in a binary file.
- `reporter.cpp`: A program to read employee records from a binary file, calculate salary based on hours worked, and generate a report.
- `main.cpp`: The main program that interacts with the user, orchestrates the creation and reporting of employee records, and manages the flow of execution.

## Usage

### Requirements
- C++ compiler
- Windows operating system

### Instructions
1. Compile the source files:
   ```bash
   g++ creator.cpp -o creator.exe
   g++ reporter.cpp -o reporter.exe
   g++ main.cpp -o main.exe
   ```
2. Run the `main.exe` program:
   ```bash
   main.exe
   ```
3. Follow the instructions provided by the program:
   - Enter the binary file name for storing employee records.
   - Enter the number of employee records to create.
   - Enter information for each employee (ID, name, hours).
   - Enter the output file name for the report.
   - Enter the salary value per one hour.

4. Enjoy :)
