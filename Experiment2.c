 // Print the addresses of 2 variables.

 #include <stdio.h>

void main()
{
	int number1 = 100;
	int number2 = 100;
	char character1 = 'D';
	char character2 = 'D';
	char array1[] = "Daya";
	char array2[] = "Daya";
	printf("Address of array1: %u\n", array1);
	printf("Address of array2: %u\n", array2);
	printf("Address of number1: %u\n", &number1);
	printf("Address of number2: %u\n", &number2);
	printf("Address of character1: %u\n", &character1);
	printf("Address of character2: %u\n", &character2);
	scanf("%d", &number1);
}