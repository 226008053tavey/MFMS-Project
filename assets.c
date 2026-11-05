#include <stdio.h>
#include <string.h>
#include "assets.h"
#include "validation.h"

#define MAX_ASSETS 100
#define ASSET_TEXT_LENGTH 100

/* Array used to store the registered assets. */
static Asset assets[MAX_ASSETS];
static int assetCount = 0;


static int findAssetById(int id)
{
    int i;

    for (i = 0; i < assetCount; i++) {
        if (assets[i].id == id) {
            return i;
        }
    }
    return -1;
}

static void addAsset(void)
{
    Asset newAsset;

    if (assetCount >= MAX_ASSETS) {
        printf("The asset register is full (maximum %d assets).\n", MAX_ASSETS);
        return;
    }

    puts("\n--- Add Asset ---");

    for (;;) {
        printf("Asset ID (positive whole number): ");
        newAsset.id = getValidPositiveInt();

        if (findAssetById(newAsset.id) >= 0) {
            puts("That asset ID is already registered. Choose a different ID.");
        } else {
            break;
        }
    }

    printf("Asset name: ");
    getValidString(newAsset.name, sizeof(newAsset.name));

    printf("Asset type (for example, Vehicle or Computer): ");
    getValidString(newAsset.type, sizeof(newAsset.type));

    printf("Purchase value (N$): ");
    newAsset.purchaseValue = getValidPositiveDouble();

    printf("Department: ");
    getValidString(newAsset.department, sizeof(newAsset.department));

    printf("Condition (for example, Good or Needs repair): ");
    getValidString(newAsset.condition, sizeof(newAsset.condition));

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
    if (assetCount == 0) {
        puts("No assets have been registered yet.");
        return;
    }

    for (i = 0; i < assetCount; i++) {
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

    if (assetCount == 0) {
        puts("No assets are registered yet.");
        return;
    }

    puts("\nSearch by:");
    puts("1. Asset ID");
    puts("2. Exact asset name");

    printf("Enter your choice: ");
    choice = getValidMenuChoice(1, 2);

    if (choice == 1) {
        printf("Enter asset ID: ");
        id = getValidPositiveInt();

        index = findAssetById(id);

        if (index < 0) {
            printf("No asset found with ID %d.\n", id);
        } else {
            puts("\nAsset found:");
            displayAsset(&assets[index]);
        }
    } else {
        printf("Enter the exact asset name: ");
        getValidString(name, sizeof(name));

        for (i = 0; i < assetCount; i++) {
            if (strcmp(assets[i].name, name) == 0) {
                puts("\nAsset found:");
                displayAsset(&assets[i]);
                found = 1;
            }
        }

        if (!found) {
            printf("No asset found with the name \"%s\".\n", name);
        }
    }
}

void displayAssetMenu(void)
{
    int choice;

    do {
        puts("\n================================");
        puts("       ASSET MANAGEMENT");
        puts("================================");
        puts("1. Add asset");
        puts("2. Display all assets");
        puts("3. Search for an asset");
        puts("4. Exit");

        choice = getValidMenuChoice(1, 4);

        switch (choice) {
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
        }

    } while (choice != 4);
}