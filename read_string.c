 // Function of read string.

#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 20

void read_string(char*);
char remove_new_line(char*);

void main()
{
	printf("Enter your name: ");
	char *name = (char*)malloc(MAX_NAME_LENGTH);
	read_string(name);
	printf("Your name is: %s", name);
}

void read_string(char *name)
{
	fgets(name, MAX_NAME_LENGTH, stdin);
	remove_new_line(name);
}