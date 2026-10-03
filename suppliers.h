#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#define MAX_SUPPLIERS 5
#define MAX_STRING_LEN 50

extern int supplierIDs[MAX_SUPPLIERS];
extern char supplierNames[MAX_SUPPLIERS][MAX_STRING_LEN];
extern char supplierEmails[MAX_SUPPLIERS][MAX_STRING_LEN];
extern char supplierPhones[MAX_SUPPLIERS][MAX_STRING_LEN];
extern char supplierTowns[MAX_SUPPLIERS][MAX_STRING_LEN];
extern int supplierCount;

void displaySupplierMenu(void);
void addSupplier(void);
void displayAllSuppliers(void);
void searchSupplierByName(void);
void saveSuppliersToFile(void);
void loadSuppliersFromFile(void);

#endif 