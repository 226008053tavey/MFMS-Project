#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "validation.h"

void clearInputBuffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

int getValidMenuChoice(int min, int max)
{
    int choice;
    while (1)
    {
        printf("Enter your choice: ");

        if (scanf("%d", &choice) == 1)
        {

          clearInputBuffer();

        
            if (choice >= min && choice <= max)
            {

                return choice;
            }
        }
            else
        {
                clearInputBuffer();
        }
        printf("Invalid choice. Please enter a number between %d and %d.\n", min, max);
   }
}

int getValidPositiveInt(void)
{
    int value;
    while (1)
    {
        if (scanf("%d", &value) == 1 && value > 0)
        {
            clearInputBuffer();

            return value;
            
        }     
        else
        {
            clearInputBuffer();
        }

        
        printf("Invalid input. Please enter a positive whole number: ");

        
    }
}

double getValidPositiveDouble(void)
{
    double value;
    char input[100];
    char extra;

    while (1)
    {
        if (fgets(input, sizeof(input), stdin) != NULL)
        {
            if (sscanf(input, "%lf %c", &value, &extra) == 1
                && value >= 0)
            {
                return value;
            }
        }

        printf("Invalid input. Please enter zero or a positive number: ");
    }
}
 
int isEmptyString(char text[])
{
    int i = 0;

    while (text[i] != '\0')
    {
       if (!isspace((unsigned char)text[i]))
        {
            return 0;
        }

        i++;
    }

    return 1;
}
int getValidString(char text[], int size)
{

    while (1)
    {
        if(fgets(text, size , stdin) == NULL)
        {
            return 0;
        }

            if (strchr(text, '\n') != NULL)
            {
               text[strcspn(text, "\n")] = '\0';
            }
            else
            {
                int ch;

            while ((ch = getchar()) != '\n' && ch != EOF)
            {

            }
            }

    

        if (!isEmptyString(text))
        {
            return 1;
        }

        printf("Input cannot be empty. Please try again: ");
    }
}
