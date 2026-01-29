 // Program to perform CRUD operations on account of a customer.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"

void remove_new_line(char*);
void clear_buffer();
void open_an_account();
void show_all_accounts();
void close_an_account();
void withdraw_amount();
void deposit_amount();
int find_account(FILE*, char*);

ACCOUNT customer;
int size_of_account = sizeof(customer);
char *FILE_NAME = "Accounts.dat";

void main()
{
	int choice;
	do
	{
		printf("1. Open an Account\n2. Show All Accounts\n3. Close an Account\n4. Withdraw Amount\n5. Deposit Amount\n6. Find Account\n7. Exit\nEnter your Choice: ");
		scanf("%d", &choice);
		clear_buffer();
		switch(choice)
		{
			case 1:
				open_an_account();
				break;
			case 2:
				show_all_accounts();
				break;
			case 3:
				close_an_account();
				break;
			case 4:
				withdraw_amount();
				break;
			case 5:
				deposit_amount();
				break;
			case 6:
				char account_number[ACCOUNT_NUMBER_SIZE];
				int found;
				printf("Enter the Customer's Account Number to Find: ");
				scanf("%s", account_number);
				FILE *fp_accounts = fopen(FILE_NAME, "r");
				found = find_account(fp_accounts, account_number);
				fseek(fp_accounts, -size_of_account, SEEK_CUR);
				if (found == 1)
				{
					fread(&customer, size_of_account, 1, fp_accounts);
					printf("Account was found.\n");
					printf("Customer Details:\nAccount Number: %s\nCustomer Name: %s\nAmount: %d\n", customer.account_number, customer.customer_name, customer.balance_amount);
					if (customer.status == 'a')
					{
						printf("The account is open.\n");
					}
					else
					{
						printf("Account was Closed.\n");
					}
				}
				else
				{
					printf("Account not found.\n");
				}
				fclose(fp_accounts);
				break;
			case 7:
				exit(0);
			default :
				printf("Enter a Valid Choice:\n");
		}
	}while (1);
}

void open_an_account()
{
	printf("Enter Details of Customer: \n");

	printf("Account Number: ");
	fgets(customer.account_number, ACCOUNT_NUMBER_SIZE, stdin);
	remove_new_line(customer.account_number);

	printf("Name of Customer: ");
	fgets(customer.customer_name, NAME_SIZE, stdin);
	remove_new_line(customer.customer_name);

	printf("Customer Amount: ");
	scanf("%d", &customer.balance_amount);
	clear_buffer();

	customer.status = 'a';
	// printf("Status: ");
	// fgets(&customer.status, 2, stdin);
	// clear_buffer();

	FILE *fp_accounts = fopen(FILE_NAME, "a");
	fwrite(&customer, size_of_account, 1, fp_accounts);
	fclose(fp_accounts);
}

void show_all_accounts()
{
	FILE *fp_accounts = fopen(FILE_NAME, "r");
	fseek(fp_accounts, 0, SEEK_END);
    if (ftell(fp_accounts) == 0)
    {
        printf("No accounts found!\n");
    }
    else
    {
    	rewind(fp_accounts);
		printf("All Accounts Details:");
		printf("\n%-20s%-20s%-11s%-5s", "Account Number", "Name", "Amount", "Status\n");
	    printf("---------------------------------------------------------\n");
		while ((fread(&customer, size_of_account, 1, fp_accounts)) == 1)
		{
		 	printf("%-20s%-20s%-11d", customer.account_number, customer.customer_name, customer.balance_amount);
		 	if (customer.status == 'a')
		 	{
		 		printf("%-8s\n", "Active");
		 	}
		 	else
		 	{
		 		printf("%-8s\n","Closed");
		 	}
		}
	}
	fclose(fp_accounts);
}

void close_an_account()
{
	int found = 0;
	char account_number[ACCOUNT_NUMBER_SIZE];
	printf("Enter the Customer's Account Number to Close the Account: ");
	scanf("%s", account_number);
	FILE *fp_accounts = fopen(FILE_NAME, "r+");
	while ((fread(&customer, size_of_account, 1, fp_accounts)) == 1)
	{
		if (strcmp(customer.account_number, account_number) == 0)
		{
			found = 1;
			fseek(fp_accounts, -size_of_account, SEEK_CUR);
			customer.status = 'c';
			fwrite(&customer, size_of_account, 1, fp_accounts);
			break;
		}
	}
	fclose(fp_accounts);
	if (found == 1)
	{
		printf("Account Closed.\n");
	}
	else
	{
		printf("No account found.\n");
	}
}

void withdraw_amount()
{
	int found = 0;
	int withdraw_amount;
	char account_number[ACCOUNT_NUMBER_SIZE];
	printf("Enter the Customer's Account Number to Withdraw the Amount: ");
	scanf("%s", account_number);
	FILE *fp_accounts = fopen(FILE_NAME, "r+");
	while ((fread(&customer, size_of_account, 1, fp_accounts)) == 1)
	{
		if (strcmp(customer.account_number, account_number) == 0)
		{
			found = 1;
			printf("Enter the Amount to Withdraw: ");
			scanf("%d", &withdraw_amount);
			customer.balance_amount -= withdraw_amount;
			fseek(fp_accounts, -size_of_account, SEEK_CUR);
			fwrite(&customer, size_of_account, 1, fp_accounts);
			break;
		}
	}
	fclose(fp_accounts);
	if (found == 1)
	{
		printf("Amount Withdrawed.\n");
	}
	else
	{
		printf("No account found.\n");
	}
}

void deposit_amount()
{
	int withdraw_amount, found = 0;
	char account_number[ACCOUNT_NUMBER_SIZE];
	printf("Enter the Customer's Account Number to Deposit the Amount: ");
	scanf("%s", account_number);
	FILE *fp_accounts = fopen(FILE_NAME, "r+");
	while ((fread(&customer, size_of_account, 1, fp_accounts)) == 1)
	{
		if (strcmp(customer.account_number, account_number) == 0)
		{
			found = 1;
			printf("Enter the Amount to Deposit: ");
			scanf("%d", &withdraw_amount);
			customer.balance_amount += withdraw_amount;
			fseek(fp_accounts, -size_of_account, SEEK_CUR);
			fwrite(&customer, size_of_account, 1, fp_accounts);
			break;
		}
	}
	fclose(fp_accounts);
	if (found == 1)
	{
		printf("Amount Deposited.\n");
	}
	else
	{
		printf("No account found.\n");
	}
}

// int find_account(FILE *fp_accounts, char *account_number)
// {
// 	int found = 0;
// 	ACCOUNT customer;
// 	while ((fread(&customer, sizeof (customer), 1, fp_accounts)) == 1)
// 	{
// 		if (strcmp(customer.account_number, account_number) == 0)
// 		{
// 			fseek(fp_accounts, -size_of_account, SEEK_CUR);
// 			found = 1;
// 			return found;
// 		}
// 	}
// 	return found;
// }