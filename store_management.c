// Program to perform CRUD operations on item of store.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mytools.h"

#define ID_SIZE 15
#define NAME_SIZE 30
#define FILE_NAME "Items.dat"

void add_item();
void show_all_items();
void update_item();
void delete_item();

typedef struct item_details
{
    char id[ID_SIZE];
    char name[NAME_SIZE];
    int price;
    char status;
} ITEM;

int const size_of_structure = sizeof(ITEM);

void main()
{
    int choice;
    do
    {
        printf("1.Add an item\n2.Show all items\n3.Update an item\n4.Delete an item\n5.Exit\nEnter your choice: ");
        scanf("%d", &choice);
        clear_buffer();
        switch(choice)
        {
            case 1:
                 add_item();
                 break;
            case 2:
                 show_all_items();
                 break;
            case 3: 
                update_item();
                break;
            case 4: 
                delete_item();
                break;
            case 5:
                exit(0);
            default: 
                printf ("\nEnter a valid option:\n");
        }
    } while (1);
}

void add_item()
{
    ITEM item;
    printf("Enter details of item:\n");

    printf("Enter the item id: ");
    fgets(item.id, ID_SIZE, stdin);
    remove_new_line(item.id);

    printf("Enter the item name: ");
    fgets(item.name, NAME_SIZE, stdin);
    remove_new_line(item.name);

    printf("Enter the price: ");
    scanf("%d", &item.price); 
    clear_buffer();

    item.status = 'a';

    FILE *fp_items = fopen(FILE_NAME, "a");
    fwrite(&item, size_of_structure, 1, fp_items);
    fclose(fp_items);
}

void show_all_items()
{
    ITEM item;
    FILE *fp_items = fopen(FILE_NAME, "r");
    printf ("\nAll items:");
    printf("\n%-20s%-20s%-11s%-5s", "Item ID", "Name", "Price", "Status\n");
    printf("---------------------------------------------------------\n");
    while ((fread(&item, size_of_structure, 1, fp_items)) == 1)
    {
        printf("%-20s%-20s%-11d", item.id, item.name, item.price);
        if (item.status == 'u')
        {
            printf("%-12s\n", "Unavailable");
        }
        else
        {
            printf("%-10s\n", "Available");
        }
    }
    fclose(fp_items);
}

void update_item()
{
    ITEM item;
    char id[ID_SIZE];
    printf("\nEnter the id of the item to update its price: ");
    scanf("%s", id);
    FILE *fp_items = fopen(FILE_NAME, "r+");
    while ((fread(&item, size_of_structure, 1, fp_items)) == 1)
    {
        if (strcmp(item.id, id) == 0)
        {
            printf("Enter the new price: ");
            scanf("%d", &item.price);
            fseek(fp_items, -size_of_structure, SEEK_CUR);
            fwrite(&item, size_of_structure, 1, fp_items);
            break;
        }
    }
    fclose(fp_items);
}

void delete_item()
{
    ITEM item;
    char id[ID_SIZE];
    printf("\nEnter the id of the item to delete it: ");
    scanf("%s", id);
    FILE *fp_items = fopen(FILE_NAME, "r+");
    while ((fread(&item, size_of_structure, 1, fp_items)) == 1)
    {
        if (strcmp(item.id, id) == 0)
        {
            fseek(fp_items, -size_of_structure, SEEK_CUR);
            item.status = 'u';
            fwrite(&item, size_of_structure, 1, fp_items);
            break;
        }
    }
    fclose(fp_items);
}