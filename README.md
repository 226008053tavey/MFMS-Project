# MFMS

## PAP521S Project A - Municipal Financial Management System

The Municipal Financial Management System (MFMS) is a menu-driven
application developed in ANSI C (C99) for PAP521S Programming in Practice.

The system demonstrates programming concepts including variables,
data types, input validation, decisions, loops, arrays, strings,
functions, modular programming, and GitHub collaboration.

## System Features

- Employee Management
  - Add employees
  - Display employees
  - Search employees by ID or name
  - Calculate employee salary

- Budget Management
  - Add department budgets
  - Record expenditure
  - Calculate remaining budgets
  - Display budget information
  - Identify departments exceeding their budgets

- Supplier Management
  - Add suppliers
  - Display suppliers
  - Search suppliers by name
  - Save supplier records
  - Load supplier records

- Asset Management
  - Add assets
  - Display assets
  - Search assets by ID or name

- Reports
  - Employee salary report
  - Budget report
  - Supplier report
  - Asset report

- Input Validation
  - Menu choice validation
  - Positive numerical input validation
  - Empty text validation
  - Duplicate ID/department checks

## Programming Language

ANSI C (C99)

## Development Environment

- Visual Studio Code
- GCC
- GitHub

## Project Structure

| File | Purpose |
|---|---|
| main.c | Main menu and system integration |
| employees.c / employees.h | Employee management |
| budget.c / budget.h | Budget management |
| suppliers.c / suppliers.h | Supplier management |
| assets.c / assets.h | Asset management |
| reports.c / reports.h | System reports |
| validation.c / validation.h | Input validation |
| test_validation.c | Validation testing |

## Group Responsibilities

| Student | Responsibility |
|---|---|
| Student 1 | Employee Management |
| Student 2 | Budget Management |
| Student 3 | Supplier Management |
| Student 4 | Asset Management |
| Student 5 | Reports |
| Student 6 | Functions, Integration and Validation |
| Student 7 | Testing, Documentation and Git Coordination |

## Compilation

The complete system can be compiled using GCC:

gcc -std=c99 -Wall -Wextra -pedantic main.c employees.c budget.c suppliers.c assets.c reports.c validation.c -o mfms.exe

The program can then be run from the terminal.

## Testing

The system was tested for:

- Main menu navigation
- Employee management
- Employee searching
- Salary calculation
- Budget calculations
- Over-budget detection
- Duplicate department prevention
- Supplier management
- Supplier searching
- Supplier file saving and loading
- Asset management
- Asset searching
- Reports
- Invalid menu choices
- Input validation

## Project Objective

The objective of Project A is to develop a functional foundation
version of a Municipal Financial Management System using the
programming concepts covered in PAP521S.
