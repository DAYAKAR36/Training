 //  Print the contents of a file.

#include <stdio.h>

#define file_name "names.txt"

void main()
{
	int size_of_file;
	FILE *fp = fopen(file_name, "r");
	fseek(fp, 0, SEEK_END);
	size_of_file = ftell(fp);
	printf("%s file size is %d.\n", file_name, size_of_file);
	char content[size_of_file];
	rewind(fp);
	fread(content, 1, size_of_file, fp);
	fwrite(content, 1, size_of_file, stdout);
	fclose(fp);
} 
 

/* //  Print the contents of a file.

#include <stdio.h>

#define file_name "print_all_bytes_of_string.c"

int const size_of_file = 500;

void main()
{
	FILE *fp = fopen(file_name, "r");
	char content[size_of_file];
	size_t n = fread(content, size_of_file, 1, fp);
	printf("%d", n);
	fwrite(content, n, 1, stdout);
	fclose(fp);
} */

/*#include <stdio.h>

#define file_name "print_all_bytes_of_string.c"

int const size_of_file = 500;

void main()
{
	FILE *fp = fopen(file_name, "r");
	char character;
	while((character = fgetc(fp)) != EOF)
	{
		printf("%c", character);
	}
	fclose(fp);
}
*/