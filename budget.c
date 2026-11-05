#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "budget.h"
#include "validation.h"


/* Case-insensitive check for existing department */
static int departmentExists(Department budgets[], int count, const char *name) {
    for (int i = 0; i < count; i++) {
        if (strcasecmp(budgets[i].department, name) == 0) return i;
    }
    return -1;
}

/* ---------- CORE FUNCTIONS ---------- */

int addDepartmentBudget(Department budgets[], int count) {
    if (count >= MAX_DEPARTMENTS) {
        printf("Maximum number of departments (%d) reached.\n", MAX_DEPARTMENTS);
        return count;
    }

    char name[NAME_LEN];

    printf("Enter department name: ");

    if (!getValidString(name, NAME_LEN)) {
        printf("Unable to read department name.\n");
        return count;
    }

    if (departmentExists(budgets, count, name) != -1) {
        printf("Department '%s' already exists. Use 'Enter Expenditure' to update it.\n", name);
        return count;
    }

    strcpy(budgets[count].department, name);

    printf("Enter allocated budget (N$): ");
    budgets[count].allocatedBudget = getValidPositiveDouble();

    budgets[count].expenditure = 0.0;

    printf("Budget for '%s' added successfully.\n", name);

    return count + 1;
}
/* Enter expenditure for an existing department */
void enterExpenditure(Department budgets[], int count) {
    if (count == 0) {
        printf("No departments registered yet. Add a budget first.\n");
        return;
    }

    char name[NAME_LEN];

    printf("Enter department name: ");

    if (!getValidString(name, NAME_LEN)) {
        printf("Unable to read department name.\n");
        return;
    }

    int idx = departmentExists(budgets, count, name);

    if (idx == -1) {
        printf("Department '%s' not found.\n", name);
        return;
    }

    double amount;

    printf("Enter expenditure amount (N$): ");
    amount = getValidPositiveDouble();

    budgets[idx].expenditure += amount;

    printf("Expenditure of N$%.2f recorded for %s.\n",
           amount, budgets[idx].department);

    if (budgets[idx].expenditure > budgets[idx].allocatedBudget) {
        printf("WARNING: %s has EXCEEDED its budget!\n",
               budgets[idx].department);
    }
}

/* Calculate + display remaining budget and status for each department */
void calculateRemainingBudget(Department budgets[], int count) {
    if (count == 0) {
        printf("No budget data available.\n");
        return;
    }

    printf("\n==================== BUDGET BALANCES ====================\n");
    for (int i = 0; i < count; i++) {
        double remaining = budgets[i].allocatedBudget - budgets[i].expenditure;
        printf("\nDepartment      : %s\n", budgets[i].department);
        printf("Allocated Budget: N$%.2f\n", budgets[i].allocatedBudget);
        printf("Expenditure     : N$%.2f\n", budgets[i].expenditure);
        printf("Remaining Budget: N$%.2f\n", remaining);
        printf("Status          : %s\n",
               remaining < 0 ? "OVER BUDGET" : "WITHIN BUDGET");
    }
    printf("=========================================================\n");
}

/* Display all departments with budget info */
void displayAllBudgets(Department budgets[], int count) {
    if (count == 0) {
        printf("No departments registered.\n");
        return;
    }

    printf("\n%-20s %15s %15s %15s %-15s\n",
           "Department", "Allocated", "Expenditure", "Remaining", "Status");
    printf("---------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        double remaining = budgets[i].allocatedBudget - budgets[i].expenditure;
        printf("%-20s %15.2f %15.2f %15.2f %-15s\n",
               budgets[i].department,
               budgets[i].allocatedBudget,
               budgets[i].expenditure,
               remaining,
               remaining < 0 ? "OVER BUDGET" : "WITHIN BUDGET");
    }
}

/* List departments that exceeded their allocated budget */
void displayExceededBudgets(Department budgets[], int count) {
    int found = 0;
    printf("\n--- Departments Exceeding Budget ---\n");
    for (int i = 0; i < count; i++) {
        if (budgets[i].expenditure > budgets[i].allocatedBudget) {
            double over = budgets[i].expenditure - budgets[i].allocatedBudget;
            printf("%-20s over by N$%.2f\n", budgets[i].department, over);
            found = 1;
        }
    }
    if (!found) printf("No departments have exceeded their budget.\n");
}

void budgetMenu(void) {
    Department budgets[MAX_DEPARTMENTS];
    int count = 0;
    int choice;

    do {
        printf("\n===== BUDGET MANAGEMENT =====\n");
        printf("1. Add Department Budget\n");
        printf("2. Enter Expenditure\n");
        printf("3. Calculate Remaining Budget\n");
        printf("4. Display All Budgets\n");
        printf("5. Show Departments Exceeding Budget\n");
        printf("0. Back to Main Menu\n");

choice = getValidMenuChoice(0, 5);

        switch (choice) {
            case 1: count = addDepartmentBudget(budgets, count); break;
            case 2: enterExpenditure(budgets, count);            break;
            case 3: calculateRemainingBudget(budgets, count);    break;
            case 4: displayAllBudgets(budgets, count);           break;
            case 5: displayExceededBudgets(budgets, count);      break;
            case 0: printf("Returning to main menu...\n");       break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}
