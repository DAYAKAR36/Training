 // Read names from file and save them back into another file in alphabetically sorted order.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME "Names.txt"
#define MAX_NAME_LENGTH 20

int get_names_count();
void remove_new_line(char*);

void main()
{
	int name_count = get_names_count();
	char **names = (char**)malloc(name_count * sizeof(char*));
	char *temp = (char*)malloc(MAX_NAME_LENGTH);
	FILE *fp_names = fopen(FILE_NAME, "r");
	for (int counter = 0; counter < name_count; counter ++)
	{
		names[counter] = (char*)malloc(MAX_NAME_LENGTH);
		fgets(names[counter], MAX_NAME_LENGTH, fp_names);
		remove_new_line(names[counter]);
	}
	fclose(fp_names);
	for (int counter = 0; counter < name_count - 1; counter ++)
	{
		for (int counter2 = 0; counter2 < name_count - counter - 1; counter2 ++)
		{
			if (strcmp(names[counter2], names[counter2 + 1]) > 0)
			{
				strcpy(temp, names[counter2]);
				strcpy(names[counter2], names[counter2 + 1]);
				strcpy(names[counter2 + 1], temp);
			}
		}
	}
	FILE *fp_name = fopen("sorted_names.txt", "w");
	for (int counter = 0; counter < name_count; counter ++)
	{
		fputs(names[counter], fp_name);
		fputc('\n', fp_name);
	}
	fclose(fp_name);
}

int get_names_count()
{
	char name[MAX_NAME_LENGTH];
	int count = 0;
	FILE *fp_names = fopen(FILE_NAME, "r");
	while (fgets(name, MAX_NAME_LENGTH, fp_names))
	{
		count ++;
	}
	fclose(fp_names);
	return count;
}