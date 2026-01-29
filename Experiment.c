 // Experiment on string literals.

#include <stdio.h>

void main()
{
	char *ptr_city1 = "Vizag";
	char *ptr_city2 = "Vizag";
	printf("Address of pointer 1: %u\n", ptr_city1);
	printf("Address of pointer 2: %u\n", ptr_city2);
}