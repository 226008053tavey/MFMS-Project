#include <stdio.h>
#include "validation.h"
#include "suppliers.h"

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
    printf("5. Reports\n");
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
        printf("\nEmployee Management Selected.\n");
        pauseScreen();
        break;

        case 2:
        printf("\nBudget Management selected.\n");
        pauseScreen();
        break;

        case 3:
        displaySupplierMenu();
        return 1;

        case 4:
        printf("\nAsset Management selected.\n");
        pauseScreen();
        break;

        case 5:
        printf("\nReport selected");
        pauseScreen();
        break;

        case 6:
        printf("\n Exiting the system...\n");
        return 0;
    }
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