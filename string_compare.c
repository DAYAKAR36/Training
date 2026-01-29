 // Function  which behaves like strcmp().

#include <stdio.h>

#define MAX_STRING_SIZE 30

int string_compare(char*,char*);

void main()
{
	char string1[MAX_STRING_SIZE], string2[MAX_STRING_SIZE];
	printf("Enter string 1 to compare: ");
	scanf("%s", string1);
	printf("Enter string 2 to compare: ");
	scanf("%s", string2);
	int is_equal = string_compare(string1, string2);
	if (is_equal == 0)
	{
		printf("Given two strings are equal.\n");
	}
	else if (is_equal > 0)
	{
		printf("String 1 is bigger than string 2.\n");
	}
	else if (is_equal < 0)
	{
		printf("String 1 is smaller than string 2.\n");
	}
}


int string_compare(char *string1, char *string2)
{
	int difference, counter = 0;
	char character1, character2;
	while (string1[counter] != '\0' || string2[counter] != '\0')
	{
		character1 = string1[counter];
		character2 = string2[counter];
		if (character1 > character2)
		{
			return 1;
		}
		if (character1 < character2)
		{
			return -1;
		}
		counter ++;
	}
	return 0;
}