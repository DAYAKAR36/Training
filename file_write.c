 // Writing into a file.

#include <stdio.h>

void main()
{
	FILE *fpText;
	int size = 100;
	char text[size];
	printf("Enter text: ");
	fgets(text, size, stdin);
	fpText = fopen("message.txt", "w");
	fputs(text, fpText);
	fprintf(fpText, "%s", text);
	fwrite(text, size, 1, fpText);
	fclose(fpText);
}
