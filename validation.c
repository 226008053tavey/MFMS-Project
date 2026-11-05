#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <float.h>
#include "validation.h"

/* Clears the remaining characters in the input line. */
static void clearInputBuffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

/* Reads a complete line and removes the newline character. */
static int readInputLine(char text[], int size)
{
    if (fgets(text, size, stdin) == NULL)
    {
        return 0;
    }

    if (strchr(text, '\n') != NULL)
    {
        text[strcspn(text, "\n")] = '\0';
    }
    else
    {
        int ch = getchar();

        if (ch != '\n' && ch != EOF)
        {
            clearInputBuffer();
            return -1;
        }
    }

    return 1;
}

int getValidMenuChoice(int min, int max)
{
    char input[100];
    char *end;
    long choice;

    while (1)
    {
        printf("Enter your choice: ");

        if (readInputLine(input, sizeof(input)) == 0)
        {
            return min;
        }

        errno = 0;
        choice = strtol(input, &end, 10);

        while (isspace((unsigned char)*end))
        {
            end++;
        }

        if (end != input && *end == '\0' &&
            errno != ERANGE && choice >= min && choice <= max)
        {
            return (int)choice;
        }

        printf("Invalid choice. Please enter a number between %d and %d.\n",
               min, max);
    }
}

int getValidPositiveInt(void)
{
    char input[100];
    char *end;
    long value;

    while (1)
    {
        if (readInputLine(input, sizeof(input)) == 0)
        {
            return 0;
        }

        errno = 0;
        value = strtol(input, &end, 10);

        while (isspace((unsigned char)*end))
        {
            end++;
        }

        if (end != input && *end == '\0' &&
            errno != ERANGE && value > 0 && value <= INT_MAX)
        {
            return (int)value;
        }

        printf("Invalid input. Please enter a positive whole number: ");
    }
}
int getValidPositiveIntOrCancel(int *value)
{
    char input[100];
    char *end;
    char *start;
    long number;

    while (1)
    {
        if (readInputLine(input, sizeof(input)) == 0)
            return 0;

        start = input;

        while (isspace((unsigned char)*start))
            start++;

        if ((start[0] == 'Q' || start[0] == 'q') &&
            start[1] == '\0')
            return 0;

        errno = 0;
        number = strtol(start, &end, 10);

        while (isspace((unsigned char)*end))
            end++;

        if (end != start && *end == '\0' &&
            errno != ERANGE && number > 0 && number <= INT_MAX)
        {
            *value = (int)number;
            return 1;
        }

        printf("Invalid input. Enter a positive whole number or Q to cancel: ");
    }
}
double getValidPositiveDouble(void)
{
    char input[100];
    char *end;
    double value;

    while (1)
    {
        if (readInputLine(input, sizeof(input)) == 0)
        {
            return 0.0;
        }

        errno = 0;
        value = strtod(input, &end);

        while (isspace((unsigned char)*end))
        {
            end++;
        }

        if (end != input && *end == '\0' &&
            errno != ERANGE && value > 0 && value <= DBL_MAX)
        {
            return value;
        }

        printf("Invalid input. Please enter a positive number: ");
    }
}
int getValidPositiveDoubleOrCancel(double *value)
{
    char input[100];
    char *end;
    double number;
    char *start;

    while (1)
    {
        if (readInputLine(input, sizeof(input)) == 0)
            return 0;

        start = input;

        while (isspace((unsigned char)*start))
            start++;

        if ((start[0] == 'Q' || start[0] == 'q') &&
            start[1] == '\0')
            return 0;

        errno = 0;
        number = strtod(start, &end);

        while (isspace((unsigned char)*end))
            end++;

        if (end != start && *end == '\0' &&
            errno != ERANGE && number > 0 && number <= DBL_MAX)
        {
            *value = number;
            return 1;
        }

        printf("Invalid input. Enter a positive number or Q to cancel: ");
    }
}

int isEmptyString(char text[])
{
    int i;

    if (text == NULL)
    {
        return 1;
    }

    for (i = 0; text[i] != '\0'; i++)
    {
        if (!isspace((unsigned char)text[i]))
        {
            return 0;
        }
    }

    return 1;
}

int getValidString(char text[], int size)
{
    int result;

    if (text == NULL || size <= 0)
    {
        return 0;
    }

    while (1)
    {
        result = readInputLine(text, size);

        if (result == 0)
        {
            return 0;
        }

        if (result == 1 && !isEmptyString(text))
        {
            return 1;
        }

        printf("Input cannot be empty or too long. Please try again: ");
    }
}