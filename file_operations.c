 // Menu driven program for file operations.

#include <stdio.h>
#include <stdlib.h>

// #define file_name "names.txt"
// #define size 20

void save_name();
void display_names();

char const file_name[] = "names.txt";
int const size = 20;
void main()
{
	int option;
	do
	{
		printf("\n1. Save a name\n2. Show all names\n3. Exit\nEnter your choice: ");
		scanf("%d", &option);
		getchar();
		switch(option)
		{
		case 1:
			save_name();
			break;
		case 2:
			display_names();
			break;
		case 3:
			exit(0);
			break;
		default:
			printf("Entered invalid option.");
		}
	}while(1);
}

void save_name()
{
    char name[size];
    FILE *fp;
    int counter = 0;
    printf("Enter name: ");
    fgets(name, size, stdin);
    fp = fopen(file_name, "a");
    fwrite(name, size, 1, fp);
    //fputs(name, fp);
    // fprintf(fp, "%s", name);
    // while(name[counter] != '\0')
    // {
    //     fputc(name[counter], fp);
    //     counter ++;
    // }
    fclose(fp);
}

void display_names()
{
	char name[size];
	char character;
	FILE *fp = fopen(file_name, "r");
	//	while((character = fgetc(fp)) != EOF)
	//     {
	//         printf("%c", character);
	//     }
	// while((fgets(name, size, fp)) != NULL)
	// {
	//  	printf("%s", name);
	// }
	while(fscanf(fp, "%s", name) != -1)
	{
		printf("%s\n", name);
	}
	// while(fread(name, size, 1, fp) == 1)
	// {
	// 	printf("%s", name);
	// }
	fclose(fp);
}
