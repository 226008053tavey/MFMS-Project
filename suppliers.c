#include <stdio.h>
#include <string.h>
#include "suppliers.h"
#include "validation.h"

int supplierIDs[MAX_SUPPLIERS];
char supplierNames[MAX_SUPPLIERS][MAX_STRING_LEN];
char supplierEmails[MAX_SUPPLIERS][MAX_STRING_LEN];
char supplierPhones[MAX_SUPPLIERS][MAX_STRING_LEN];
char supplierTowns[MAX_SUPPLIERS][MAX_STRING_LEN];
int supplierCount = 0;

static int findSupplierByID(int id)
{
    int i;

    for (i = 0; i < supplierCount; i++)
    {
        if (supplierIDs[i] == id)
        {
            return i;
        }
    }

    return -1;
}

void displaySupplierMenu(void)
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("       MFMS SUPPLIER MANAGEMENT MODULE  \n");
        printf("========================================\n");
        printf("1. Add New Supplier\n");
        printf("2. Display All Registered Suppliers\n");
        printf("3. Search for Supplier by Name\n");
        printf("4. Save Supplier Database to File\n");
        printf("5. Load Supplier Database from File\n");
        printf("6. Return to Main Menu\n");
        printf("========================================\n");

        choice = getValidMenuChoice(1, 6);

        switch (choice)
        {
            case 1:
                addSupplier();
                break;

            case 2:
                displayAllSuppliers();
                break;

            case 3:
                searchSupplierByName();
                break;

            case 4:
                saveSuppliersToFile();
                break;

            case 5:
                loadSuppliersFromFile();
                break;

            case 6:
                printf("Returning to the main menu...\n");
                break;
        }

    } while (choice != 6);
}

void addSupplier(void)
{
    int id;

    if (supplierCount >= MAX_SUPPLIERS)
    {
        printf("Supplier limit reached. Maximum is %d.\n",
               MAX_SUPPLIERS);
        return;
    }

    printf("\n===== ADD NEW SUPPLIER =====\n");

    while (1)
    {
        printf("Enter Supplier ID: ");
        id = getValidPositiveInt();

        if (findSupplierByID(id) != -1)
        {
            printf("That Supplier ID already exists. Please use another ID.\n");
        }
        else
        {
            break;
        }
    }

    supplierIDs[supplierCount] = id;

    printf("Enter Supplier Name: ");
    getValidString(supplierNames[supplierCount],
                   MAX_STRING_LEN);

    printf("Enter Email Address: ");
    getValidString(supplierEmails[supplierCount],
                   MAX_STRING_LEN);

    printf("Enter Phone Number: ");
    getValidString(supplierPhones[supplierCount],
                   MAX_STRING_LEN);

    printf("Enter Town Location: ");
    getValidString(supplierTowns[supplierCount],
                   MAX_STRING_LEN);

    supplierCount++;

    printf("Supplier added successfully!\n");
}

void displayAllSuppliers(void)
{
    int i;

    if (supplierCount == 0)
    {
        printf("\nNo suppliers registered.\n");
        return;
    }

    printf("\n=================================================================================\n");
    printf("%-5s | %-20s | %-20s | %-12s | %-12s\n",
           "ID", "Name", "Email", "Phone", "Town");
    printf("=================================================================================\n");

    for (i = 0; i < supplierCount; i++)
    {
        printf("%-5d | %-20s | %-20s | %-12s | %-12s\n",
               supplierIDs[i],
               supplierNames[i],
               supplierEmails[i],
               supplierPhones[i],
               supplierTowns[i]);
    }

    printf("=================================================================================\n");
}

void searchSupplierByName(void)
{
    char searchTarget[MAX_STRING_LEN];
    int i;

    if (supplierCount == 0)
    {
        printf("\nNo suppliers registered.\n");
        return;
    }

    printf("\n===== SEARCH SUPPLIER =====\n");
    printf("Enter Supplier Name: ");

    getValidString(searchTarget, MAX_STRING_LEN);

    for (i = 0; i < supplierCount; i++)
    {
        if (strcmp(supplierNames[i], searchTarget) == 0)
        {
            printf("\nSupplier Found!\n");
            printf("ID    : %d\n", supplierIDs[i]);
            printf("Name  : %s\n", supplierNames[i]);
            printf("Email : %s\n", supplierEmails[i]);
            printf("Phone : %s\n", supplierPhones[i]);
            printf("Town  : %s\n", supplierTowns[i]);
            return;
        }
    }

    printf("Supplier '%s' was not found.\n", searchTarget);
}

void saveSuppliersToFile(void)
{
    FILE *filePointer;
    int i;

    filePointer = fopen("suppliers.txt", "w");

    if (filePointer == NULL)
    {
        printf("Error: Unable to save supplier data.\n");
        return;
    }

    for (i = 0; i < supplierCount; i++)
    {
        fprintf(filePointer,
                "%d|%s|%s|%s|%s\n",
                supplierIDs[i],
                supplierNames[i],
                supplierEmails[i],
                supplierPhones[i],
                supplierTowns[i]);
    }

    fclose(filePointer);

    printf("Successfully saved %d supplier record(s).\n",
           supplierCount);
}

void loadSuppliersFromFile(void)
{
    FILE *filePointer;
    int tempID;
    char tempName[MAX_STRING_LEN];
    char tempEmail[MAX_STRING_LEN];
    char tempPhone[MAX_STRING_LEN];
    char tempTown[MAX_STRING_LEN];
    int loadedRecordsCount = 0;

    filePointer = fopen("suppliers.txt", "r");

    if (filePointer == NULL)
    {
        printf("No supplier data file found.\n");
        return;
    }

    while (loadedRecordsCount < MAX_SUPPLIERS &&
           fscanf(filePointer,
                  "%d|%49[^|]|%49[^|]|%49[^|]|%49[^\n]",
                  &tempID,
                  tempName,
                  tempEmail,
                  tempPhone,
                  tempTown) == 5)
    {
        supplierIDs[loadedRecordsCount] = tempID;

        strcpy(supplierNames[loadedRecordsCount], tempName);
        strcpy(supplierEmails[loadedRecordsCount], tempEmail);
        strcpy(supplierPhones[loadedRecordsCount], tempPhone);
        strcpy(supplierTowns[loadedRecordsCount], tempTown);

        loadedRecordsCount++;
    }

    fclose(filePointer);

    supplierCount = loadedRecordsCount;

    printf("Successfully loaded %d supplier record(s).\n",
           supplierCount);
}