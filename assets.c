#include <stdio.h>
#include <string.h>
#include "assets.h"
#include "validation.h"

/* Array used to store the registered assets. */
Asset assets[MAX_ASSETS];
int assetCount = 0;

static int findAssetById(int id)
{
    int i;

    for (i = 0; i < assetCount; i++)
    {
        if (assets[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

static void addAsset(void)
{
    Asset newAsset;

    if (assetCount >= MAX_ASSETS)
    {
        printf("The asset register is full (maximum %d assets).\n",
               MAX_ASSETS);
        return;
    }

    puts("\n--- Add Asset ---");
    puts("Enter Q at any prompt to cancel asset registration.");

    /* Asset ID */
    for (;;)
    {
        printf("Asset ID (positive whole number): ");

        if (!getValidPositiveIntOrCancel(&newAsset.id))
        {
            puts("Asset registration cancelled.");
            return;
        }

        if (findAssetById(newAsset.id) >= 0)
        {
            puts("That asset ID is already registered. Choose a different ID.");
        }
        else
        {
            break;
        }
    }

    /* Asset name */
    printf("Asset name: ");

    if (!getValidString(newAsset.name, sizeof(newAsset.name)))
        return;

    if (strcmp(newAsset.name, "Q") == 0 ||
        strcmp(newAsset.name, "q") == 0)
    {
        puts("Asset registration cancelled.");
        return;
    }

    /* Asset type */
    printf("Asset type (for example, Vehicle or Computer): ");

    if (!getValidString(newAsset.type, sizeof(newAsset.type)))
        return;

    if (strcmp(newAsset.type, "Q") == 0 ||
        strcmp(newAsset.type, "q") == 0)
    {
        puts("Asset registration cancelled.");
        return;
    }

    /* Purchase value */
    printf("Purchase value (N$): ");

    if (!getValidPositiveDoubleOrCancel(&newAsset.purchaseValue))
    {
        puts("Asset registration cancelled.");
        return;
    }

    /* Department */
    printf("Department: ");

    if (!getValidString(newAsset.department, sizeof(newAsset.department)))
        return;

    if (strcmp(newAsset.department, "Q") == 0 ||
        strcmp(newAsset.department, "q") == 0)
    {
        puts("Asset registration cancelled.");
        return;
    }

    /* Condition */
    printf("Condition (for example, Good or Needs repair): ");

    if (!getValidString(newAsset.condition, sizeof(newAsset.condition)))
        return;

    if (strcmp(newAsset.condition, "Q") == 0 ||
        strcmp(newAsset.condition, "q") == 0)
    {
        puts("Asset registration cancelled.");
        return;
    }

    assets[assetCount] = newAsset;
    assetCount++;

    puts("Asset added successfully.");
}
static void displayAsset(const Asset *asset)
{
    printf("Asset ID:       %d\n", asset->id);
    printf("Asset name:     %s\n", asset->name);
    printf("Asset type:     %s\n", asset->type);
    printf("Purchase value: N$%.2f\n", asset->purchaseValue);
    printf("Department:     %s\n", asset->department);
    printf("Condition:      %s\n", asset->condition);
}

static void displayAllAssets(void)
{
    int i;

    puts("\n--- Asset Register ---");

    if (assetCount == 0)
    {
        puts("No assets have been registered yet.");
        return;
    }

    for (i = 0; i < assetCount; i++)
    {
        printf("\nAsset %d of %d\n", i + 1, assetCount);
        displayAsset(&assets[i]);
    }
}

static void searchAsset(void)
{
    int choice;
    int id;
    int index;
    int i;
    char name[ASSET_TEXT_LENGTH];
    int found = 0;

    if (assetCount == 0)
    {
        puts("No assets are registered yet.");
        return;
    }

    puts("\nSearch by:");
    puts("1. Asset ID");
    puts("2. Exact asset name");

printf("Enter your choice: ");
choice = getValidMenuChoice(1, 2);

if (choice == 1){
    printf("Enter asset ID: ");
    id = getValidPositiveInt();

        index = findAssetById(id);

        if (index < 0)
        {
            printf("No asset found with ID %d.\n", id);
        }
        else
        {
            puts("\nAsset found:");
            displayAsset(&assets[index]);
        }
    }
    else
    {
        printf("Enter the exact asset name: ");
getValidString(name, sizeof(name));

        for (i = 0; i < assetCount; i++)
        {
            if (strcmp(assets[i].name, name) == 0)
            {
                puts("\nAsset found:");
                displayAsset(&assets[i]);
                found = 1;
            }
        }

        if (!found)
        {
            printf("No asset found with the name \"%s\".\n", name);
        }
    }
}

void displayAssetMenu(void)
{
    int choice = 0;

    do
    {
        puts("\n================================");
        puts("       ASSET MANAGEMENT");
        puts("================================");
        puts("1. Add asset");
        puts("2. Display all assets");
        puts("3. Search for an asset");
        puts("4. Exit");

        choice = getValidMenuChoice(1, 4);

        switch (choice)
        {
            case 1:
                addAsset();
                break;

            case 2:
                displayAllAssets();
                break;

            case 3:
                searchAsset();
                break;

            case 4:
                puts("Exiting Asset Management.");
                break;

            default:
                puts("Invalid choice.");
        }

    } while (choice != 4);
}