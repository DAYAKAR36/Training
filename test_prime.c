 // Unit testing for is_prime function.

#include <stdio.h>
#include <stdbool.h>

#define FAIL_MSG "Failed at input "
bool is_prime(int);

void main()
{
	int failed = 0;
	if (is_prime(0) == true)
	{
		printf("%s 0.\n", FAIL_MSG);
		failed = 1;	
	}
	if (is_prime(1) == true)
	{
		printf("%s 1.\n", FAIL_MSG);
		failed = 1;	
	}
	if (is_prime(-23) == true)
	{
		printf("%s -23.\n", FAIL_MSG);
		failed = 1;
	}
	if (is_prime(-22) == true)
	{
		printf("%s -22.\n", FAIL_MSG);
		failed = 1;	
	}
	if (is_prime(2) == false)
	{
		printf("%s 2.\n", FAIL_MSG);
		failed = 1;	
	}
	if (is_prime(22) == true)
	{
		printf("%s 22.\n", FAIL_MSG);
		failed = 1;	
	}
	if (is_prime(3) == false)
	{
		printf("%s 3.\n", FAIL_MSG);
		failed = 1;	
	}
	if (is_prime(5) == false)
	{
		printf("%s 5.\n", FAIL_MSG);
		failed = 1;	
	}
	if (is_prime(97) == false)
	{
		printf("%s 97.\n", FAIL_MSG);
		failed = 1;	
	}
	if (failed == 0)
	{
		printf("All test cases are passed.");
	}
}
