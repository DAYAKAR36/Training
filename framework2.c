// Framework for all domains menus.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MENU_FILE_NAME "menu.cfg"
#define FIELD_FILE_NAME "fieldnames.cfg"
#define RECORDS_FILE_NAME "records.dat"
#define MAX_MENU_LINE_SIZE 30
#define MAX_FIELD_NAME_SIZE 20
#define MAX_FIELD_VALUE_SIZE 15
#define ACTIVE 'Y'
#define INACTIVE 'N'
#define UPDATE 3
#define DELETE 4
#define DELETE_RECORD_TEXT "Successfully closed"

int record_size = 0;

void print_menu_options();
void create_record();
void clear_buffer();
void show_records();
int get_fields_count();
void update_record(int);
int is_record_exist(char*);
int get_record_index(char*);
char** load_fields_into_array(int);
int get_records_count(FILE*);
void removeNewline(char*);
void underlineText(int);

int main()
{
	int user_choice;
	int fields_count = get_fields_count();
	record_size = (fields_count * MAX_FIELD_VALUE_SIZE) + sizeof(char);
	while (1)
	{
		printf("\n");
		print_menu_options();
		scanf("%d", &user_choice);
		clear_buffer();
		switch (user_choice)
		{
			case 1:
				create_record();
				break;
			case 2:
				show_records();
				break;
			case 3:
				update_record(UPDATE);
				break;
			case 4:
				update_record(DELETE);
				break;	
			case 5:
				exit(0);
			default:
				printf("Invalid choice.\n");
				break;
		}
	}
}

void create_record()
{
	int fields_count = get_fields_count();
	char field_value[MAX_FIELD_VALUE_SIZE], status;
	char** field_names = load_fields_into_array(fields_count);
	FILE *fp_records = fopen(RECORDS_FILE_NAME, "a");
	for (int counter = 0; counter < fields_count; counter++)
	{
		printf("Enter %s: ", field_names[counter]);
		fgets(field_value, MAX_FIELD_VALUE_SIZE, stdin);
		removeNewline(field_value);
		fwrite(field_value, MAX_FIELD_VALUE_SIZE, 1, fp_records);
	}
	status = ACTIVE;
	fwrite(&status, sizeof(char), 1, fp_records);
	printf("Successfully opened.\n");
	fclose(fp_records);
}

void show_records()
{
	int total_field_names_length = 0, field_value_counter = 0, counter, fields_count = get_fields_count();
	char field_value[MAX_FIELD_VALUE_SIZE], status;
	char** field_names = load_fields_into_array(fields_count);
	for (counter = 0; counter < fields_count; counter++)
	{
		total_field_names_length += printf("%*s", MAX_FIELD_NAME_SIZE, field_names[counter]);
		if (counter == fields_count - 1)
		{
			printf("\n");
		}
		else
		{
			total_field_names_length += printf(" |");
		}
	}
	underlineText(total_field_names_length);
	FILE *fp_records = fopen(RECORDS_FILE_NAME, "r");
	int total_records = get_records_count(fp_records);
	rewind(fp_records);
	for (counter = 0; counter < total_records; counter++)
	{
		long record_position = ftell(fp_records);
		fseek(fp_records, fields_count * MAX_FIELD_VALUE_SIZE, SEEK_CUR);
		fread(&status, sizeof(char), 1, fp_records);
		if (status == ACTIVE)
		{
			fseek(fp_records, record_position, SEEK_SET);
			for (int field_value_counter = 1; field_value_counter <= fields_count; field_value_counter++)
			{
				fread(field_value, MAX_FIELD_VALUE_SIZE, 1, fp_records);
				printf("%*s", MAX_FIELD_NAME_SIZE, field_value);
				if (field_value_counter < fields_count)
				{
					printf(" |");
				}
				else
				{
					printf("\n");
				}
			}
		}
		fseek(fp_records, record_position + record_size, SEEK_SET);
	}
	fclose(fp_records);
}

