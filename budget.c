#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "budget.h"

Department budgets[MAX_DEPARTMENTS];
int budgetCount = 0;

double getPositiveDouble(const char *prompt)
{
    double value;
    char line[100];
    char extra;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            continue;
        }

        if (sscanf(line, "%lf %c", &value, &extra) != 1)
        {
            printf("Invalid number. Try again.\n");
            continue;
        }

        if (value < 0)
        {
            printf("Value cannot be negative. Try again.\n");
            continue;
        }

        return value;
    }
}

static void getNonEmptyString(const char *prompt, char *out, int size)
{
    while (1)
    {
        printf("%s", prompt);

        if (fgets(out, size, stdin) == NULL)
        {
            continue;
        }

        out[strcspn(out, "\n")] = '\0';

        if (strlen(out) == 0)
        {
            printf("Input cannot be empty. Try again.\n");
            continue;
        }

        return;
    }
}

/* ANSI C99 case-insensitive string comparison */
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

int addDepartmentBudget(Department budgetList[], int count)
{
    char name[NAME_LEN];

    if (count >= MAX_DEPARTMENTS)
    {
        printf("Maximum number of departments (%d) reached.\n",
               MAX_DEPARTMENTS);
        return count;
    }

    getNonEmptyString("Enter department name: ", name, NAME_LEN);

    if (departmentExists(budgetList, count, name) != -1)
    {
        printf("Department '%s' already exists.\n", name);
        return count;
    }

    strcpy(budgetList[count].department, name);

    budgetList[count].allocatedBudget =
        getPositiveDouble("Enter allocated budget (N$): ");

    budgetList[count].expenditure = 0.0;

    printf("Budget for '%s' added successfully.\n", name);

    return count + 1;
}

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

    getNonEmptyString("Enter department name: ", name, NAME_LEN);

    index = departmentExists(budgetList, count, name);

    if (index == -1)
    {
        printf("Department '%s' not found.\n", name);
        return;
    }

    amount = getPositiveDouble("Enter expenditure amount (N$): ");

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

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid menu choice. Enter a number from 0 to 5.\n");

            while (getchar() != '\n')
            {
            }

            choice = -1;
            continue;
        }

        while (getchar() != '\n')
        {
        }

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

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);
}