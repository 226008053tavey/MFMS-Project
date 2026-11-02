#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include "assets.h"

/* Array used to store the registered assets. */
Asset assets[MAX_ASSETS];
int assetCount = 0;

/* Reads one line of text and discards extra characters beyond the buffer. */
static void readLine(const char *prompt, char text[], size_t capacity)
{
    size_t length;
    int character;

    printf("%s", prompt);

    if (fgets(text, (int)capacity, stdin) == NULL)
    {
        text[0] = '\0';
        return;
    }

    length = strlen(text);

    if (length > 0 && text[length - 1] == '\n')
    {
        text[length - 1] = '\0';
    }
    else
    {
        while ((character = getchar()) != '\n' && character != EOF)
        {
        }
    }
}

static int isBlank(const char text[])
{
    size_t i;

    for (i = 0; text[i] != '\0'; i++)
    {
        if (!isspace((unsigned char)text[i]))
        {
            return 0;
        }
    }

    return 1;
}

/* Reads an integer between minimum and maximum, inclusive. */
static int readInteger(const char *prompt,
                       int minimum,
                       int maximum,
                       int *value)
{
    char input[ASSET_TEXT_LENGTH];
    char *end;
    long parsed;

    readLine(prompt, input, sizeof(input));

    errno = 0;
    parsed = strtol(input, &end, 10);

    while (isspace((unsigned char)*end))
    {
        end++;
    }

    if (isBlank(input) ||
        *end != '\0' ||
        errno != 0 ||
        parsed < minimum ||
        parsed > maximum)
    {
        return 0;
    }

    *value = (int)parsed;

    return 1;
}

/* Reads a valid non-negative purchase value. */
static int readPurchaseValue(double *value)
{
    char input[ASSET_TEXT_LENGTH];
    char *end;
    double parsed;

    readLine("Purchase value (N$): ", input, sizeof(input));

    errno = 0;
    parsed = strtod(input, &end);

    while (isspace((unsigned char)*end))
    {
        end++;
    }

    if (isBlank(input) ||
        *end != '\0' ||
        errno != 0 ||
        !isfinite(parsed) ||
        parsed < 0.0)
    {
        return 0;
    }

    *value = parsed;

    return 1;
}

static void readRequiredText(const char *prompt,
                             char text[],
                             size_t capacity)
{
    do
    {
        readLine(prompt, text, capacity);

        if (isBlank(text))
        {
            puts("This field cannot be empty. Please try again.");
        }

    } while (isBlank(text));
}

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

    for (;;)
    {
        if (!readInteger("Asset ID (positive whole number): ",
                         1,
                         INT_MAX,
                         &newAsset.id))
        {
            puts("Enter a valid positive whole number for the asset ID.");
        }
        else if (findAssetById(newAsset.id) >= 0)
        {
            puts("That asset ID is already registered. Choose a different ID.");
        }
        else
        {
            break;
        }
    }

    readRequiredText("Asset name: ",
                     newAsset.name,
                     sizeof(newAsset.name));

    readRequiredText("Asset type (for example, Vehicle or Computer): ",
                     newAsset.type,
                     sizeof(newAsset.type));

    while (!readPurchaseValue(&newAsset.purchaseValue))
    {
        puts("Enter a valid purchase value of zero or more.");
    }

    readRequiredText("Department: ",
                     newAsset.department,
                     sizeof(newAsset.department));

    readRequiredText("Condition (for example, Good or Needs repair): ",
                     newAsset.condition,
                     sizeof(newAsset.condition));

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

    if (!readInteger("Enter your choice: ", 1, 2, &choice))
    {
        puts("Invalid search choice.");
        return;
    }

    if (choice == 1)
    {
        if (!readInteger("Enter asset ID: ",
                         1,
                         INT_MAX,
                         &id))
        {
            puts("Invalid asset ID.");
            return;
        }

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
        readRequiredText("Enter the exact asset name: ",
                         name,
                         sizeof(name));

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

        if (!readInteger("Enter your choice: ",
                         1,
                         4,
                         &choice))
        {
            puts("Invalid menu choice. Enter a number from 1 to 4.");
            choice = 0;
            continue;
        }

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