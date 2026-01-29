 // Print n numbers using single variable.

#include <stdio.h>

void print(int number)
{
	if (number == 0)
	{
		return;
	}
	print(number - 1);
	printf("%d\n", number);
}

void main()
{
	int number;
	printf("Enter range: ");
	scanf("%d", &number);
	print(number);
}