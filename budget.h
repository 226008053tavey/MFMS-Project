<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> fcdd781c0cf001336c087a0d3c51ea44597e7e11
#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPARTMENTS 10
#define NAME_LEN 50

/* Structure for one department's budget */
typedef struct {
    char department[NAME_LEN];
    double allocatedBudget;
    double expenditure;
} Department;

/* Function prototypes */
void budgetMenu(void);
int addDepartmentBudget(Department budgets[], int count);
void enterExpenditure(Department budgets[], int count);
void calculateRemainingBudget(Department budgets[], int count);
void displayAllBudgets(Department budgets[], int count);
void displayExceededBudgets(Department budgets[], int count);
double getPositiveDouble(const char *prompt);

<<<<<<< HEAD
=======
#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPARTMENTS 10
#define NAME_LEN 50

/* Structure for one department's budget */
typedef struct {
    char department[NAME_LEN];
    double allocatedBudget;
    double expenditure;
} Department;

/* Function prototypes */
void budgetMenu(void);
int addDepartmentBudget(Department budgets[], int count);
void enterExpenditure(Department budgets[], int count);
void calculateRemainingBudget(Department budgets[], int count);
void displayAllBudgets(Department budgets[], int count);
void displayExceededBudgets(Department budgets[], int count);
double getPositiveDouble(const char *prompt);

>>>>>>> main
=======
>>>>>>> fcdd781c0cf001336c087a0d3c51ea44597e7e11
#endif