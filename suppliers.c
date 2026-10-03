#include <stdio.h>
#include <string.h>
#include "suppliers.h"

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
        printf("Enter choice: ");
        
        if (scanf("%d", &choice) != 1) 
        {
            printf("Invalid selection! Input must be a valid number.\n");
            while (getchar() != '\n'); 
            continue;
        }
        while (getchar() != '\n'); 

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
    if (scanf("%d", &supplierIDs[supplierCount]) != 1 || supplierIDs[supplierCount] <= 0) 
    {
        printf("Invalid ID configuration! Must be a positive integer number.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n'); 

    printf("Enter Supplier Name: ");
    fgets(supplierNames[supplierCount], MAX_STRING_LEN, stdin);
    supplierNames[supplierCount][strcspn(supplierNames[supplierCount], "\n")] = '\0'; 

    if (strlen(supplierNames[supplierCount]) == 0) 
    {
        printf("Validation Error: Supplier name field cannot be blank.\n");
        return;
    }

    printf("Enter Email Address: ");
    fgets(supplierEmails[supplierCount], MAX_STRING_LEN, stdin);
    supplierEmails[supplierCount][strcspn(supplierEmails[supplierCount], "\n")] = '\0';

    printf("Enter Phone Number: ");
    fgets(supplierPhones[supplierCount], MAX_STRING_LEN, stdin);
    supplierPhones[supplierCount][strcspn(supplierPhones[supplierCount], "\n")] = '\0';

    printf("Enter Town Location: ");
    fgets(supplierTowns[supplierCount], MAX_STRING_LEN, stdin);
    supplierTowns[supplierCount][strcspn(supplierTowns[supplierCount], "\n")] = '\0';

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
        printf("\nNo active supplier data maps loaded in system runtime arrays.\n");
        return;
    }

    char searchTarget[MAX_STRING_LEN];
    printf("\nEnter full Supplier Name to search: ");
    fgets(searchTarget, MAX_STRING_LEN, stdin);
    searchTarget[strcspn(searchTarget, "\n")] = '\0'; 

    int found = 0;
    for (int i = 0; i < supplierCount; i++) 
    {
        if (strcmp(supplierNames[i], searchTarget) == 0) 
        {
            printf("\nSupplier Found! Displaying information records:\n");
            printf("ID      : %d\nName    : %s\nEmail   : %s\nPhone   : %s\nTown    : %s\n",
                   supplierIDs[i], supplierNames[i], supplierEmails[i], supplierPhones[i], supplierTowns[i]);
            found = 1;
            break; 
        }
    }

    if (!found) 
    {
        printf("Search unconfirmed. Supplier name '%s' does not exist.\n", searchTarget);
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
        printf("Notice: Persistence storage file 'suppliers.txt' not found. Starting fresh.\n");
        return;
    }

    int tempID;
    char tempName[MAX_STRING_LEN];
    char tempEmail[MAX_STRING_LEN];
    char tempPhone[MAX_STRING_LEN];
    char tempTown[MAX_STRING_LEN];
    int loadedRecordsCount = 0;

    while (fscanf(filePointer, "%d|%49[^|]|%49[^|]|%49[^|]|%49[^\n]\n",
                  &tempID, tempName, tempEmail, tempPhone, tempTown) == 5) 
    {
        if (loadedRecordsCount >= MAX_SUPPLIERS) 
        {
            break;
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
    printf("System Notification: Successfully loaded %d records into active memory structures!\n", supplierCount);
}