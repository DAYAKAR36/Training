// Measures execution time and memory usage.

#include <stdio.h>
#include "clock.h"

void greet(char*);

void main()
{
    char name[20];
    printf("Enter name: ");
    scanf("%s", name);
    GET_EXECUTION_TIME(greet);
}

void greet(char *string)
{
    for (int counter = 0, x = printf("Hi %s!\n", string); counter < 100000000; counter ++);
}