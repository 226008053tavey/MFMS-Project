#include <stdio.h>
#include <string.h>
#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

void displayReports(void)
{
    printf("\n========================================\n");
    printf("          MFMS REPORTS MODULE\n");
    printf("========================================\n");

    employeeReport();
    budgetReport();
    supplierReport();
    assetReport();
}

void employeeReport(void)
{
    int i;
    double totalSalary = 0.0;
    double highestSalary = 0.0;
    double lowestSalary = 0.0;
    double averageSalary;

    printf("\n--- Employee Report ---\n");

    if (employeeCount == 0)
    {
        printf("No employees registered.\n");
        return;
    }

    for (i = 0; i < employeeCount; i++)
    {
        double salary;

        salary = employees[i].basicSalary
               + employees[i].housingAllowance
               + employees[i].transportAllowance;

        totalSalary += salary;

        if (i == 0 || salary > highestSalary)
        {
            highestSalary = salary;
        }

        if (i == 0 || salary < lowestSalary)
        {
            lowestSalary = salary;
        }
    }

    averageSalary = totalSalary / employeeCount;

    printf("Total Employees : %d\n", employeeCount);
    printf("Average Salary  : N$%.2f\n", averageSalary);
    printf("Highest Salary  : N$%.2f\n", highestSalary);
    printf("Lowest Salary   : N$%.2f\n", lowestSalary);
}

void budgetReport(void)
{
    int i;
    double totalAllocated = 0.0;
    double totalExpenditure = 0.0;
    double totalRemaining;

    printf("\n--- Budget Report ---\n");

    if (budgetCount == 0)
    {
        printf("No budget data available.\n");
        return;
    }

    for (i = 0; i < budgetCount; i++)
    {
        totalAllocated += budgets[i].allocatedBudget;
        totalExpenditure += budgets[i].expenditure;
    }

    totalRemaining = totalAllocated - totalExpenditure;

    printf("Departments      : %d\n", budgetCount);
    printf("Total Allocated  : N$%.2f\n", totalAllocated);
    printf("Total Expenditure: N$%.2f\n", totalExpenditure);
    printf("Total Remaining  : N$%.2f\n", totalRemaining);

    if (totalRemaining < 0)
    {
        printf("Overall Status   : OVER BUDGET\n");
    }
    else
    {
        printf("Overall Status   : WITHIN BUDGET\n");
    }

    printf("\nDepartments over budget:\n");

    {
        int found = 0;

        for (i = 0; i < budgetCount; i++)
        {
            if (budgets[i].expenditure >
                budgets[i].allocatedBudget)
            {
                double amountOver;

                amountOver =
                    budgets[i].expenditure -
                    budgets[i].allocatedBudget;

                printf("- %s: over by N$%.2f\n",
                       budgets[i].department,
                       amountOver);

                found = 1;
            }
        }

        if (!found)
        {
            printf("None\n");
        }
    }
}

void supplierReport(void)
{
    int i;

    printf("\n--- Supplier Report ---\n");

    if (supplierCount == 0)
    {
        printf("No suppliers registered.\n");
        return;
    }

    printf("Total Suppliers: %d\n", supplierCount);

    for (i = 0; i < supplierCount; i++)
    {
        printf("%d. %s | %s | %s | %s\n",
               supplierIDs[i],
               supplierNames[i],
               supplierEmails[i],
               supplierPhones[i],
               supplierTowns[i]);
    }
}

void assetReport(void)
{
    int i;
    double totalValue = 0.0;

    printf("\n--- Asset Report ---\n");

    if (assetCount == 0)
    {
        printf("No assets registered.\n");
        return;
    }

    for (i = 0; i < assetCount; i++)
    {
        totalValue += assets[i].purchaseValue;
    }

    printf("Total Assets       : %d\n", assetCount);
    printf("Total Asset Value  : N$%.2f\n", totalValue);

    printf("\nRegistered Assets:\n");

    for (i = 0; i < assetCount; i++)
    {
        printf("%d. %s | %s | N$%.2f | %s | %s\n",
               assets[i].id,
               assets[i].name,
               assets[i].type,
               assets[i].purchaseValue,
               assets[i].department,
               assets[i].condition);
    }
}