#include <stdio.h>
#include <string.h>
#include "employees.h"
#include "validation.h"

Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;

void addEmployee(void)
{
    if (employeeCount >= MAX_EMPLOYEES) {
        printf("Employee limit reached.\n");
        return;
    }

    printf("\n===== ADD EMPLOYEE =====\n");

    printf("Enter Employee ID: ");
    employees[employeeCount].id = getValidPositiveInt();

    printf("Enter Employee Name: ");

if (!getValidString(employees[employeeCount].name,
                    sizeof(employees[employeeCount].name)))
{
    printf("Unable to read employee name.\n");
    return;
}
printf("Enter Department: ");

if (!getValidString(employees[employeeCount].department,
                    sizeof(employees[employeeCount].department)))
{
    printf("Unable to read department.\n");
    return;
}

    printf("Enter Basic Salary: ");
employees[employeeCount].basicSalary =
    (float)getValidPositiveDouble();

    printf("Enter Housing Allowance: ");
employees[employeeCount].housingAllowance =
    (float)getValidPositiveDouble();

    printf("Enter Transport Allowance: ");
employees[employeeCount].transportAllowance =
    (float)getValidPositiveDouble();

    employeeCount++;

    printf("Employee added successfully!\n");
}


void displayEmployees(void)
{
    int i;

    if (employeeCount == 0) {
        printf("No employees found.\n");
        return;
    }

    printf("\n===== EMPLOYEE LIST =====\n");

    for (i = 0; i < employeeCount; i++) {
        printf("\nEmployee %d\n", i + 1);
        printf("ID: %d\n", employees[i].id);
        printf("Name: %s\n", employees[i].name);
        printf("Department: %s\n", employees[i].department);
        printf("Basic Salary: %.2f\n", employees[i].basicSalary);
        printf("Housing Allowance: %.2f\n",
               employees[i].housingAllowance);
        printf("Transport Allowance: %.2f\n",
               employees[i].transportAllowance);
    }
}


void searchEmployee(void)
{
    int choice;
    int id;
    int i;
    char name[50];

    printf("\n===== SEARCH EMPLOYEE =====\n");
    printf("1. Search by Employee ID\n");
    printf("2. Search by Employee Name\n");
    printf("Enter your choice: ");
    choice = getValidMenuChoice(1, 2);

    if (choice == 1) {

        printf("Enter Employee ID: ");
        id = getValidPositiveInt();
        for (i = 0; i < employeeCount; i++) {

            if (employees[i].id == id) {

                printf("\nEmployee found!\n");
                printf("ID: %d\n", employees[i].id);
                printf("Name: %s\n", employees[i].name);
                printf("Department: %s\n", employees[i].department);
                printf("Basic Salary: %.2f\n",
                       employees[i].basicSalary);
                printf("Housing Allowance: %.2f\n",
                       employees[i].housingAllowance);
                printf("Transport Allowance: %.2f\n",
                       employees[i].transportAllowance);

                return;
            }
        }

        printf("Employee with ID %d was not found.\n", id);

    } else if (choice == 2) {

        printf("Enter Employee Name: ");

if (!getValidString(name, sizeof(name)))
{
    printf("Unable to read employee name.\n");
    return;
}
        for (i = 0; i < employeeCount; i++) {

            if (strcmp(employees[i].name, name) == 0) {

                printf("\nEmployee found!\n");
                printf("ID: %d\n", employees[i].id);
                printf("Name: %s\n", employees[i].name);
                printf("Department: %s\n", employees[i].department);
                printf("Basic Salary: %.2f\n",
                       employees[i].basicSalary);
                printf("Housing Allowance: %.2f\n",
                       employees[i].housingAllowance);
                printf("Transport Allowance: %.2f\n",
                       employees[i].transportAllowance);

                return;
            }
        }

        printf("Employee with name '%s' was not found.\n", name);

    } else {

        printf("Invalid search option.\n");
    }
}


void calculateSalary(void)
{
    int id;
    int i;
    float totalSalary;

    printf("\n===== CALCULATE SALARY =====\n");

    printf("Enter Employee ID: ");
    id = getValidPositiveInt();

    for (i = 0; i < employeeCount; i++) {

        if (employees[i].id == id) {

            totalSalary = employees[i].basicSalary
                        + employees[i].housingAllowance
                        + employees[i].transportAllowance;

            printf("\nEmployee: %s\n", employees[i].name);
            printf("Basic Salary: %.2f\n",
                   employees[i].basicSalary);
            printf("Housing Allowance: %.2f\n",
                   employees[i].housingAllowance);
            printf("Transport Allowance: %.2f\n",
                   employees[i].transportAllowance);
            printf("Total Salary: %.2f\n", totalSalary);

            return;
        }
    }

    printf("Employee with ID %d was not found.\n", id);
}


void employeeMenu(void)
{
    int choice;

    do {
        printf("\n===== EMPLOYEE MANAGEMENT =====\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Calculate Salary\n");
        printf("5. Return to Main Menu\n");
        printf("Enter your choice: ");

        choice = getValidMenuChoice(1, 5);

        switch (choice) {

            case 1:
                addEmployee();
                break;

            case 2:
                displayEmployees();
                break;

            case 3:
                searchEmployee();
                break;

            case 4:
                calculateSalary();
                break;

            case 5:
                printf("Returning to Main Menu...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 5);
}