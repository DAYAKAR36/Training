 // Framework for CRUD.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 20
#define FIELD_NAME_FILE "field_names.cfg"
#define MENU_FILE_NAME "menu.cfg"
#define DATA_FILE_NAME "records.dat"
#define ACTIVE 'a'
#define CLOSED 'c'
#define MODE_UPDATE 3
#define MODE_DELETE 4

void print_menu();
void create_records();
void read_records();
int read_field_names();
void clear_buffer();
void remove_new_line(char*);
int find_record_count();
void underline_text(int);
void update_record(char*, int);

int field_count = 0;
char field_names[10][MAX_SIZE];
int record_count;

void main()
{
	int choice;
	field_count = read_field_names();
	record_count = find_record_count();
	while (1)
	{
		print_menu();
		scanf("%d", &choice);
		clear_buffer();
		switch (choice)
		{
			case 1:
				create_records();
				break;
			case 2:
				read_records();
				break;
			case 3:
			case 4:
				char key_to_update[MAX_SIZE];
				printf("Enter the %s to Updated: ", field_names[0]);
				fgets(key_to_update, MAX_SIZE, stdin);
				remove_new_line(key_to_update);
				update_record(key_to_update, choice);
				break;
			case 5:
				exit(0);
			default:
				printf("Enter a valid choice\n ");
		}
	}
}

void print_menu()
{
	char menu[MAX_SIZE];
	FILE *fp_menu = fopen(MENU_FILE_NAME, "r");
	while (fgets(menu, sizeof(menu), fp_menu))
	{
		printf("%s", menu);
	}
	fclose(fp_menu);
}

void create_records()
{
	char field_value[MAX_SIZE];
	FILE *fp_data = fopen(DATA_FILE_NAME, "ab");
	for (int field_counter = 0; field_counter < field_count; field_counter ++)
	{
		printf("Enter %s: ", field_names[field_counter]);
		fgets(field_value, MAX_SIZE, stdin);
		remove_new_line(field_value);
		fwrite(field_value, MAX_SIZE, 1, fp_data);
	}
	char status = ACTIVE;
	fwrite(&status, sizeof(status), 1, fp_data);
	fclose(fp_data);
	record_count = find_record_count();
	printf("Record Successfully created.");
}

void read_records()
{
	char field_value[MAX_SIZE];
	printf("All Records Details...\n");
	for (int field_counter = 0; field_counter < field_count ; field_counter ++)
	{
		printf("|%-20s", field_names[field_counter]);	
	}
	printf("|\n");
	underline_text(20 * (field_count) + field_count + 1);
	printf("\n");
	FILE *fp_data = fopen(DATA_FILE_NAME, "rb");
	for (int record_counter = 0; record_counter < record_count; record_counter ++)
	{
		char status;
		int record_position = ftell(fp_data);
		fseek(fp_data, (record_position + (field_count) * MAX_SIZE), SEEK_SET);
		fread(&status, sizeof(status), 1, fp_data);
		if (status == ACTIVE)
		{
			fseek(fp_data, record_position, SEEK_SET);
			for (int field_counter = 0; field_counter < field_count; field_counter ++)
			{
				fread(field_value, MAX_SIZE, 1, fp_data);
				printf("|%-20s", field_value);
			}
			printf("|\n");
		}
		fseek(fp_data, record_position + ((field_count * MAX_SIZE) + 1), SEEK_SET);
	}
	printf("\n");
	fclose(fp_data);
}

void update_record(char *key_to_update, int mode)
{
	int is_updated = 0;
	char actual_key[MAX_SIZE];
	FILE *fp_data = fopen(DATA_FILE_NAME, "r+b");
	while (fread(actual_key, MAX_SIZE, 1, fp_data))
	{
		int record_position = ftell(fp_data) - MAX_SIZE;
		if (strcmp(actual_key, key_to_update) == 0)
		{
			char status;
			fseek(fp_data, record_position + field_count  * MAX_SIZE, SEEK_SET);
			fread(&status, sizeof(status), 1, fp_data);
			if (mode == MODE_UPDATE && status == ACTIVE)
			{
				is_updated = 1;
				char new_value[MAX_SIZE];
				printf("Enter the new value: ");
				fgets(new_value, MAX_SIZE, stdin);
				remove_new_line(new_value);
				fseek(fp_data, (record_position + (field_count - 1) * MAX_SIZE), SEEK_SET);
				fwrite(new_value, MAX_SIZE, 1, fp_data);
				break;
			}
			else if (mode == MODE_DELETE && status == ACTIVE)
			{
				char status = CLOSED;
				fseek(fp_data, (record_position + field_count * MAX_SIZE), SEEK_SET);
				fwrite(&status, sizeof(status), 1, fp_data);
				is_updated = 1;
				break;
			}
		}
		fseek(fp_data, record_position + field_count * MAX_SIZE + 1, SEEK_SET);
	}
	fclose(fp_data);
	if (is_updated == 1)
	{
		printf("Record Updated Successfully\n");
	}
	else
	{
		printf("No Record found\n");
	}
}

			
int read_field_names()
{
	int count = 0;
	char field_name[MAX_SIZE];
	FILE *fp_field_names = fopen(FIELD_NAME_FILE, "r");
	while (fgets(field_name, sizeof(field_name), fp_field_names))
	{
		remove_new_line(field_name);
		strcpy(field_names[count], field_name);
		count ++;
	}
	fclose(fp_field_names);
	return count;
}

int find_record_count()
{
	char field_value[MAX_SIZE];
	FILE *fp_data = fopen(DATA_FILE_NAME, "r");
	fseek(fp_data, 0, SEEK_END);
	int file_size = ftell(fp_data);
	return file_size/((field_count * MAX_SIZE) + 1);
}