#ifndef REPORTS_H
#define REPORTS_H

#define MAX_EMPLOYEES 100
#define MAX_BUDGETS 50
#define MAX_SUPPLIERS 50
#define MAX_ASSETS 100

struct Employee {
    int id;
    char name[50];
    char department[50];
    double basic_salary;
    double housing_allowance;
    double transport_allowance;
};

struct Budget {
    char department[50];
    double allocated;
    double expenditure;
};

struct Supplier {
    int id;
    char name[50];
    char email[50];
    char phone[20];
    char location[50];
};

struct Asset {
    int id;
    char name[50];
    char type[30];
    double purchase_value;
    char department[50];
    char condition[20];
};

void generateEmployeeReport(struct Employee employees[], int count);
void generateBudgetReport(struct Budget budgets[], int count);
void generateSupplierReport(struct Supplier suppliers[], int count);
void generateAssetReport(struct Asset assets[], int count);
void displayReportsMenu(struct Employee employees[], int emp_count, 
                        struct Budget budgets[], int budget_count, 
                        struct Supplier suppliers[], int sup_count, 
                        struct Asset assets[], int asset_count);

#endif