 // CRUD operations for any domain.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FIELDS 20
#define MAX_FIELD_NAME 50
#define MAX_FIELD_VALUE 100
#define MAX_LINE 1024

#define DATA_FILE "data.dat"
#define TEMP_FILE "temp.dat"

void trim_newline(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}

int is_empty_line(const char *str)
{
    while (*str)
    {
        if (*str != ' ' && *str != '\t' && *str != '\n')
        {
            return 0;
        }
        str++;
    }
    return 1;
}

FILE *open_file(const char *filename, const char *mode)
{
    FILE *fp = fopen(filename, mode);
    if (fp == NULL)
    {
        printf("%s not found\n", filename);
        exit(1);
    }
    return fp;
}

void read_key(char *key, const char *field_name)
{
    printf("Enter %s: ", field_name);
    fgets(key, MAX_FIELD_VALUE, stdin);
    trim_newline(key);
}

int is_key_match(const char *line, const char *key)
{
    char copy[MAX_LINE];
    strcpy(copy, line);

    char *first = strtok(copy, "|");
    if (first != NULL && strcmp(first, key) == 0)
    {
        return 1;
    }
    return 0;
}

int load_fields(char fields[][MAX_FIELD_NAME])
{
    FILE *fp = open_file("fieldnames.cfg", "r");
    char line[MAX_FIELD_NAME];
    int count = 0;

    while (fgets(line, sizeof(line), fp))
    {
        trim_newline(line);

        if (is_empty_line(line))
        {
            continue;
        }

        strcpy(fields[count], line);
        count++;
    }

    fclose(fp);
    return count;
}

int print_menu(void)
{
    FILE *fp = open_file("menu.cfg", "r");
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), fp))
    {
        printf("%s", line);
    }

    fclose(fp);

    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    return choice;
}

void create_record(char fields[][MAX_FIELD_NAME], int field_count)
{
    FILE *fp = open_file(DATA_FILE, "a");

    for (int i = 0; i < field_count; i++)
    {
        char value[MAX_FIELD_VALUE];
        printf("Enter %s: ", fields[i]);
        fgets(value, sizeof(value), stdin);
        trim_newline(value);
        fprintf(fp, "%s|", value);
    }

    fprintf(fp, "\n");
    fclose(fp);
}

void read_records(char fields[][MAX_FIELD_NAME], int field_count)
{
    FILE *fp = open_file(DATA_FILE, "r");

    for (int i = 0; i < field_count; i++)
    {
        printf("%-15s", fields[i]);
    }
    printf("\n");

    for (int i = 0; i < field_count; i++)
    {
        printf("---------------");
    }
    printf("\n");

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), fp))
    {
        char *token = strtok(line, "|");
        while (token)
        {
            printf("%-15s", token);
            token = strtok(NULL, "|");
        }
        printf("\n");
    }

    fclose(fp);
}

void update_record(char fields[][MAX_FIELD_NAME], int field_count)
{
    FILE *fp = fopen(DATA_FILE, "r");
    if (fp == NULL)
    {
        return;
    }

    FILE *temp = open_file(TEMP_FILE, "w");

    char key[MAX_FIELD_VALUE];
    read_key(key, fields[0]);

    char line[MAX_LINE];
    int found = 0;

    while (fgets(line, sizeof(line), fp))
    {
        if (is_key_match(line, key))
        {
            found = 1;
            fprintf(temp, "%s|", key);

            for (int i = 1; i < field_count; i++)
            {
                char value[MAX_FIELD_VALUE];
                printf("Enter %s: ", fields[i]);
                fgets(value, sizeof(value), stdin);
                trim_newline(value);
                fprintf(temp, "%s", value);
            }
            fprintf(temp, "\n");
        }
        else
        {
            fputs(line, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(DATA_FILE);
    rename(TEMP_FILE, DATA_FILE);

    if (!found)
    {
        printf("Record not found\n");
    }
}

void delete_record(char fields[][MAX_FIELD_NAME])
{
    FILE *fp = fopen(DATA_FILE, "r");
    if (fp == NULL)
    {
        return;
    }

    FILE *temp = open_file(TEMP_FILE, "w");

    char key[MAX_FIELD_VALUE];
    read_key(key, fields[0]);

    char line[MAX_LINE];
    int found = 0;

    while (fgets(line, sizeof(line), fp))
    {
        if (is_key_match(line, key))
        {
            found = 1;
            continue;
        }
        fputs(line, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(DATA_FILE);
    rename(TEMP_FILE, DATA_FILE);

    if (!found)
    {
        printf("Record not found\n");
    }
}

int main(void)
{
    char fields[MAX_FIELDS][MAX_FIELD_NAME];
    int field_count = load_fields(fields);

    while (1)
    {
        int choice = print_menu();

        switch (choice)
        {
            case 1:
            {
                create_record(fields, field_count);
                break;
            }
            case 2:
            {
                read_records(fields, field_count);
                break;
            }
            case 3:
            {
                update_record(fields, field_count);
                break;
            }
            case 4:
            {
                delete_record(fields);
                break;
            }
            case 5:
            {
                exit(0);
            }
            default:
            {
                printf("Invalid choice\n");
            }
        }
    }
}
