// Program to perform CRUD operations on student details.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mytools.h"

#define id_size 10
#define name_size 30
#define file_name "Items.dat"

void add_item();
void show_all_items();
void update_item();
void delete_item();
void clear_the_file();

typedef struct item_details
{
    char id[id_size];
    char name[name_size];
    int price;
    char status;
} ITEM;

int const size_of_structure = sizeof(ITEM);
ITEM item;

void main()
{
    int option;
    do
    {
        printf("\n1.Add an item\n2.Show all items\n3.Update an item\n4.Delete an item\n5.Exit\n0.Clear the 'Items.dat' file\nEnter your choice: ");
        scanf("%d", &option);
        switch (option)
        {
            case 1 : add_item();
                     break;
            case 2 : show_all_items();
                     break;
            case 3 : update_item();
                     break;
            case 4 : delete_item();
                     break;
            case 5 : printf("\nTerminating execution\n");
                     exit(0);
            case 0 : clear_the_file();
                     break;
            default : printf ("\nEnter a valid option\n");
        }
    } while (1);
}

void add_item()
{
    printf("\nEnter details of item...\n");

    printf("Enter the item id: ");
    fflush(stdin);
    fgets(item.id, id_size, stdin);
    removeNewline(item.id);

    printf("Enter the item name: ");
    fgets(item.name, name_size, stdin);
    removeNewline(item.name);

    printf("Enter the price: ");
    scanf("%d", &item.price); 

    FILE *fp_items = fopen (file_name, "a");
    fwrite(&item, size_of_structure, 1, fp_items);
    fclose(fp_items);
}

void show_all_items()
{
    FILE *fp_items = fopen(file_name, "r");
    fseek(fp_items, 0, SEEK_END);
    if (ftell(fp_items) == 0)
        printf("\nNo items found!\n");
    else
    {
        rewind(fp_items);
        printf ("\nAll items...\n");
        printf("\n%-15s%-20s%-11s%-5s", "Item ID", "Name", "Price", "Status\n");
        printf("---------------------------------------------------------\n");
        while ((fread(&item, size_of_structure, 1, fp_items)) == 1)
        {
            printf("%-15s%-20s%-11d", item.id, item.name, item.price);
            if (item.status == 'U')
                printf("%-12s\n", "unavailable");
            else
                printf("\n");
        }
    }
    fclose(fp_items);
}

void clear_the_file()
{
    FILE *fp_accounts = fopen(file_name, "w");
    fclose(fp_accounts);
    printf("\n'Accounts.dat' file is cleared\n");
}

void update_item()
{
    char id[id_size];
    printf("\nEnter the id of the item to update its price: ");
    scanf("%s", id);
    FILE *fp_items = fopen(file_name, "r+");
    while ((fread(&item, size_of_structure, 1, fp_items)) == 1)
    {
        if (strcmp(item.id, id) == 0)
        {
            printf("Enter the new price: ");
            scanf("%d", &item.price);
            fseek(fp_items, -size_of_structure, SEEK_CUR);
            fwrite(&item, size_of_structure, 1, fp_items);
            printf("\nPrice updated\n");
            break;
        }
    }
    fclose(fp_items);
}

void delete_item()
{
    char id[id_size];
    printf("\nEnter the id of the item to delete it: ");
    scanf("%s", id);
    FILE *fp_items = fopen(file_name, "r+");
    while ((fread(&item, size_of_structure, 1, fp_items)) == 1)
    {
        if (strcmp(item.id, id) == 0)
        {
            fseek(fp_items, -size_of_structure, SEEK_CUR);
            item.status = 'U';
            fwrite(&item, size_of_structure, 1, fp_items);
            break;
        }
    }
    fclose(fp_items);
}