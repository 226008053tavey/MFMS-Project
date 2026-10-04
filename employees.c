/*
 * employees.c
 * Employee Management module - Municipal Financial Management System (MFMS)
 * PAP521S - Programming in Practice, Project A
 *
 * Storage : a fixed-size array of Employee structures.
 * Salary  : gross = basic + housing + transport + other allowances.
 *           Tax and pension rates below are SIMPLIFIED, illustrative values
 *           for this course project - they are not official PAYE rules.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include "employees.h"

/* ---------- Constants ---------- */
#define INPUT_BUF   128
#define MAX_AMOUNT  1000000.0     /* upper sanity limit for money inputs */
#define PENSION_RATE 0.05         /* 5% of basic salary */

/* Simplified monthly tax bands (illustrative) */
#define TAX_BAND1_LIMIT 5000.0    /* 0% up to here */
#define TAX_BAND2_LIMIT 10000.0   /* 15% above band 1 */
#define TAX_BAND3_LIMIT 20000.0   /* 25% above band 2, 32% above band 3 */

const char *const EMP_DEPARTMENTS[NUM_DEPARTMENTS] = {
    "Finance", "Human Resources", "Public Works",
    "Health Services", "IT", "Town Planning"
};

/* ---------- Module data ---------- */
static Employee employees[MAX_EMPLOYEES];
static int      employeeCount = 0;

/* =====================================================================
 *  Input helpers (all validation lives here so every prompt is safe)
 * ===================================================================== */

static void trim(char *s)
{
    char  *start = s;
    size_t len;

    while (*start != '\0' && isspace((unsigned char)*start)) {
        start++;
    }
    if (start != s) {
        memmove(s, start, strlen(start) + 1);
    }
    len = strlen(s);
    while (len > 0 && isspace((unsigned char)s[len - 1])) {
        s[--len] = '\0';
    }
}

/* Reads one line, removes the newline, trims spaces, discards overflow. */
static void readLine(const char *prompt, char *buf, int size)
{
    size_t len;
    int    c;

    printf("%s", prompt);
    if (fgets(buf, size, stdin) == NULL) {
        printf("\nInput closed. Exiting.\n");
        exit(1);
    }
    len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    } else {
        while ((c = getchar()) != '\n' && c != EOF) {
            /* discard the rest of an over-long line */
        }
    }
    trim(buf);
}

static int readInt(const char *prompt, int min, int max)
{
    char  buf[INPUT_BUF];
    char *end;
    long  value;

    for (;;) {
        readLine(prompt, buf, sizeof buf);
        if (buf[0] == '\0') {
            printf("  Error: input cannot be empty.\n");
            continue;
        }
        errno = 0;
        value = strtol(buf, &end, 10);
        if (*end != '\0' || errno == ERANGE) {
            printf("  Error: please enter a whole number.\n");
            continue;
        }
        if (value < min || value > max) {
            printf("  Error: enter a number between %d and %d.\n", min, max);
            continue;
        }
        return (int)value;
    }
}

static double readMoney(const char *prompt, int allowZero)
{
    char   buf[INPUT_BUF];
    char  *end;
    double value;

    for (;;) {
        readLine(prompt, buf, sizeof buf);
        if (buf[0] == '\0') {
            printf("  Error: input cannot be empty.\n");
            continue;
        }
        errno = 0;
        value = strtod(buf, &end);
        if (*end != '\0' || errno == ERANGE || !isfinite(value)) {
            printf("  Error: please enter a valid number (e.g. 12500.50).\n");
            continue;
        }
        if (value < 0.0) {
            printf("  Error: amount cannot be negative.\n");
            continue;
        }
        if (value == 0.0 && !allowZero) {
            printf("  Error: amount must be greater than zero.\n");
            continue;
        }
        if (value > MAX_AMOUNT) {
            printf("  Error: amount is too large (maximum N$%.0f).\n", MAX_AMOUNT);
            continue;
        }
        return value;
    }
}

