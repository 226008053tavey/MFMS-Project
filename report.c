#include <stdio.h>
#include <string.h>
#include "reports.h"

void generateEmployeeReport(struct Employee employees[], int count) {
    printf("\n========================================\n");
    printf("            EMPLOYEE REPORT             \n");
    printf("========================================\n");

    if (count == 0) {
        printf("No employee records found.\n");
        return;
    }

    double total_salary = 0.0;
    double highest_salary = employees[0].basic_salary + employees[0].housing_allowance + employees[0].transport_allowance;
    double lowest_salary = highest_salary;

    for (int i = 0; i < count; i++) {
        double gross_salary = employees[i].basic_salary + employees[i].housing_allowance + employees[i].transport_allowance;
        total_salary += gross_salary;

        if (gross_salary > highest_salary) {
            highest_salary = gross_salary;
        }
        if (gross_salary < lowest_salary) {
            lowest_salary = gross_salary;
        }
    }

    double average_salary = total_salary / count;

    printf("Total Employees : %d\n", count);
    printf("Average Salary  : N$%.2f\n", average_salary);
    printf("Highest Salary  : N$%.2f\n", highest_salary);
    printf("Lowest Salary   : N$%.2f\n", lowest_salary);
    printf("========================================\n");
}

void generateBudgetReport(struct Budget budgets[], int count) {
    printf("\n========================================\n");
    printf("             BUDGET REPORT              \n");
    printf("========================================\n");

    if (count == 0) {
        printf("No budget records found.\n");
        return;
    }

    double total_allocated = 0.0;
    double total_expenditure = 0.0;

    for (int i = 0; i < count; i++) {
        total_allocated += budgets[i].allocated;
        total_expenditure += budgets[i].expenditure;
    }

    double total_remaining = total_allocated - total_expenditure;

    printf("Total Allocated Budget : N$%.2f\n", total_allocated);
    printf("Total Expenditure      : N$%.2f\n", total_expenditure);
    printf("Total Remaining Budget : N$%.2f\n", total_remaining);
    
    printf("\nDepartments Exceeding Allocated Budget:\n");
    int exceeded_count = 0;
    for (int i = 0; i < count; i++) {
        if (budgets[i].expenditure > budgets[i].allocated) {
            double deficit = budgets[i].expenditure - budgets[i].allocated;
            printf("- %s (Over budget by N$%.2f)\n", budgets[i].department, deficit);
            exceeded_count++;
        }
    }

    if (exceeded_count == 0) {
        printf("None. All departments are within budget.\n");
    }
    printf("========================================\n");
}

void generateSupplierReport(struct Supplier suppliers[], int count) {
    printf("\n========================================================================================\n");
    printf("                                    SUPPLIER REPORT                                     \n");
    printf("========================================================================================\n");

    if (count == 0) {
        printf("No supplier records found.\n");
        return;
    }

    printf("%-10s %-20s %-25s %-15s %-15s\n", "ID", "Name", "Email", "Phone", "Location");
    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-10d %-20s %-25s %-15s %-15s\n", 
               suppliers[i].id, 
               suppliers[i].name, 
               suppliers[i].email, 
               suppliers[i].phone, 
               suppliers[i].location);
    }
    printf("========================================================================================\n");
}

void generateAssetReport(struct Asset assets[], int count) {
    printf("\n========================================================================================\n");
    printf("                                      ASSET REPORT                                      \n");
    printf("========================================================================================\n");

    if (count == 0) {
        printf("No asset records found.\n");
        return;
    }

    printf("%-10s %-20s %-15s %-15s %-15s %-10s\n", "ID", "Name", "Type", "Value (N$)", "Department", "Condition");
    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-10d %-20s %-15s %-15.2f %-15s %-10s\n", 
               assets[i].id, 
               assets[i].name, 
               assets[i].type, 
               assets[i].purchase_value, 
               assets[i].department, 
               assets[i].condition);
    }
    printf("========================================================================================\n");
}

void displayReportsMenu(struct Employee employees[], int emp_count, 
                        struct Budget budgets[], int budget_count, 
                        struct Supplier suppliers[], int sup_count, 
                        struct Asset assets[], int asset_count) {
    int choice;
    do {
        printf("\n=== REPORTS MODULE ===\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Display All Reports\n");
        printf("6. Return to Main Menu\n");
        printf("Enter choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                generateEmployeeReport(employees, emp_count);
                break;
            case 2:
                generateBudgetReport(budgets, budget_count);
                break;
            case 3:
                generateSupplierReport(suppliers, sup_count);
                break;
            case 4:
                generateAssetReport(assets, asset_count);
                break;
            case 5:
                generateEmployeeReport(employees, emp_count);
                generateBudgetReport(budgets, budget_count);
                generateSupplierReport(suppliers, sup_count);
                generateAssetReport(assets, asset_count);
                break;
            case 6:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid selection. Try again.\n");
        }
    } while (choice != 6);
}