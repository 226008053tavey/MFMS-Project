/*
 * employees.h
 * Employee Management module - Municipal Financial Management System (MFMS)
 * PAP521S - Programming in Practice, Project A
 */
#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES   100
#define MAX_ID_LEN      10
#define MAX_NAME_LEN    50
#define MAX_DEPT_LEN    30
#define MAX_POSITION_LEN 40
#define NUM_DEPARTMENTS 6

/* Department names. Share these with the Budget module so the names match. */
extern const char *const EMP_DEPARTMENTS[NUM_DEPARTMENTS];

typedef struct {
    char   id[MAX_ID_LEN];              /* e.g. EMP001 */
    char   name[MAX_NAME_LEN];
    char   department[MAX_DEPT_LEN];
    char   position[MAX_POSITION_LEN];
    double basicSalary;                 /* monthly, N$ */
    double housingAllowance;            /* monthly, N$ */
    double transportAllowance;          /* monthly, N$ */
    double otherAllowance;              /* monthly, N$ */
    int    yearsOfService;
} Employee;

/* ---- Menu / user-facing operations (called from main.c) ---- */
void employeeMenu(void);
void addEmployee(void);
void displayEmployees(void);
void searchEmployee(void);
void calculateSalary(void);            /* asks for an ID and prints a payslip */
void loadSampleEmployees(void);        /* demo data, skips IDs already present */

/* ---- Calculations (pass-by-value / return-value functions) ---- */
double calculateGrossSalary(const Employee *emp);
double calculateTax(double grossSalary);
double calculatePension(double basicSalary);
double calculateNetSalary(const Employee *emp);

/* ---- Helpers for the Reports module (gross monthly salary) ---- */
int            getEmployeeCount(void);
double         getAverageSalary(void);   /* 0.0 if no employees */
double         getHighestSalary(void);   /* 0.0 if no employees */
double         getLowestSalary(void);    /* 0.0 if no employees */
const Employee *getEmployeeByIndex(int index); /* NULL if out of range */

#endif /* EMPLOYEES_H */
