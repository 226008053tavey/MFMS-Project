#include <stdio.h>

#include "report.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "validation.h"

/* Display employee information and salary statistics. */
static void employeeReport(void)
{
    int i;
    const Employee *emp;

    printf("\n========== EMPLOYEE REPORT ==========\n");

    if (getEmployeeCount() == 0) {
        printf("No employee records found.\n");
        return;
    }

    printf("%-10s %-22s %-20s %-12s\n",
           "ID", "Name", "Department", "Gross Salary");

    printf("---------------------------------------------------------------------\n");

    for (i = 0; i < getEmployeeCount(); i++) {
        emp = getEmployeeByIndex(i);

        if (emp != NULL) {
            printf("%-10s %-22s %-20s N$%-10.2f\n",
                   emp->id,
                   emp->name,
                   emp->department,
                   calculateGrossSalary(emp));
        }
    }

    printf("\nTotal Employees : %d\n", getEmployeeCount());
    printf("Average Salary  : N$%.2f\n", getAverageSalary());
    printf("Highest Salary  : N$%.2f\n", getHighestSalary());
    printf("Lowest Salary   : N$%.2f\n", getLowestSalary());
}

/* Display budget information and totals. */
static void budgetReport(void)
{
    int i;
    double totalAllocated = 0.0;
    double totalExpenditure = 0.0;
    int exceededCount = 0;

    printf("\n========== BUDGET REPORT ==========\n");

    if (budgetCount == 0) {
        printf("No budget records found.\n");
        return;
    }

    printf("%-20s %-16s %-16s %-16s\n",
           "Department", "Allocated", "Expenditure", "Remaining");

    printf("--------------------------------------------------------------------------\n");

    for (i = 0; i < budgetCount; i++) {
        double remaining;

        totalAllocated += budgets[i].allocatedBudget;
        totalExpenditure += budgets[i].expenditure;

        remaining = budgets[i].allocatedBudget - budgets[i].expenditure;

        printf("%-20s N$%-13.2f N$%-13.2f N$%-13.2f\n",
               budgets[i].department,
               budgets[i].allocatedBudget,
               budgets[i].expenditure,
               remaining);

        if (budgets[i].expenditure > budgets[i].allocatedBudget) {
            exceededCount++;
        }
    }

    printf("\nTotal Allocated    : N$%.2f\n", totalAllocated);
    printf("Total Expenditure  : N$%.2f\n", totalExpenditure);
    printf("Total Remaining    : N$%.2f\n",
           totalAllocated - totalExpenditure);

    printf("Departments Over Budget: %d\n", exceededCount);
}

/* Display all registered suppliers. */
static void supplierReport(void)
{
    int i;

    printf("\n========== SUPPLIER REPORT ==========\n");

    if (supplierCount == 0) {
        printf("No supplier records found.\n");
        return;
    }

    printf("%-8s %-20s %-25s %-18s %-18s\n",
           "ID", "Name", "Email", "Phone", "Town");

    printf("----------------------------------------------------------------------------------------\n");

    for (i = 0; i < supplierCount; i++) {
        printf("%-8d %-20s %-25s %-18s %-18s\n",
               supplierIDs[i],
               supplierNames[i],
               supplierEmails[i],
               supplierPhones[i],
               supplierTowns[i]);
    }

    printf("\nTotal Suppliers: %d\n", supplierCount);
}

/* Display all registered assets. */
static void assetReport(void)
{
    int i;

    printf("\n========== ASSET REPORT ==========\n");

    if (assetCount == 0) {
        printf("No asset records found.\n");
        return;
    }

    printf("%-8s %-18s %-15s %-14s %-18s %-15s\n",
           "ID", "Name", "Type", "Value (N$)",
           "Department", "Condition");

    printf("----------------------------------------------------------------------------------------\n");

    for (i = 0; i < assetCount; i++) {
        printf("%-8d %-18s %-15s %-14.2f %-18s %-15s\n",
               assets[i].id,
               assets[i].name,
               assets[i].type,
               assets[i].purchaseValue,
               assets[i].department,
               assets[i].condition);
    }

    printf("\nTotal Assets: %d\n", assetCount);
}

/* Reports menu called from the main MFMS menu. */
void displayReports(void)
{
    int choice;

    do {
        printf("\n========================================\n");
        printf("             REPORTS MODULE\n");
        printf("========================================\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Display All Reports\n");
        printf("6. Return to Main Menu\n");

        choice = getValidMenuChoice(1, 6);

        switch (choice) {
            case 1:
                employeeReport();
                break;

            case 2:
                budgetReport();
                break;

            case 3:
                supplierReport();
                break;

            case 4:
                assetReport();
                break;

            case 5:
           if (getEmployeeCount() == 0 &&
        budgetCount == 0 &&
        supplierCount == 0 &&
        assetCount == 0)
    {
        printf("\nNo reports found. No records are available in the system.\n");
    }
    else
    {
        employeeReport();
        budgetReport();
        supplierReport();
        assetReport();
    }
    break;
            case 6:
                printf("Returning to main menu...\n");
                break;
        }

    } while (choice != 6);
}