 // Reading from a file.

#include <stdio.h>

void main()
{
	FILE *fpText;
	char character;
	fpText = fopen("message.txt", "r");
	while((character = fgetc(fpText)) != -1)
	{
		printf("%c", character);
	}
	fclose(fpText);
}
