 // Bubble sorting

#include <stdio.h>

void main()
{
	int count;
	printf("Enter count of numbers you want to sort: ");
	scanf("%d", &count);
	int numbers[count];
	printf("Enter the numbers you want to sort:\n");
	for (int counter = 0; counter < count; counter ++)
	{
		printf("Enter number %d of %d: ", counter + 1, count);
		scanf("%d", &numbers[counter]);
	}
	for (int counter = 0; counter < count - 1; counter ++)
	{
		for (int counter2 = 0; counter2 < count - counter - 1; counter2 ++)
		{
			if (numbers[counter2] > numbers[counter2 + 1])
			{
				int temp = numbers[counter2];
				numbers[counter2] = numbers[counter2 + 1];
				numbers[counter2 + 1] = temp;
			}
		}
	}
	printf("Sorted Array:\n");
	for (int counter = 0; counter < count; counter ++)
	{
		printf("%d  ", numbers[counter]);
	}
}