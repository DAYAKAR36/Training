 // Print all bytes of a string variable including garbage.

#include <stdio.h>

void main()
{
	int size = 30;
	char string[size];
	printf("Enter string: ");
	scanf("%s", string);
	fwrite(string, size, 1, stdout);
}