/* Letters, spaces, hyphens, apostrophes and dots; at least one letter. */
static int isValidName(const char *s)
{
    int i;
    int letters = 0;

    for (i = 0; s[i] != '\0'; i++) {
        if (isalpha((unsigned char)s[i])) {
            letters++;
        } else if (s[i] != ' ' && s[i] != '-' && s[i] != '\'' && s[i] != '.') {
            return 0;
        }
    }
    return letters > 0;
}

static int isValidId(const char *s)
{
    size_t len = strlen(s);
    size_t i;

    if (len < 3 || len > MAX_ID_LEN - 1) {
        return 0;
    }
    for (i = 0; i < len; i++) {
        if (!isalnum((unsigned char)s[i])) {
            return 0;
        }
    }
    return 1;
}

static void toUpperStr(char *s)
{
    for (; *s != '\0'; s++) {
        *s = (char)toupper((unsigned char)*s);
    }
}

/* Case-insensitive "contains" using lower-cased copies. */
static int containsIgnoreCase(const char *text, const char *part)
{
    char a[INPUT_BUF], b[INPUT_BUF];
    int  i;

    strncpy(a, text, sizeof a - 1);
    a[sizeof a - 1] = '\0';
    strncpy(b, part, sizeof b - 1);
    b[sizeof b - 1] = '\0';
    for (i = 0; a[i] != '\0'; i++) a[i] = (char)tolower((unsigned char)a[i]);
    for (i = 0; b[i] != '\0'; i++) b[i] = (char)tolower((unsigned char)b[i]);
    return strstr(a, b) != NULL;
}

/* =====================================================================
 *  Lookup / display helpers
 * ===================================================================== */

