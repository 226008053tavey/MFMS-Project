#ifndef ASSETS_H
#define ASSETS_H

#define MAX_ASSETS 100
#define ASSET_TEXT_LENGTH 100

typedef struct
{
    int id;
    char name[ASSET_TEXT_LENGTH];
    char type[ASSET_TEXT_LENGTH];
    double purchaseValue;
    char department[ASSET_TEXT_LENGTH];
    char condition[ASSET_TEXT_LENGTH];
} Asset;

void displayAssetMenu(void);

#endif