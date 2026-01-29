// Experiment with scanf().

#include <stdio.h>

#define size 15
void main()
{
	char name[size], id[size];
	printf("Enter name: ");
	scanf("%s", name);
	printf("Name: %s", name);
	printf("Enter id: ");
	scanf("%s", id);
	printf("Id: %s", id);
}