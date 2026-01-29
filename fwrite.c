 // Writing group of names into a file.

#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "Names.txt"
#define SIZE 20
void main()
{
	int number_of_names;
	printf("Enter the number of names you want to write: ");
	scanf("%d", &number_of_names);
	char **names = (char**)malloc(number_of_names*sizeof(char*));
	FILE *fp_names = fopen(FILE_NAME, "a");
	for (int name_counter = 0; name_counter < number_of_names; name_counter ++)
    {
        names[name_counter] = (char*)malloc(SIZE);
        printf("Enter name %d of %d: ", (name_counter+1), number_of_names);
        scanf("%s", names[name_counter]);
		fwrite(names[name_counter], SIZE, 1, fp_names);
	}
}