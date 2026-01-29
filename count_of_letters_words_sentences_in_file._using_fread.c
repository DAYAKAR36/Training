// Print the count of letters, words and sentences in a file using fread().

#include <stdio.h>

#define file_name "file_operations.txt"

void main()
{
	int letter_counter = 0, word_counter = 0, sentence_counter = 0;
	int file_counter = 0;
	char character;
	FILE *fp = fopen (file_name, "r");
	fseek(fp, 0, SEEK_END);
	int size_of_file = ftell (fp);
	char content[size_of_file];
	rewind (fp);
	fread (content, size_of_file, 1, fp);
	while (file_counter < size_of_file)
	{
		// fread(&character, 1, 1, fp);
		character = content[file_counter];
		if (character == ' ')
		{
			word_counter ++;
		}
		else if (character == '.')
		{
			sentence_counter ++;
		}
		else
		{
			letter_counter ++;
		}
		file_counter ++;
	}
	printf("The count of letters, words and sentences in a file are %d, %d and %d respectively. ", letter_counter, (word_counter+1), sentence_counter);
	fclose(fp);
}
