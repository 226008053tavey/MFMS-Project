#include <stdio.h>
#include "validation.h"

int main(void){
    int choice;
    int number;
    double amount;
    char name[50];

    printf("=== VALIDATION TEST ===\n\n");

    printf("Testing menu choice (1-6)\n");
    choice = getValidMenuChoice(1, 6);
    printf("Accepted choice: %d\n\n", choice);

    printf("Testing positive integer\n");
    printf("Enter integer: ");
    number = getValidPositiveInt();
    printf("Accepted integer: %d\n\n",number);

    printf("Testing positive number\n");
    printf("Enter an amount: ");
    amount = getValidPositiveDouble();
    printf("Accepted amount: %.2f\n", amount);

    printf("\nTesting string validation\n");
    printf("Enter a name: ");

    getValidString(name, 50);

    printf("Accepted name: %s\n", name);

    while (getchar() != '\n'){
        
    }

    return 0;

}