void update_record(int mode)
{
	char  first_field_value[MAX_FIELD_VALUE_SIZE], last_field_value[MAX_FIELD_VALUE_SIZE];
	int record_index, fields_count = get_fields_count();
	char **field_names = load_fields_into_array(fields_count);
	printf("Enter %s: ", field_names[0]);
	fgets(first_field_value, MAX_FIELD_VALUE_SIZE, stdin);
	removeNewline(first_field_value);
	if (is_record_exist(first_field_value) == 1)
	{
		FILE *fp_records = fopen(RECORDS_FILE_NAME, "r+");
		record_index = get_record_index(first_field_value);
		if (record_index == -1)
		{
			printf("Record not found.\n");
			fclose(fp_records);
			return;
		}
		else
		{
			if (mode == UPDATE)
			{
				printf("Enter new %s: ", field_names[fields_count - 1]);
				fgets(last_field_value, MAX_FIELD_VALUE_SIZE, stdin);
				removeNewline(last_field_value);
				fseek(fp_records, record_index + (fields_count - 1) * MAX_FIELD_VALUE_SIZE, SEEK_SET);
				fwrite(last_field_value, MAX_FIELD_VALUE_SIZE, 1, fp_records);
				printf("%s", "Successfully updated");
			}
			else if (mode == DELETE)
			{
				char status = INACTIVE;
				fseek(fp_records, record_index + (fields_count * MAX_FIELD_VALUE_SIZE), SEEK_SET);
				fwrite(&status, sizeof(char), 1, fp_records);
				printf("%s", DELETE_RECORD_TEXT);
			}
			fclose(fp_records);
		}
	}
	else
	{
		printf("Record not found.\n");
	}
}

int get_record_index(char* first_field_value)
{
	int fields_count = get_fields_count();
	int record_index = -1;
	char field_value[MAX_FIELD_VALUE_SIZE], status;
	FILE *fp_records = fopen(RECORDS_FILE_NAME, "r");
	while (fread(field_value, MAX_FIELD_VALUE_SIZE, 1, fp_records) == 1)
	{
		fseek(fp_records, (fields_count - 1) * MAX_FIELD_VALUE_SIZE, SEEK_CUR);
		fread(&status, sizeof(char), 1, fp_records);
		if (status == ACTIVE && strcmp(first_field_value, field_value) == 0)
		{
			fseek(fp_records, -record_size, SEEK_CUR);
			record_index = ftell(fp_records);
			break;	
		}
	}
	fclose(fp_records);
	return record_index;
}

int get_records_count(FILE *fp_records)
{
	fseek(fp_records, 0, SEEK_END);
	long bytes_count = ftell(fp_records);
	int records_count = bytes_count / record_size;
	return records_count;
}

int is_record_exist(char* first_field_value)
{
	int fields_count = get_fields_count();
	int record_skip_size = fields_count * MAX_FIELD_VALUE_SIZE;
	char field_value[MAX_FIELD_VALUE_SIZE], status;
	FILE *fp_records = fopen(RECORDS_FILE_NAME, "r");
	while (fread(field_value, MAX_FIELD_VALUE_SIZE, 1, fp_records) == 1)
	{
		fseek(fp_records, (fields_count - 1) * MAX_FIELD_VALUE_SIZE, SEEK_CUR);
		fread(&status, sizeof(char), 1, fp_records);
		if (status == ACTIVE && strcmp(first_field_value, field_value) == 0)
		{
			fclose(fp_records);
			return 1;
		}
	}
	fclose(fp_records);
	return 0;
}

void print_menu_options()
{
	char menu[MAX_MENU_LINE_SIZE];
	FILE *fp_menu = fopen(MENU_FILE_NAME, "r");
	while (fgets(menu, MAX_MENU_LINE_SIZE, fp_menu))
	{
		printf("%s", menu);
	}
	fclose(fp_menu);
}

char** load_fields_into_array(int fields_count)
{
	char **field_names = malloc(fields_count * sizeof(char*));
	int field_counter = 0;
	FILE *fp_fields = fopen(FIELD_FILE_NAME, "r");
	while (field_counter < fields_count)
	{
		field_names[field_counter] = malloc(MAX_FIELD_NAME_SIZE);
		fgets(field_names[field_counter], MAX_FIELD_NAME_SIZE, fp_fields);
		removeNewline(field_names[field_counter]);
		field_counter++;
	}
	fclose(fp_fields);
	return field_names;
}

int get_fields_count()
{
	int field_counter = 0;
	char field_name[MAX_FIELD_NAME_SIZE];
	FILE *fp_fields = fopen(FIELD_FILE_NAME, "r");
	while (fgets(field_name, MAX_FIELD_NAME_SIZE, fp_fields))
	{
		field_counter++;
	}
	fclose(fp_fields);
	return field_counter;
}

void clear_buffer()
{
	int buffer_charecter;
	while ((buffer_charecter = getchar()) != '\n');
}

void removeNewline(char* text)
{
	char *last_character = &text[strlen(text) - 1];
	if (*last_character == '\n')
	{
		*last_character = '\0';
	}
}

void underlineText(int count)
{
	for (int counter = 0; counter < count; counter ++)
	{
		printf("-");
	}
	printf("\n");
}