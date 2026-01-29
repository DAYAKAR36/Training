// Read n names and print the longest using pointer

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    int number_of_names, max_name_length = 20, longest_name_length =0;
    printf("Enter the number of names you want to print the longest name among them: ");
    scanf("%d", &number_of_names);
    char **names = (char**)malloc(number_of_names*sizeof(char*));
    char *longest_name;
    for (int name_counter = 0; name_counter < number_of_names; name_counter ++)
    {
        names[name_counter] = (char*)malloc(max_name_length);
        printf("Enter name %d of %d: ", (name_counter+1), number_of_names);
        scanf("%s", names[name_counter]);
        if (name_counter == 0 || longest_name_length < strlen(names[name_counter]))
        {
            longest_name_length = strlen(names[name_counter]);
            longest_name = names[name_counter];
        }
    }   
    printf("Longest name among %d given names is %s with a length of %d characters. ", number_of_names, longest_name, longest_name_length);
}
