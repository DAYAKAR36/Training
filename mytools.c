#include <stdio.h>
#include <string.h>

void remove_new_line(char *string)
{
    char* lastLetter = &string[strlen(string) - 1];
    if (*lastLetter == '\n')
    {
        *lastLetter = '\0';
    }
}

void clear_buffer()
{
    while (getchar() != '\n');
}

void underline_text(int count)
{
    for (int counter = 0; counter < count; counter ++)
    {
        printf("-");
    }
}
