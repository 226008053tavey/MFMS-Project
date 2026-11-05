#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "budget.h"
#include "validation.h"

/* Shared budget data */
Department budgets[MAX_DEPARTMENTS];
int budgetCount = 0;

/* Case-insensitive string comparison */
static int stringsEqualIgnoreCase(const char *first, const char *second)
{
    while (*first != '\0' && *second != '\0')
    {
        if (tolower((unsigned char)*first) !=
            tolower((unsigned char)*second))
        {
            return 0;
        }

        first++;
        second++;
    }

    return *first == '\0' && *second == '\0';
}

/* Check whether a department already exists */
static int departmentExists(Department budgetList[],
                            int count,
                            const char *name)
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (stringsEqualIgnoreCase(budgetList[i].department, name))
        {
            return i;
        }
    }

    return -1;
}

/* Add a department budget */
int addDepartmentBudget(Department budgetList[], int count)
{
    char name[NAME_LEN];

    if (count >= MAX_DEPARTMENTS)
    {
        printf("Maximum number of departments (%d) reached.\n",
               MAX_DEPARTMENTS);
        return count;
    }

    while (1)
    {
       printf("Enter department name (Q to cancel): ");

if (!getValidString(name, NAME_LEN))
{
    printf("Invalid input. Please try again.\n");
    continue;
}

if (strcmp(name, "Q") == 0 || strcmp(name, "q") == 0)
{
    printf("Adding department cancelled.\n");
    return count;
}

        if (!getValidString(name, NAME_LEN))
        {
            printf("Invalid input. Please try again.\n");
            continue;
        }

        if (strcmp(name, "-1") == 0)
        {
            printf("Error: -1 is not a valid department name. Please try again.\n");
            continue;
        }

        if (departmentExists(budgetList, count, name) != -1)
        {
            printf("Department '%s' already exists. Please try again.\n", name);
            continue;
        }

        break;
    }

    strcpy(budgetList[count].department, name);

    printf("Enter allocated budget (N$) or Q to cancel: ");

if (!getValidPositiveDoubleOrCancel(&budgetList[count].allocatedBudget))
{
    printf("Adding department cancelled.\n");
    return count;
}
    budgetList[count].expenditure = 0.0;

    printf("Budget for '%s' added successfully.\n", name);

    return count + 1;
}

/* Enter expenditure for an existing department */
void enterExpenditure(Department budgetList[], int count)
{
    char name[NAME_LEN];
    int index;
    double amount;

    if (count == 0)
    {
        printf("No departments registered yet. Add a budget first.\n");
        return;
    }

    printf("Enter department name: ");

    if (!getValidString(name, NAME_LEN))
    {
        printf("Unable to read department name.\n");
        return;
    }

    index = departmentExists(budgetList, count, name);

    if (index == -1)
    {
        printf("Department '%s' not found.\n", name);
        return;
    }

    printf("Enter expenditure amount (N$): ");
    amount = getValidPositiveDouble();

    budgetList[index].expenditure += amount;

    printf("Expenditure of N$%.2f recorded for %s.\n",
           amount,
           budgetList[index].department);

    if (budgetList[index].expenditure >
        budgetList[index].allocatedBudget)
    {
        printf("WARNING: %s has EXCEEDED its budget!\n",
               budgetList[index].department);
    }
}

/* Calculate remaining budget */
void calculateRemainingBudget(Department budgetList[], int count)
{
    int i;

    if (count == 0)
    {
        printf("No budget data available.\n");
        return;
    }

    printf("\n==================== BUDGET BALANCES ====================\n");

    for (i = 0; i < count; i++)
    {
        double remaining =
            budgetList[i].allocatedBudget -
            budgetList[i].expenditure;

        printf("\nDepartment      : %s\n",
               budgetList[i].department);

        printf("Allocated Budget: N$%.2f\n",
               budgetList[i].allocatedBudget);

        printf("Expenditure     : N$%.2f\n",
               budgetList[i].expenditure);

        printf("Remaining Budget: N$%.2f\n",
               remaining);

        printf("Status          : %s\n",
               remaining < 0
               ? "OVER BUDGET"
               : "WITHIN BUDGET");
    }

    printf("=========================================================\n");
}

/* Display all department budgets */
void displayAllBudgets(Department budgetList[], int count)
{
    int i;

    if (count == 0)
    {
        printf("No departments registered.\n");
        return;
    }

    printf("\n%-20s %15s %15s %15s %-15s\n",
           "Department",
           "Allocated",
           "Expenditure",
           "Remaining",
           "Status");

    printf("---------------------------------------------------------------------------------\n");

    for (i = 0; i < count; i++)
    {
        double remaining =
            budgetList[i].allocatedBudget -
            budgetList[i].expenditure;

        printf("%-20s %15.2f %15.2f %15.2f %-15s\n",
               budgetList[i].department,
               budgetList[i].allocatedBudget,
               budgetList[i].expenditure,
               remaining,
               remaining < 0
               ? "OVER BUDGET"
               : "WITHIN BUDGET");
    }
}

/* Display departments that have exceeded their budgets */
void displayExceededBudgets(Department budgetList[], int count)
{
    int i;
    int found = 0;

    printf("\n--- Departments Exceeding Budget ---\n");

    for (i = 0; i < count; i++)
    {
        if (budgetList[i].expenditure >
            budgetList[i].allocatedBudget)
        {
            double over =
                budgetList[i].expenditure -
                budgetList[i].allocatedBudget;

            printf("%-20s over by N$%.2f\n",
                   budgetList[i].department,
                   over);

            found = 1;
        }
    }

    if (!found)
    {
        printf("No departments have exceeded their budget.\n");
    }
}

/* Budget management menu */
void budgetMenu(void)
{
    int choice;

    do
    {
        printf("\n===== BUDGET MANAGEMENT =====\n");
        printf("1. Add Department Budget\n");
        printf("2. Enter Expenditure\n");
        printf("3. Calculate Remaining Budget\n");
        printf("4. Display All Budgets\n");
        printf("5. Show Departments Exceeding Budget\n");
        printf("0. Back to Main Menu\n");

        choice = getValidMenuChoice(0, 5);

        switch (choice)
        {
            case 1:
                budgetCount =
                    addDepartmentBudget(budgets, budgetCount);
                break;

            case 2:
                enterExpenditure(budgets, budgetCount);
                break;

            case 3:
                calculateRemainingBudget(budgets, budgetCount);
                break;

            case 4:
                displayAllBudgets(budgets, budgetCount);
                break;

            case 5:
                displayExceededBudgets(budgets, budgetCount);
                break;

            case 0:
                printf("Returning to main menu...\n");
                break;
        }

    } while (choice != 0);
}