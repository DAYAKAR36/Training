// Program to change a given name in the file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 20
#define FILE_NAME "Names.txt"

int change_name(char*);
void remove_new_line(char*);

void main()
{
    int is_changed;
    char *name_to_change = (char*)malloc(MAX_NAME_LENGTH);
    printf("Enter the name you want to change: ");
    fgets(name_to_change, MAX_NAME_LENGTH, stdin);
    // remove_new_line(name_to_change);
    is_changed = change_name(name_to_change);
    if (is_changed == 0)
    {
        printf("No name found");
    }
}

int change_name(char *name_to_change)
{
    int is_changed = 0;
    char *actual_name = (char*)malloc(MAX_NAME_LENGTH);
    FILE *fp_names = fopen(FILE_NAME, "r+");
    if (fp_names == NULL)
    {
        printf("File not opened\n");
        return 0;
    }
    rewind(fp_names);
    while (fgets(actual_name, MAX_NAME_LENGTH, fp_names))
    {
        if (strcmp(actual_name, name_to_change) == 0)
        {
            char new_name[MAX_NAME_LENGTH];
            printf("Name was found\nEnter the new name to change: ");
            fgets(new_name, MAX_NAME_LENGTH, stdin);
            int length = strlen(actual_name);
            // printf("%d\n", length);
            fseek(fp_names, -(length + 1), SEEK_CUR);
            remove_new_line(new_name);
            fputs(new_name, fp_names);
            is_changed = 1;
            return is_changed;
        }
    }
    fclose(fp_names);
    return is_changed;
}
