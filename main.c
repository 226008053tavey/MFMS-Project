#include <stdio.h>
#include "validation.h"
#include "suppliers.h"
#include "assets.h"
#include "employees.h"
#include "budget.h"

void displayMenu(void);
void pauseScreen(void);
int handleMenuChoice(int choice);

void displayMenu(void){


    printf("\n");
    printf("======================================\n");
    printf("MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("======================================\n");

    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("6. Exit\n");

    printf("======================================\n");
}
void pauseScreen(void){

    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

int handleMenuChoice(int choice){
    switch (choice)
    {
        case 1:
        employeeMenu();
        return 1;
    
        case 2:
        budgetMenu();
        return 1;
    
        case 3:
        displaySupplierMenu();
        return 1;

        case 4:
        displayAssetMenu();
        return 1;

        case 5:
        return 1;
    
        case 6:
        printf("\n Exiting the system...\n");
    }
        return 0;
    }
int main(void){

    int choice;
    int continueProgram = 1;

    while(continueProgram){

        displayMenu();

        choice = getValidMenuChoice(1, 6);

        continueProgram = handleMenuChoice(choice);
    }
    return 0;
}
