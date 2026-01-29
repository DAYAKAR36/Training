 // Experiment with extern variable.

#include <stdio.h>

extern int sum;

int add(int , int);

void main()
{
	int number1, number2;
	printf("Enter number 1 to add: ");
	scanf("%d", &number1);
	printf("Enter number 2 to add: ");
	scanf("%d", &number2);
	add(number1, number2);
	printf("Sum of %d and %d is %d. ", number1, number2, sum);
}