# Individual Contribution Record – Project A

**Student Name:** Abigail Da Cunha
**Student Number:** [226074943]
**Course:** PAP521S – Programming in Practice
**Project:** Project A – Municipal Financial Management System
---

## Assigned Responsibility

Budget Management Module

---

## Functions / Modules Developed

### Files Created
- `budget.h` – Header file with the `Department` struct and function prototypes
- `budget.c` – Implementation of the Budget Management module

### Functions Implemented in `budget.c`

| Function | Purpose |
|----------|---------|
| `budgetMenu()` | Displays the Budget Management sub-menu and handles user navigation |
| `addDepartmentBudget()` | Prompts the user to add a new department with an allocated budget |
| `enterExpenditure()` | Records expenditure against an existing department |
| `calculateRemainingBudget()` | Calculates the remaining budget and displays the status |
| `displayAllBudgets()` | Displays all departments in a formatted table |
| `displayExceededBudgets()` | Lists departments that have exceeded their allocated budget |
| `getPositiveDouble()` | Validates and returns a positive numerical input (helper function) |
| `getNonEmptyString()` | Validates and returns a non-empty string (helper function) |
| `departmentExists()` | Case-insensitive check for existing departments (helper function) |

---

## GitHub Contribution

- **Branch:** `budget-management`
- **Pull Request:** [#2 – Add Budget Management module](https://github.com/JHafeni/MFMS/pull/2)
- **Commit:** `c20e1bf` – "Add Budget Management module"
- **Lines of Code:** 213 insertions across 2 files
- **GitHub Username:** dacunhaabigail10-droid

---

## Testing Performed

### Compilation Testing
- Compiled with: `gcc -std=c99 -Wall -Wextra -c budget.c -o budget.o`
- Result: **Clean compile, no errors or warnings**

### Manual Functional Testing
| Test Case | Expected Result | Actual Result |
|-----------|-----------------|---------------|
| Add a department with valid budget | Department added successfully | ✅ Pass |
| Add a department with negative budget | Rejected with error message | ✅ Pass |
| Add a department with empty name | Rejected with error message | ✅ Pass |
| Add a duplicate department | Rejected with duplicate message | ✅ Pass |
| Enter expenditure within budget | Recorded, status "WITHIN BUDGET" | ✅ Pass |
| Enter expenditure that exceeds budget | Recorded with warning, status "OVER BUDGET" | ✅ Pass |
| Calculate remaining budget for all departments | Correct calculations displayed | ✅ Pass |
| Display all budgets in table format | All departments shown correctly | ✅ Pass |
| Show departments exceeding budget | Only over-budget departments shown | ✅ Pass |
| Enter invalid menu choice | Handled with error message | ✅ Pass |

### Edge Cases Tested
- Negative expenditure values
- Zero budget values
- Very large expenditure values
- More than one department added
- Attempting to enter expenditure when no departments exist

---

## Individual Understanding

I understand the complete Budget Management module, including:
- How the `Department` struct stores department data
- How the array of structs holds multiple departments
- How string comparison (`strcasecmp`) is used to find departments
- How the remaining budget is calculated (`allocatedBudget - expenditure`)
- How over-budget detection works (`expenditure > allocatedBudget`)
- Why input validation is important for financial data
- How the module integrates with `main.c` via the `budgetMenu()` function

---

## Declaration

I confirm that the work described above is my own individual contribution to the group project. I have not submitted another group member's work as my own.

**Signed:** Abigail Dacunha
**Date:** [2.10.2026]