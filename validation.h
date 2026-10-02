#ifndef VALIDATION_H
#define VALIDATION_H

int getValidMenuChoice(int min, int max);
int getValidPositiveInt(void);
double getValidPositiveDouble(void);
int isEmptyString(char text[]);
int getValidString(char text[], int size);

#endif