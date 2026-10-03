#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPARTMENTS 10
#define NAME_LEN 50

typedef struct {
    char department[NAME_LEN];
    double allocatedBudget;
    double expenditure;
} Department;

extern Department budgets[MAX_DEPARTMENTS];
extern int budgetCount;

void budgetMenu(void);
int addDepartmentBudget(Department budgets[], int count);
void enterExpenditure(Department budgets[], int count);
void calculateRemainingBudget(Department budgets[], int count);
void displayAllBudgets(Department budgets[], int count);
void displayExceededBudgets(Department budgets[], int count);
double getPositiveDouble(const char *prompt);

#endif