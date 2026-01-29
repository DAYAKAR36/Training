// Print the count of letters, words and sentences in a file.

#include <stdio.h>

#define file_name "file_operations.txt"

void main()
{
	int letter_counter = 0, word_counter = 0, sentence_counter = 0;
	char character;
	FILE *fp = fopen(file_name, "r");
	while ((character = fgetc(fp)) != EOF)
	{
		if (character == ' ')
		{
			word_counter += 1;
		}
		else if (character == '.')
		{
			sentence_counter += 1;
		}
		else
		{
			letter_counter += 1;
		}
	}
	printf("The count of letters, words and sentences in a file are %d, %d and %d respectively. ", letter_counter, (word_counter+1), sentence_counter);
	fclose(fp);
}