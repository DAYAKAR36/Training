#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FIELDS 10
#define NAME_SIZE  20

/* ---------- STRUCTURES ---------- */

typedef struct
{
    char field_name[NAME_SIZE];
    char field_type[10];
    int field_size;
    int position;
} FIELD;

typedef struct
{
    char domain_name[NAME_SIZE];
    int number_of_fields;
    FIELD fields[MAX_FIELDS];
    int total_size;
} DOMAIN;

/* ---------- FUNCTIONS ---------- */

void clear_buffer();
void read_cfg(char *cfg_file, DOMAIN *domain);
void add_record(DOMAIN *domain, char *data_file);
void show_all_records(DOMAIN *domain, char *data_file);
void update_record(DOMAIN *domain, char *data_file);
void delete_record(DOMAIN *domain, char *data_file);

/* ---------- MAIN ---------- */

int main()
{
    DOMAIN domain;
    int choice;

    char cfg_file[]  = "student.cfg";
    char data_file[] = "student.dat";

    read_cfg(cfg_file, &domain);

    do
    {
        printf("\n--- %s CRUD MENU ---\n", domain.domain_name);
        printf("1. Add Record\n");
        printf("2. Show All Records\n");
        printf("3. Update Record\n");
        printf("4. Delete Record\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        clear_buffer();

        switch (choice)
        {
            case 1: add_record(&domain, data_file); break;
            case 2: show_all_records(&domain, data_file); break;
            case 3: update_record(&domain, data_file); break;
            case 4: delete_record(&domain, data_file); break;
            case 5: exit(0);
            default: printf("Invalid choice\n");
        }
    } while (1);
}

/* ---------- READ CFG ---------- */

void read_cfg(char *cfg_file, DOMAIN *domain)
{
    FILE *fp = fopen(cfg_file, "r");
    int i, pos = 0;

    fscanf(fp, "%s", domain->domain_name);
    fscanf(fp, "%d", &domain->number_of_fields);

    for (i = 0; i < domain->number_of_fields; i++)
    {
        fscanf(fp, "%s %s %d",
               domain->fields[i].field_name,
               domain->fields[i].field_type,
               &domain->fields[i].field_size);

        domain->fields[i].position = pos;

        if (strcmp(domain->fields[i].field_type, "int") == 0)
            pos += sizeof(int);
        else if (strcmp(domain->fields[i].field_type, "char") == 0)
            pos += sizeof(char);
        else
            pos += domain->fields[i].field_size;
    }

    domain->total_size = pos;
    fclose(fp);
}
/* ---------- ADD RECORD ---------- */

void add_record(DOMAIN *domain, char *data_file)
{
    char record[domain->total_size];
    int i;

    memset(record, 0, domain->total_size);

for (i = 0; i < domain->number_of_fields; i++)
{
    if (strcmp(domain->fields[i].field_type, "int") == 0)
    {
        printf("Enter %s: ", domain->fields[i].field_name);
        scanf("%d", (int *)(record + domain->fields[i].position));
        clear_buffer();   // remove leftover newline
    }
    else if (strcmp(domain->fields[i].field_type, "char") == 0)
    {
        printf("Enter %s: ", domain->fields[i].field_name);
        scanf(" %c", (char *)(record + domain->fields[i].position));
        clear_buffer();   // remove leftover newline
    }
    else   /* string */
    {
        clear_buffer();   // remove leftover '\n' from previous input
        printf("Enter %s: ", domain->fields[i].field_name);
        fgets(record + domain->fields[i].position,
              domain->fields[i].field_size, stdin);

        /* remove trailing newline */
        record[domain->fields[i].position +
               strcspn(record + domain->fields[i].position, "\n")] = '\0';
    }
}


    FILE *fp = fopen(data_file, "ab");
    fwrite(record, domain->total_size, 1, fp);
    fclose(fp);

    printf("Record added successfully!\n");
}


/* ---------- SHOW ALL RECORDS ---------- */

void show_all_records(DOMAIN *domain, char *data_file)
{
    char record[domain->total_size];
    int i;

    FILE *fp = fopen(data_file, "rb");
    if (!fp)
    {
        printf("No records found.\n");
        return;
    }

    printf("\n--- ALL RECORDS ---\n\n");

    /* Print header */
    for (i = 0; i < domain->number_of_fields; i++)
        printf("%-15s", domain->fields[i].field_name);
    printf("\n");

    /* Separator */
    for (i = 0; i < domain->number_of_fields; i++)
        printf("---------------");
    printf("\n");

    /* Print rows */
    while (fread(record, domain->total_size, 1, fp) == 1)
    {
        for (i = 0; i < domain->number_of_fields; i++)
        {
            if (strcmp(domain->fields[i].field_type, "int") == 0)
                printf("%-15d", *(int *)(record + domain->fields[i].position));
            else if (strcmp(domain->fields[i].field_type, "char") == 0)
                printf("%-15c", *(char *)(record + domain->fields[i].position));
            else
                printf("%-15s", record + domain->fields[i].position);
        }
        printf("\n");
    }

    fclose(fp);
}

/* ---------- UPDATE (by KEY FIELD) ---------- */

void update_record(DOMAIN *domain, char *data_file)
{
    char key[50];
    char record[domain->total_size];
    int i, found = 0;

    printf("Enter %s to update: ", domain->fields[0].field_name);
    scanf("%s", key);
    clear_buffer();

    FILE *fp = fopen(data_file, "r+b");

    while (fread(record, domain->total_size, 1, fp) == 1)
    {
        if (strcmp(record + domain->fields[0].position, key) == 0)
        {
            found = 1;

            for (i = 1; i < domain->number_of_fields; i++)
            {
                printf("Enter new %s: ", domain->fields[i].field_name);

                if (strcmp(domain->fields[i].field_type, "int") == 0)
                    scanf("%d", (int *)(record + domain->fields[i].position));
                else if (strcmp(domain->fields[i].field_type, "char") == 0)
                    scanf(" %c", (char *)(record + domain->fields[i].position));
                else
                    fgets(record + domain->fields[i].position,
                          domain->fields[i].field_size, stdin);

                clear_buffer();
            }

            fseek(fp, -domain->total_size, SEEK_CUR);
            fwrite(record, domain->total_size, 1, fp);
            break;
        }
    }
    fclose(fp);

    if (found)
        printf("Record updated successfully!\n");
    else
        printf("Record not found!\n");
}

/* ---------- DELETE (status = 'd') ---------- */

void delete_record(DOMAIN *domain, char *data_file)
{
    char key[50];
    char record[domain->total_size];
    int found = 0;

    printf("Enter %s to delete: ", domain->fields[0].field_name);
    scanf("%s", key);
    clear_buffer();

    FILE *fp = fopen(data_file, "r+b");

    while (fread(record, domain->total_size, 1, fp) == 1)
    {
        if (strcmp(record + domain->fields[0].position, key) == 0)
        {
            found = 1;
            *(char *)(record + domain->fields[domain->number_of_fields - 1].position) = 'd';

            fseek(fp, -domain->total_size, SEEK_CUR);
            fwrite(record, domain->total_size, 1, fp);
            break;
        }
    }
    fclose(fp);

    if (found)
        printf("Record deleted successfully!\n");
    else
        printf("Record not found!\n");
}

/* ---------- CLEAR BUFFER ---------- */

void clear_buffer()
{
    while (getchar() != '\n');
}