/* Returns the array index of the employee with this ID, or -1. */
static int findEmployeeIndexById(const char *id)
{
    int i;

    for (i = 0; i < employeeCount; i++) {
        if (strcmp(employees[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

/* Builds "Name - Department" for headings (uses strcpy + strcat). */
static void buildEmployeeLabel(const Employee *emp, char *label, int size)
{
    char temp[MAX_NAME_LEN + MAX_DEPT_LEN + 4];

    strcpy(temp, emp->name);
    strcat(temp, " - ");
    strcat(temp, emp->department);
    strncpy(label, temp, size - 1);
    label[size - 1] = '\0';
}

static void printTableHeader(void)
{
    printf("\n%-4s %-9s %-22s %-16s %12s %12s\n",
           "No.", "ID", "Name", "Department", "Basic (N$)", "Gross (N$)");
    printf("---- --------- ---------------------- ---------------- "
           "------------ ------------\n");
}

static void printTableRow(int number, const Employee *emp)
{
    printf("%-4d %-9s %-22.22s %-16.16s %12.2f %12.2f\n",
           number, emp->id, emp->name, emp->department,
           emp->basicSalary, calculateGrossSalary(emp));
}

static void displayEmployeeDetails(const Employee *emp)
{
    char label[MAX_NAME_LEN + MAX_DEPT_LEN + 4];

    buildEmployeeLabel(emp, label, sizeof label);
    printf("\n  --- %s ---\n", label);
    printf("  Employee ID        : %s\n", emp->id);
    printf("  Name               : %s\n", emp->name);
    printf("  Department         : %s\n", emp->department);
    printf("  Position           : %s\n", emp->position);
    printf("  Years of service   : %d\n", emp->yearsOfService);
    printf("  Basic salary       : N$%.2f\n", emp->basicSalary);
    printf("  Housing allowance  : N$%.2f\n", emp->housingAllowance);
    printf("  Transport allowance: N$%.2f\n", emp->transportAllowance);
    printf("  Other allowance    : N$%.2f\n", emp->otherAllowance);
    printf("  Gross salary       : N$%.2f\n", calculateGrossSalary(emp));
}

static void displayPayslip(const Employee *emp)
{
    double gross   = calculateGrossSalary(emp);
    double tax     = calculateTax(gross);
    double pension = calculatePension(emp->basicSalary);
    double net     = gross - tax - pension;
    char   label[MAX_NAME_LEN + MAX_DEPT_LEN + 4];

    buildEmployeeLabel(emp, label, sizeof label);
    printf("\n========================================\n");
    printf("            MONTHLY PAYSLIP\n");
    printf("========================================\n");
    printf("Employee : %s (%s)\n", label, emp->id);
    printf("Position : %s\n", emp->position);
    printf("----------------------------------------\n");
    printf("Basic salary        : N$%10.2f\n", emp->basicSalary);
    printf("Housing allowance   : N$%10.2f\n", emp->housingAllowance);
    printf("Transport allowance : N$%10.2f\n", emp->transportAllowance);
    printf("Other allowance     : N$%10.2f\n", emp->otherAllowance);
    printf("----------------------------------------\n");
    printf("GROSS SALARY        : N$%10.2f\n", gross);
    printf("Income tax          : N$%10.2f\n", tax);
    printf("Pension (%.1f%%)      : N$%10.2f\n", PENSION_RATE * 100.0, pension);
    printf("----------------------------------------\n");
    printf("NET SALARY          : N$%10.2f\n", net);
    printf("========================================\n");
}

/* =====================================================================
 *  Salary calculations
 * ===================================================================== */

double calculateGrossSalary(const Employee *emp)
{
    return emp->basicSalary + emp->housingAllowance
         + emp->transportAllowance + emp->otherAllowance;
}

/* Simplified progressive monthly tax. */
double calculateTax(double grossSalary)
{
    double tax;

    if (grossSalary <= TAX_BAND1_LIMIT) {
        tax = 0.0;
    } else if (grossSalary <= TAX_BAND2_LIMIT) {
        tax = (grossSalary - TAX_BAND1_LIMIT) * 0.15;
    } else if (grossSalary <= TAX_BAND3_LIMIT) {
        tax = (TAX_BAND2_LIMIT - TAX_BAND1_LIMIT) * 0.15
            + (grossSalary - TAX_BAND2_LIMIT) * 0.25;
    } else {
        tax = (TAX_BAND2_LIMIT - TAX_BAND1_LIMIT) * 0.15
            + (TAX_BAND3_LIMIT - TAX_BAND2_LIMIT) * 0.25
            + (grossSalary - TAX_BAND3_LIMIT) * 0.32;
    }
    return tax;
}

double calculatePension(double basicSalary)
{
    return basicSalary * PENSION_RATE;
}

double calculateNetSalary(const Employee *emp)
{
    double gross = calculateGrossSalary(emp);
    return gross - calculateTax(gross) - calculatePension(emp->basicSalary);
}

/* =====================================================================
 *  Operations
 * ===================================================================== */

void addEmployee(void)
{
    Employee emp;
    char     buf[INPUT_BUF];
    int      choice;

    printf("\n--- ADD EMPLOYEE ---\n");
    if (employeeCount >= MAX_EMPLOYEES) {
        printf("Error: employee list is full (%d maximum).\n", MAX_EMPLOYEES);
        return;
    }

    /* Employee ID: 3-9 letters/digits, must be unique */
    for (;;) {
        readLine("Employee ID (e.g. EMP001): ", buf, sizeof buf);
        toUpperStr(buf);
        if (!isValidId(buf)) {
            printf("  Error: ID must be 3-%d letters/digits, no spaces.\n",
                   MAX_ID_LEN - 1);
        } else if (findEmployeeIndexById(buf) != -1) {
            printf("  Error: an employee with ID %s already exists.\n", buf);
        } else {
            strcpy(emp.id, buf);
            break;
        }
    }

    /* Name */
    for (;;) {
        readLine("Full name: ", buf, sizeof buf);
        if (strlen(buf) == 0) {
            printf("  Error: name cannot be empty.\n");
        } else if (strlen(buf) >= MAX_NAME_LEN) {
            printf("  Error: name is too long (max %d characters).\n",
                   MAX_NAME_LEN - 1);
        } else if (!isValidName(buf)) {
            printf("  Error: name may only contain letters, spaces, - ' and .\n");
        } else {
            strcpy(emp.name, buf);
            break;
        }
    }

    /* Department */
    printf("Departments:\n");
    for (choice = 0; choice < NUM_DEPARTMENTS; choice++) {
        printf("  %d. %s\n", choice + 1, EMP_DEPARTMENTS[choice]);
    }
    choice = readInt("Select department: ", 1, NUM_DEPARTMENTS);
    strcpy(emp.department, EMP_DEPARTMENTS[choice - 1]);

    /* Position */
    for (;;) {
        readLine("Position / job title: ", buf, sizeof buf);
        if (strlen(buf) == 0) {
            printf("  Error: position cannot be empty.\n");
        } else if (strlen(buf) >= MAX_POSITION_LEN) {
            printf("  Error: position is too long (max %d characters).\n",
                   MAX_POSITION_LEN - 1);
        } else {
            strcpy(emp.position, buf);
            break;
        }
    }

    emp.yearsOfService     = readInt("Years of service (0-50): ", 0, 50);
    emp.basicSalary        = readMoney("Basic salary (N$ per month): ", 0);
    emp.housingAllowance   = readMoney("Housing allowance (N$): ", 1);
    emp.transportAllowance = readMoney("Transport allowance (N$): ", 1);
    emp.otherAllowance     = readMoney("Other allowance (N$): ", 1);

    employees[employeeCount] = emp;
    employeeCount++;
    printf("\nEmployee %s added successfully. Total employees: %d\n",
           emp.id, employeeCount);
}

void displayEmployees(void)
{
    int i;

    printf("\n--- ALL EMPLOYEES ---\n");
    if (employeeCount == 0) {
        printf("No employees registered yet.\n");
        return;
    }
    printTableHeader();
    for (i = 0; i < employeeCount; i++) {
        printTableRow(i + 1, &employees[i]);
    }
    printf("\nTotal employees: %d\n", employeeCount);
}

void searchEmployee(void)
{
    char buf[INPUT_BUF];
    int  option, i, found = 0, dept;

    printf("\n--- SEARCH EMPLOYEE ---\n");
    if (employeeCount == 0) {
        printf("No employees registered yet.\n");
        return;
    }
    printf("1. Search by Employee ID\n");
    printf("2. Search by name (partial match allowed)\n");
    printf("3. Search by department\n");
    option = readInt("Choose search type: ", 1, 3);

    if (option == 1) {
        readLine("Enter Employee ID: ", buf, sizeof buf);
        toUpperStr(buf);
        i = findEmployeeIndexById(buf);
        if (i == -1) {
            printf("No employee found with ID \"%s\".\n", buf);
        } else {
            displayEmployeeDetails(&employees[i]);
        }
        return;
    }

    if (option == 2) {
        for (;;) {
            readLine("Enter name or part of a name: ", buf, sizeof buf);
            if (strlen(buf) > 0) break;
            printf("  Error: search text cannot be empty.\n");
        }
        for (i = 0; i < employeeCount; i++) {
            if (containsIgnoreCase(employees[i].name, buf)) {
                if (!found) printTableHeader();
                printTableRow(i + 1, &employees[i]);
                found++;
            }
        }
    } else {
        for (dept = 0; dept < NUM_DEPARTMENTS; dept++) {
            printf("  %d. %s\n", dept + 1, EMP_DEPARTMENTS[dept]);
        }
        dept = readInt("Select department: ", 1, NUM_DEPARTMENTS);
        for (i = 0; i < employeeCount; i++) {
            if (strcmp(employees[i].department, EMP_DEPARTMENTS[dept - 1]) == 0) {
                if (!found) printTableHeader();
                printTableRow(i + 1, &employees[i]);
                found++;
            }
        }
    }

    if (found == 0) {
        printf("No matching employees found.\n");
    } else {
        printf("\n%d employee(s) found.\n", found);
    }
}

void calculateSalary(void)
{
    char buf[INPUT_BUF];
    int  index;

    printf("\n--- CALCULATE SALARY ---\n");
    if (employeeCount == 0) {
        printf("No employees registered yet.\n");
        return;
    }
    readLine("Enter Employee ID: ", buf, sizeof buf);
    toUpperStr(buf);
    index = findEmployeeIndexById(buf);
    if (index == -1) {
        printf("No employee found with ID \"%s\".\n", buf);
        return;
    }
    displayPayslip(&employees[index]);
}

void loadSampleEmployees(void)
{
    static const Employee samples[] = {
        {"EMP001", "Maria Shikongo",   "Finance",         "Finance Manager",     28000.0, 4500.0, 2000.0,  500.0, 12},
        {"EMP002", "Johannes Amukwa",  "Public Works",    "Works Supervisor",    14500.0, 2500.0, 1500.0,    0.0,  8},
        {"EMP003", "Selma Nghipandulwa","Human Resources","HR Officer",          12000.0, 2000.0, 1200.0,  300.0,  5},
        {"EMP004", "Petrus Haufiku",   "IT",              "Systems Administrator",18500.0, 3000.0, 1800.0,  600.0,  6},
        {"EMP005", "Anna Kandjii",     "Health Services", "Clinic Nurse",         8500.0, 1500.0, 1000.0,    0.0,  2}
    };
    int n = (int)(sizeof samples / sizeof samples[0]);
    int i, added = 0;

    for (i = 0; i < n; i++) {
        if (employeeCount >= MAX_EMPLOYEES) break;
        if (findEmployeeIndexById(samples[i].id) == -1) {
            employees[employeeCount++] = samples[i];
            added++;
        }
    }
    printf("Loaded %d sample employee(s).\n", added);
}

void employeeMenu(void)
{
    int choice;

    do {
        printf("\n========================================\n");
        printf("          EMPLOYEE MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add employee\n");
        printf("2. Display all employees\n");
        printf("3. Search for an employee\n");
        printf("4. Calculate salary (payslip)\n");
        printf("5. Load sample data (demo)\n");
        printf("6. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 6);

        switch (choice) {
            case 1: addEmployee();          break;
            case 2: displayEmployees();     break;
            case 3: searchEmployee();       break;
            case 4: calculateSalary();      break;
            case 5: loadSampleEmployees();  break;
            case 6: printf("Returning to main menu...\n"); break;
            default: break;
        }
    } while (choice != 6);
}

/* =====================================================================
 *  Helpers for the Reports module
 * ===================================================================== */

int getEmployeeCount(void)
{
    return employeeCount;
}

double getAverageSalary(void)
{
    double total = 0.0;
    int    i;

    if (employeeCount == 0) return 0.0;
    for (i = 0; i < employeeCount; i++) {
        total += calculateGrossSalary(&employees[i]);
    }
    return total / employeeCount;
}

double getHighestSalary(void)
{
    double highest, g;
    int    i;

    if (employeeCount == 0) return 0.0;
    highest = calculateGrossSalary(&employees[0]);
    for (i = 1; i < employeeCount; i++) {
        g = calculateGrossSalary(&employees[i]);
        if (g > highest) highest = g;
    }
    return highest;
}

double getLowestSalary(void)
{
    double lowest, g;
    int    i;

    if (employeeCount == 0) return 0.0;
    lowest = calculateGrossSalary(&employees[0]);
    for (i = 1; i < employeeCount; i++) {
        g = calculateGrossSalary(&employees[i]);
        if (g < lowest) lowest = g;
    }
    return lowest;
}

const Employee *getEmployeeByIndex(int index)
{
    if (index < 0 || index >= employeeCount) return NULL;
    return &employees[index];
}
