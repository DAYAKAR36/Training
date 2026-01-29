// Read and print name using pointer

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void removeNewLine(char *);
 
void main()
{
    int length = 20;
    char *name=(char*)malloc(length);
    printf("Enter name: ");
    fgets(name, length, stdin);
    removeNewLine(name);
    printf("Hi %s! ", name);
}

void removeNewLine(char *text)
{
    char *lastCharacter = &text[strlen(text) - 1];
    if (*lastCharacter == '\n')
    {
        *lastCharacter = '\0';
    }
}
 