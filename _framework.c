 // Framework for CRUD.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIELDS_FILE_NAME "fieldnames.cfg"
#define MENU_FILE_NAME "menu.cfg"
#define SIZE 30
#define DATA_FILE_NAME "records.dat"

void print_menu();
void read_field_names(char field_names[][SIZE]);
void create_record(char field_names[][SIZE]);
void show_all_records(char field_names[][SIZE]);
void clear_buffer();
void remove_new_line(char*);
int find_record_count();
int get_field_count();
void update_record(char*);
void delete_record(char*);

int field_count = 0;

void main()
{
    int choice;
    field_count = get_field_count();
    char field_names[field_count][SIZE];
    read_field_names(field_names);
    while (1)
    {
        print_menu();
        scanf("%d", &choice);
        clear_buffer();
        switch (choice)
        {
            case 1:
                create_record(field_names);
                break;
            case 2:
                show_all_records(field_names);
                break;
            case 3:
                char id_to_update[SIZE];
                printf("Enter %s to be updated: ", field_names[0]);
                scanf("%s", id_to_update);
                clear_buffer();
                update_record(id_to_update);
                break;
            case 4:
                char id_to_search[SIZE];
                printf("Enter %s to be delete: ", field_names[0]);
                scanf("%s", id_to_search);
                clear_buffer();
                delete_record(id_to_search);
                break;
            case 5:
                exit(0);
            default:
                printf("Enter a valid choice\n");
        }
    }
}

void create_record(char field_names[][SIZE])
{
    char data[SIZE];
    FILE *fp_field_value = fopen(DATA_FILE_NAME, "a");
    for (int field_counter = 0; field_counter < field_count; field_counter ++)
    {
        printf("Enter %s: ", field_names[field_counter]);
        fgets(data, SIZE, stdin);
        remove_new_line(data);
        fwrite(data, SIZE, 1, fp_field_value);
    }
    char status = 'a';
    fputc(status, fp_field_value);
    fclose(fp_field_value);
}

void show_all_records(char field_names[][SIZE])
{
    char field_value[SIZE];
    char status;
    int record_count = find_record_count(field_count);
    FILE *fp_records = fopen(DATA_FILE_NAME, "rb");
    printf("All record details:\n");
    for (int record_counter = 0; record_counter < record_count; record_counter++)
    {
        long record_position = ftell(fp_records);
        fseek(fp_records, field_count*SIZE, SEEK_SET);
        // fread(&status, sizeof(char), 1, fp_records);
        status = fgetc(fp_records);
        if (status == 'a')
        {
            fseek(fp_records, record_position, SEEK_SET);
            printf("Record %d details:\n", (record_counter+1));
            for (int field_counter = 0; field_counter < field_count; field_counter++)
            {
                fread(field_value, SIZE, 1, fp_records);
                printf("%s: %s\n", field_names[field_counter], field_value);
            }
        }
        fseek(fp_records, record_position + ((SIZE*field_count)+1), SEEK_SET);
    }

}

void update_record(char *id)
{
    int found = 0;
    char actual_id[SIZE];
    FILE *fp_records = fopen(DATA_FILE_NAME, "r+b");
    while ((fread(actual_id, SIZE, 1, fp_records)) == 1)
    {
        if (strcmp(actual_id, id) == 0)
        {
            char new_rank[SIZE];
            found = 1;
            printf("Enter the new rank: ");
            scanf("%s", new_rank);
            fseek(fp_records, SIZE, SEEK_CUR);
            fwrite(new_rank, SIZE, 1, fp_records);
            break;
        }
        fseek(fp_records, (SIZE * (field_count - 1))+1, SEEK_CUR);
    }
    fclose(fp_records);
    if (found == 1)
    {
        printf("Updated.\n");
    }
    else
    {
        printf("No id found.\n");
    }
}

void delete_record(char *id)
{
    int found = 0;
    char actual_id[SIZE];
    FILE *fp_records = fopen(DATA_FILE_NAME, "r+b");
    while ((fread(actual_id, SIZE, 1, fp_records)) == 1)
    {
        if (strcmp(actual_id, id) == 0)
        {
            fseek(fp_records, (SIZE* 2), SEEK_CUR);
            char status = 'c';
            fputc(status, fp_records);
            found = 1;
            break;
        }
        fseek(fp_records, (SIZE * 2)+1, SEEK_CUR);
    }
    fclose(fp_records);
    if (found == 1)
    {
        printf("Deleted.\n");
    }
    else
    {
        printf("No id found.\n");
    }
}


void print_menu()
{
    
    FILE *fp_menu = fopen(MENU_FILE_NAME, "r");
    char menu[SIZE];
    while((fgets(menu, SIZE, fp_menu)) != NULL)
    {
        printf("%s", menu);
    }
    fclose(fp_menu);
}

void clear_buffer()
{
    while (getchar() != '\n');
}

void remove_new_line(char *string)
{
    char* lastLetter = &string[strlen(string) - 1];
    if (*lastLetter == '\n')
    {
        *lastLetter = '\0';
    }
}

void read_field_names(char field_names[][SIZE])
{
    FILE *fp_field_names = fopen(FIELDS_FILE_NAME, "r");
    for (int field_counter = 0; field_counter < field_count; field_counter++)
    {
           fgets(field_names[field_counter], sizeof(field_names[field_counter]), fp_field_names);
           remove_new_line(field_names[field_counter]);
    }
    fclose(fp_field_names);
}

int find_record_count(int field_count)
{
    FILE *fp_records = fopen(DATA_FILE_NAME, "r");
    fseek(fp_records, 0, SEEK_END);
    int file_size = ftell(fp_records);
    fclose(fp_records);
    return file_size/((field_count*SIZE) + sizeof(char));
}

int get_field_count()
{
    char field_name[SIZE];
    int field_count = 0;
    FILE *fp_field_names = fopen(FIELDS_FILE_NAME, "r");
    while (fgets(field_name, SIZE, fp_field_names) != NULL)
    {
           field_count ++;
    }
    fclose(fp_field_names);
    return field_count;
}
