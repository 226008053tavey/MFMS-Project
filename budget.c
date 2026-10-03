#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "budget.h"

/* Reads a positive double, rejects negatives / non-numbers */
double getPositiveDouble(const char *prompt) {
    double value;
    char line[100];
    while (1) {
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) == NULL) continue;
        if (sscanf(line, "%lf", &value) != 1) {
            printf("Invalid number. Try again.\n");
            continue;
        }
        if (value < 0) {
            printf("Value cannot be negative. Try again.\n");
            continue;
        }
        return value;
    }
}

/* Reads a non-empty string */
static void getNonEmptyString(const char *prompt, char *out, int size) {
    while (1) {
        printf("%s", prompt);
        if (fgets(out, size, stdin) == NULL) continue;
        out[strcspn(out, "\n")] = '\0';   /* strip newline */
        if (strlen(out) == 0) {
            printf("Input cannot be empty. Try again.\n");
            continue;
        }
        return;
    }
}

/* Case-insensitive check for existing department */
static int departmentExists(Department budgets[], int count, const char *name) {
    for (int i = 0; i < count; i++) {
        if (strcasecmp(budgets[i].department, name) == 0) return i;
    }
    return -1;
}

/* ---------- CORE FUNCTIONS ---------- */

/* Add a new department budget. Returns new count. */
int addDepartmentBudget(Department budgets[], int count) {
    if (count >= MAX_DEPARTMENTS) {
        printf("Maximum number of departments (%d) reached.\n", MAX_DEPARTMENTS);
        return count;
    }

    char name[NAME_LEN];
    getNonEmptyString("Enter department name: ", name, NAME_LEN);

    if (departmentExists(budgets, count, name) != -1) {
        printf("Department '%s' already exists. Use 'Enter Expenditure' to update it.\n", name);
        return count;
    }

    strcpy(budgets[count].department, name);
    budgets[count].allocatedBudget = getPositiveDouble("Enter allocated budget (N$): ");
    budgets[count].expenditure     = 0.0;

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
    getNonEmptyString("Enter department name: ", name, NAME_LEN);

    int idx = departmentExists(budgets, count, name);
    if (idx == -1) {
        printf("Department '%s' not found.\n", name);
        return;
    }

    double amount = getPositiveDouble("Enter expenditure amount (N$): ");
    budgets[idx].expenditure += amount;

    printf("Expenditure of N$%.2f recorded for %s.\n", amount, budgets[idx].department);

    if (budgets[idx].expenditure > budgets[idx].allocatedBudget) {
        printf("WARNING: %s has EXCEEDED its budget!\n", budgets[idx].department);
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
        printf("Enter your choice: ");

        char line[20];
        if (fgets(line, sizeof(line), stdin) == NULL) continue;
        if (sscanf(line, "%d", &choice) != 1) {
            printf("Invalid menu choice.\n");
            continue;
        }

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