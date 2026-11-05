#include <stdio.h>
#include <string.h>
#include "reports.h"
#include "validation.h"

void displayReports(void)
{
    printf("\n========================================\n");
    printf("          REPORTS MODULE\n");
    printf("========================================\n");

    employeeReport();
    budgetReport();
    supplierReport();
    assetReport();
}

void employeeReport(void)
{
    printf("\n--- Employee Report ---\n");
    printf("Employee report will be displayed here.\n");
}

void budgetReport(void)
{
    printf("\n--- Budget Report ---\n");
    printf("Budget report will be displayed here.\n");
}

void supplierReport(void)
{
    printf("\n--- Supplier Report ---\n");
    printf("Supplier report will be displayed here.\n");
}

void assetReport(void)
{
    printf("\n--- Asset Report ---\n");

    char c1[] = "Good";
    char c2[] = "Good";

    if (strcmp(c1, c2) == 0)
    {
        printf("strcmp() used: Condition is Good\n");
    }
}