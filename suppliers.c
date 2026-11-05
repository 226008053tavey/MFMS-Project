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
        
        choice = getValidMenuChoice(1, 6);

        switch (choice) 
        {
            case 1: addSupplier(); break;
            case 2: displayAllSuppliers(); break;
            case 3: searchSupplierByName(); break;
            case 4: saveSuppliersToFile(); break;
            case 5: loadSuppliersFromFile(); break;
            case 6: printf("Returning to the main framework...\n"); break;
            default: printf("Invalid option selected. Please try again.\n");
        }
    } while (choice != 6);
}

void addSupplier(void)
{
    if (supplierCount >= MAX_SUPPLIERS)
    {
        printf("Database full! Maximum capacity reached.\n");
        return;
    }

    printf("\n--- Add New Supplier Details ---\n");

    printf("Enter Supplier ID (Positive Integer): ");
    supplierIDs[supplierCount] = getValidPositiveInt();

    printf("Enter Supplier Name: ");
    if (!getValidString(supplierNames[supplierCount], MAX_STRING_LEN))
    {
        printf("Unable to read supplier name.\n");
        return;
    }

    printf("Enter Email Address: ");
    if (!getValidString(supplierEmails[supplierCount], MAX_STRING_LEN))
    {
        printf("Unable to read supplier email.\n");
        return;
    }

    printf("Enter Phone Number: ");
    if (!getValidString(supplierPhones[supplierCount], MAX_STRING_LEN))
    {
        printf("Unable to read supplier phone number.\n");
        return;
    }

    printf("Enter Town Location: ");
    if (!getValidString(supplierTowns[supplierCount], MAX_STRING_LEN))
    {
        printf("Unable to read supplier town.\n");
        return;
    }

    supplierCount++;

    printf("Supplier entry successfully logged into local memory buffer!\n");
}
void displayAllSuppliers(void) 
{
    if (supplierCount == 0) 
    {
        printf("\nNo suppliers currently residing in memory. Try loading from file.\n");
        return;
    }

    printf("\n=================================================================================\n");
    printf("%-5s | %-20s | %-20s | %-12s | %-12s\n", "ID", "Name", "Email", "Phone", "Town");
    printf("=================================================================================\n");
    for (int i = 0; i < supplierCount; i++) 
    {
        printf("%-5d | %-20s | %-20s | %-12s | %-12s\n",
               supplierIDs[i], supplierNames[i], supplierEmails[i], supplierPhones[i], supplierTowns[i]);
    }
    printf("=================================================================================\n");
}

void searchSupplierByName(void)
{
    if (supplierCount == 0)
    {
        printf("\nNo suppliers registered. Please add or load suppliers first.\n");
        return;
    }

    char searchTarget[MAX_STRING_LEN];

    printf("\nEnter full Supplier Name to search: ");

    if (!getValidString(searchTarget, MAX_STRING_LEN))
    {
        printf("Unable to read supplier name.\n");
        return;
    }

    int found = 0;

    for (int i = 0; i < supplierCount; i++)
    {
        if (strcmp(supplierNames[i], searchTarget) == 0)
        {
            printf("\nSupplier Found!\n");
            printf("ID    : %d\n", supplierIDs[i]);
            printf("Name  : %s\n", supplierNames[i]);
            printf("Email : %s\n", supplierEmails[i]);
            printf("Phone : %s\n", supplierPhones[i]);
            printf("Town  : %s\n", supplierTowns[i]);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Supplier '%s' does not exist.\n", searchTarget);
    }
}

void saveSuppliersToFile(void) 
{
    FILE *filePointer = fopen("suppliers.txt", "w");
    if (filePointer == NULL) 
    {
        perror("Critical Error: Unable to open suppliers.txt for writing");
        return;
    }

    for (int i = 0; i < supplierCount; i++) 
    {
        fprintf(filePointer, "%d|%s|%s|%s|%s\n",
                supplierIDs[i], supplierNames[i], supplierEmails[i], supplierPhones[i], supplierTowns[i]);
    }

    fclose(filePointer); 
    printf("System Notification: Successfully saved %d supplier records persistently!\n", supplierCount);
}

void loadSuppliersFromFile(void)
{
    FILE *filePointer = fopen("suppliers.txt", "r");

    if (filePointer == NULL)
    {
        printf("Notice: Supplier file 'suppliers.txt' not found.\n");
        return;
    }

    int tempID;
    char tempName[MAX_STRING_LEN];
    char tempEmail[MAX_STRING_LEN];
    char tempPhone[MAX_STRING_LEN];
    char tempTown[MAX_STRING_LEN];

    int loadedRecordsCount = 0;

    while (loadedRecordsCount < MAX_SUPPLIERS &&
           fscanf(filePointer,
                  "%d|%49[^|]|%49[^|]|%49[^|]|%49[^\n]\n",
                  &tempID,
                  tempName,
                  tempEmail,
                  tempPhone,
                  tempTown) == 5)
    {
        if (tempID <= 0)
        {
            continue;
        }

        supplierIDs[loadedRecordsCount] = tempID;

        strcpy(supplierNames[loadedRecordsCount], tempName);
        strcpy(supplierEmails[loadedRecordsCount], tempEmail);
        strcpy(supplierPhones[loadedRecordsCount], tempPhone);
        strcpy(supplierTowns[loadedRecordsCount], tempTown);

        loadedRecordsCount++;
    }

    fclose(filePointer);

    supplierCount = loadedRecordsCount;

    printf("Successfully loaded %d supplier records.\n", supplierCount);
}