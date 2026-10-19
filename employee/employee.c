#include <stdio.h>
int main(void)
{
 FILE *fp = fopen("employees.txt", "w");
 if (fp == NULL) {
 perror("employees.txt");
 return 1;
 }
 fprintf(fp, "%d %s %.2f\n", 1001, "Maria", 18500.50);
 fprintf(fp, "%d %s %.2f\n", 1002, "Simon", 17200.00);
 fclose(fp);
 return 0;
}
