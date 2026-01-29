 // Experiment on strcmp() function.

#include <stdio.h>
#include <string.h>

#define SIZE_OF_STRING 15

void main()
{
	char string1[SIZE_OF_STRING], string2[SIZE_OF_STRING];
	printf("Enter string 1: ");
	scanf("%s", string1);
	printf("Enter string 2: ");
	scanf("%s", string2);
	int compared_value = strcmp(string1, string2);
	printf("%d", compared_value);
}