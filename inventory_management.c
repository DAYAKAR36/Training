 // CRUD on inventory management using linked list.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID_SIZE 20
#define MAX_NAME_SIZE 30
#define FILE_NAME "Items.dat"
#define ITEM_NOT_FOUND printf("Item not found...\n");

typedef struct inventory_management
{
	char id[MAX_ID_SIZE];
	char name[MAX_NAME_SIZE];
	int stock_quantity;
	int price;
}ITEM;

typedef struct node_item
{
	ITEM item;
	struct node_item *next_item;
}NODE;

int size_of_item = sizeof(ITEM);
NODE *start = NULL, *end = NULL;

void add_item(ITEM);
void display(NODE*);
void underline_text(int);
void save_list();
void load_data_from_file_to_list();
void sort_list(int);
NODE* get_item(char*);
void update_item(NODE*, int);
void delete_item(NODE*);

void main()
{
	int choice;
	ITEM item;
	NODE *node_item;
	char id[MAX_NAME_SIZE];
	load_data_from_file_to_list();
	while (1)
	{
		printf("1. Add item\n2. Show all items\n3. Update item price\n4. Delete an item\n5. Sort by price\n6. Sort by name\n7. Exit\nEnter your choice: ");
		scanf("%d", &choice);
		switch (choice)
		{
			case 1:
				printf("Enter item details:\n");
				printf("Enter id: ");
				scanf("%s", item.id);
				printf("Enter name: ");
				scanf("%s", item.name);
				printf("Enter quantity: ");
				scanf("%d", &item.stock_quantity);
				printf("Enter price: ");
				scanf("%d", &item.price);
				add_item(item);
				printf("Item added successfully...\n");
				save_list();
				break;
			case 2:
				display(start);
				break;
			case 3:
				printf("Enter item id to update: ");
				scanf("%s", id);
				node_item = get_item(id);
				if (node_item == NULL)
				{
					ITEM_NOT_FOUND;
				}
				else
				{
					int price;
					printf("Enter new item price: ");
					scanf("%d", &price);
					update_item(node_item, price);
					printf("Item updated successfully...\n");
				}
				save_list();
				break;
			case 4:
				printf("Enter item id to delete: ");
				scanf("%s", id);
				node_item = get_item(id);
				if (node_item == NULL)
				{
					ITEM_NOT_FOUND;
				}
				else
				{
					delete_item(node_item);
					printf("Item deleted successfully...\n");
				}
				save_list();
				break;
			case 5:
			case 6:
				sort_list(choice);
				break;
			case 7:
				save_list();
				exit(0);
			default:
				printf("Enter a valid choice...\n");
		}
	}
}

void add_item(ITEM item)
{	
	NODE *new_item = (NODE*)malloc(sizeof(NODE));
	new_item->item = item;
	new_item->next_item = NULL;
	if (start == NULL)
	{
		start = new_item;
	}
	else
	{
		end->next_item = new_item;
	}
	end = new_item;
}

bool is_empty(NODE *head)
{
	if (head == NULL)
	{
		printf("List is empty...\n");
		return true;
	}
	return false;
}

void display(NODE *head)
{
	NODE *item = head;
	if (is_empty(item))
	{
		return;
	}
	printf("%-20s%-20s%-10s%-10s\n", "ID", "NAME", "QUANTITY", "PRICE");
	underline_text(size_of_item);
	printf("\n");
	while (item != NULL)
	{
		printf("%-20s%-20s%-10d%-10d\n", item->item.id, item->item.name, item->item.stock_quantity, item->item.price);
		item = item->next_item;
	}
	printf("\n");
}

void save_list()
{
	NODE *item = start;
	FILE *fp_items = fopen(FILE_NAME, "wb");
	while (item != NULL)
	{
		fwrite(&item->item, size_of_item, 1, fp_items);
		item = item->next_item;
	}
	fclose(fp_items);
}

void load_data_from_file_to_list()
{
	ITEM item;
	FILE *fp_items = fopen(FILE_NAME, "rb");
	while (fread(&item, size_of_item, 1, fp_items))
	{
		add_item(item);
	}
	fclose(fp_items);
}

void sort_list(int mode)
{
	NODE *temp_start = NULL, *temp_end = NULL;
	NODE *item = start;
	while (item != NULL)
	{
		NODE *new_item = (NODE*)malloc(sizeof(NODE));
		new_item->item = item->item;
		new_item->next_item = NULL;
		if (temp_start == NULL)
		{
			temp_start = new_item;
		}
		else
		{
			temp_end->next_item = new_item;
		}
		temp_end = new_item;
		item = item->next_item;
	}
	NODE *current, *next;
	ITEM temp;
	for (current = temp_start; current->next_item != NULL; current = current->next_item)
	{
		for (next = temp_start; next->next_item != NULL; next = next->next_item)
		{
			if (mode == 5)
        	{
	            if (next->item.price > next->next_item->item.price)
	            {
	                temp = next->item;
	                next->item = next->next_item->item;
	                next->next_item->item = temp;
	            }
	        }
	        if (mode == 6)
	        {
	        	if (strcmp(next->item.name, next->next_item->item.name) > 0)
	            {
	                temp = next->item;
	                next->item = next->next_item->item;
	                next->next_item->item = temp;
	            }
	        }
		}
	}
	display(temp_start);
	NODE *node_item;
	while (temp_start != NULL)
	{
	    node_item = temp_start;
	    temp_start = temp_start->next_item;
	    free(node_item);
	}
}

NODE* get_item(char *id)
{
	NODE *current = start;
	while (current != NULL)
	{
		if (strcmp(current->item.id, id) == 0)
		{
			return current;
		}
		current = current->next_item;
	}
	return NULL;
}

void update_item(NODE *matching_item, int price)
{
	matching_item->item.price = price;
}

void delete_item(NODE *matching_item)
{
	NODE **current = &start;
	while ((*current) != matching_item)
	{
		current = &((*current)->next_item);
	}
	*current = (*current)->next_item;
	if (end == matching_item)
	{
		NODE *item = start;
		while (item->next_item != NULL)
		{
			item = item->next_item;
		}
		end = item;
	}
	free(matching_item);
}