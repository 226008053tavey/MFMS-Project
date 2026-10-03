#include <stdio.h>
#include <string.h>
#include "employees.h"
#include "validation.h"

Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;

static int findEmployeeByID(int id)
{
    int i;

    for (i = 0; i < employeeCount; i++)
    {
        if (employees[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

void addEmployee(void)
{
    int id;

    if (employeeCount >= MAX_EMPLOYEES)
    {
        printf("Employee limit reached.\n");
        return;
    }

    printf("\n===== ADD EMPLOYEE =====\n");

    while (1)
    {
        printf("Enter Employee ID: ");
        id = getValidPositiveInt();

        if (findEmployeeByID(id) != -1)
        {
            printf("That Employee ID already exists. Please use another ID.\n");
        }
        else
        {
            break;
        }
    }

    employees[employeeCount].id = id;

    while (1)
    {
        printf("Enter Employee Name: ");

        if (getValidString(employees[employeeCount].name,
                           sizeof(employees[employeeCount].name)))
        {
            break;
        }
    }

    while (1)
    {
        printf("Enter Department: ");

        if (getValidString(employees[employeeCount].department,
                           sizeof(employees[employeeCount].department)))
        {
            break;
        }
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

    if (employeeCount == 0)
    {
        printf("No employees found.\n");
        return;
    }

    printf("\n===== EMPLOYEE LIST =====\n");

    for (i = 0; i < employeeCount; i++)
    {
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
    int index;
    int i;
    char name[50];

    if (employeeCount == 0)
    {
        printf("No employees found.\n");
        return;
    }

    printf("\n===== SEARCH EMPLOYEE =====\n");
    printf("1. Search by Employee ID\n");
    printf("2. Search by Employee Name\n");

    choice = getValidMenuChoice(1, 2);

    if (choice == 1)
    {
        printf("Enter Employee ID: ");
        id = getValidPositiveInt();

        index = findEmployeeByID(id);

        if (index == -1)
        {
            printf("Employee with ID %d was not found.\n", id);
            return;
        }

        printf("\nEmployee found!\n");
        printf("ID: %d\n", employees[index].id);
        printf("Name: %s\n", employees[index].name);
        printf("Department: %s\n", employees[index].department);
        printf("Basic Salary: %.2f\n", employees[index].basicSalary);
        printf("Housing Allowance: %.2f\n",
               employees[index].housingAllowance);
        printf("Transport Allowance: %.2f\n",
               employees[index].transportAllowance);
    }
    else
    {
        printf("Enter Employee Name: ");

        if (!getValidString(name, sizeof(name)))
        {
            return;
        }

        for (i = 0; i < employeeCount; i++)
        {
            if (strcmp(employees[i].name, name) == 0)
            {
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
    }
}

void calculateSalary(void)
{
    int id;
    int index;
    float totalSalary;

    if (employeeCount == 0)
    {
        printf("No employees found.\n");
        return;
    }

    printf("\n===== CALCULATE SALARY =====\n");

    printf("Enter Employee ID: ");
    id = getValidPositiveInt();

    index = findEmployeeByID(id);

    if (index == -1)
    {
        printf("Employee with ID %d was not found.\n", id);
        return;
    }

    totalSalary = employees[index].basicSalary
                + employees[index].housingAllowance
                + employees[index].transportAllowance;

    printf("\nEmployee: %s\n", employees[index].name);
    printf("Basic Salary: %.2f\n",
           employees[index].basicSalary);
    printf("Housing Allowance: %.2f\n",
           employees[index].housingAllowance);
    printf("Transport Allowance: %.2f\n",
           employees[index].transportAllowance);
    printf("Total Salary: %.2f\n", totalSalary);
}

void employeeMenu(void)
{
    int choice;

    do
    {
        printf("\n===== EMPLOYEE MANAGEMENT =====\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Calculate Salary\n");
        printf("5. Return to Main Menu\n");

        choice = getValidMenuChoice(1, 5);

        switch (choice)
        {
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
        }

    } while (choice != 5);
}