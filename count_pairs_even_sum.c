 // Counting the number of pairs whose sum is even.

#include <stdio.h>
#include <time.h>

int get_pair_count(int*, int);

/*void main()
{
	int array[1000];
	int length = sizeof(array) / sizeof(array[0]);
	for (int counter = 0; counter < length; counter++)
	{
		array[counter] = counter + 1;
	}
	int pair_count = 0;
	clock_t start = clock();
	pair_count = get_pair_count(array, length);
	clock_t end = clock();
	double time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Number of pairs with even sum: %d\n", pair_count);
	printf("Execution time: %.6f in milliseconds", time);
}

int get_pair_count(int *array, int size)
{
	int pair_count = 0;
	for (int outer_counter = 0; outer_counter < size; outer_counter++)
	{
		for (int inner_counter = outer_counter + 1; inner_counter < size; inner_counter++)
		{
			if ((array[outer_counter] + array[inner_counter]) % 2 == 0)
			{
				pair_count++;
			}
		}
	}
	return pair_count;
}*/

void main()
{
	int array[1000];
	int length = sizeof(array) / sizeof(array[0]);
	for (int counter = 0; counter < length; counter++)
	{
		array[counter] = counter + 1;
	}
	int pair_count = 0;
	clock_t start_time = clock();
	for (int counter = 0; counter < 1000; counter++)
	{
		pair_count = get_pair_count(array, length);
	}
	clock_t end_time = clock();
	printf("Execution time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
	printf("Number of pairs with even sum: %d\n", pair_count);
}

int get_pair_count(int *array, int size)
{
	int even_count = 0, odd_count = 0;
	for (int counter = 0; counter < size; counter++)
	{
		if (array[counter] % 2 == 0)
		{
			even_count++;
		}
		else
		{
			odd_count++;
		}
	}

	int pair_count = (even_count * (even_count - 1) / 2) + (odd_count * (odd_count - 1) / 2);
	return pair_count;
}

//clear
//print given name n times
//run