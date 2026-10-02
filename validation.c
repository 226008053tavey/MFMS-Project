#include <stdio.h>
#include "validation.h"

int getValidMenuChoice(int min, int max)
{
    int choice;
    while (1)
    {
        printf("Enter your choice: ");

        if (scanf("%d", &choice) == 1)
        {
            if (choice >= min && choice <= max) 
            {
                return choice;
            }
        }
        printf("Invalid choice. Please enter a number between %d and %d.\n", min, max);

        while (getchar() != '\n')
        {
        }
    }
}

int getValidPositiveInt(void)
{
    int value;
    while (1)
    {
        if (scanf("%d", &value) == 1 && value > 0)
        {
            return value;
        }
        
        printf("Invalid input. Please enter a positive whole number: ");

        while (getchar() != '\n')
        {  
        }
    }
}

double getValidPositiveDouble(void)
{
    double value;

    while (1)
    {
        if (scanf("%lf", &value) == 1 && value > 0)
        {
            return value;
        }
        printf("Invalid input. Please enter a positive number: ");

        while (getchar() != '\n')
        {
        }
    }

}    
int isEmptyString(char text[]){
    int i = 0;
    
    if (text[0] == ' '|| text[i] == '\t' || text[i] == '\n')
    {
    i++;
    }
    if (text[i] == '\0')
    {
        return 1;
    }
    return 0;
}
int getValidString(char text[], int size){

    (void)size;
    while (1)
    {
        if(fgets(text, size , stdin) != NULL){

    

        if (!isEmptyString(text))
        {
            return 1;
        }

        printf("Input cannot be empty. Please try again: ");
    }
}
}