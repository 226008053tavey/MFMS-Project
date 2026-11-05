#ifndef VALIDATION_H
#define VALIDATION_H

int getValidMenuChoice(int min, int max);
int getValidPositiveInt(void);
int getValidPositiveIntOrCancel(int *value);
double getValidPositiveDouble(void);
int getValidPositiveDoubleOrCancel(double *value);
int isEmptyString(char text[]);
int getValidString(char text[], int size);

#endif