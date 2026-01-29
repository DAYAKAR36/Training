 // Read and print n names using a function without passing parameters.

#include <stdio.h>
#include <stdlib.h>

void remove_new_line(char*);
char **read_n_names();
void clear_buffer();

void main()
{
	char **names = read_n_names();
	int count = atoi(names[0]);
	for (int name_counter = 1; name_counter <= count; name_counter++)
	{
		printf("Name %d of %d: %s\n", name_counter, count, names[name_counter]);
	}
}

char **read_n_names()
{
	int count, max_name_length = 15;
	printf("Enter the number of names you want to read and print them: ");
	scanf("%d", &count);
	clear_buffer();
	char **names = (char**)malloc((count+1)*sizeof(char*));
	for (int name_counter = 0; name_counter <= count; name_counter ++)
	{
		if (name_counter == 0)
		{
			names[name_counter] = (char*)malloc(sizeof(char*));
			itoa(count, names[name_counter], 10);
		}
		else
		{
			names[name_counter] = (char*)malloc(max_name_length);
			printf("Enter name %d of %d: ", name_counter, count);
			fgets(names[name_counter], max_name_length, stdin);
			remove_new_line(names[name_counter]);
		}
	}
	return names;
}