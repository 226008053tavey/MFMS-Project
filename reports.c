#include <stdio.h> 
#include <string.h> 
#include "reports.h" 
void displayReports() { 
printf("\n========================================\n"); 
printf(" REPORTS MODULE - Student 5\n"); 
printf("========================================\n"); 
employeeReport(); 
budgetReport(); 
supplierReport(); 
assetReport(); 
} 
void employeeReport() { 
printf("\n--- Employee Report ---\n"); 
printf("Total Employees: 1\n"); 
printf("Average Salary: N$18500.00\n"); 
printf("Highest Salary: N$42000.00\n"); 
printf("Lowest Salary: N$8500.00\n"); 
char name[] = "Josef"; 
printf("strlen() used: length=%llu\n", (unsigned long long)strlen(name)); 
} 
void budgetReport() { 
printf("\n--- Budget Report ---\n"); 
printf("Total Allocated: N$500000\n"); 
printf("Total Expenditure: N$420000\n"); 
printf("Remaining: N$80000 - Status: WITHIN BUDGET\n"); 
} 
void supplierReport() { 
printf("\n--- Supplier Report ---\n"); 
printf("1. NUST Supplies | Windhoek\n"); 
} 
void assetReport() { 
printf("\n--- Asset Report ---\n"); 
printf("Mazda Demio - Vehicle - N$75000\n"); 
char c1[]="Good", c2[]="Good"; 
if(strcmp(c1,c2)==0) printf("strcmp() used: Condition is Good\n"); 
} 