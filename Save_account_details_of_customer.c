 // Read and save account details of one customer.

#include <stdio.h>
#include "mytools.h"

#define size 15
#define file_name "Account_details_of_customer.txt"

struct account_details_of_customer
{
	char account_number[size];
	char customer_name[size];
	int balance_amount;
};

void main()
{
	struct account_details_of_customer customer1;
	printf("Enter account details of customer: \n");
	printf("Enter the account number of customer: ");
	fgets(customer1.account_number, size, stdin);
	remove_new_line(customer1.account_number);
	printf("Enter the name of customer: ");
	fgets(customer1.customer_name, size, stdin);
	remove_new_line(customer1.customer_name);
	printf("Enter customer amount: ");
	scanf("%d", &customer1.balance_amount);

	FILE *customer = fopen(file_name, "a");
	s
	// fprintf(customer, "%s", customer1.account_number);
	// fprintf(customer, "%s", customer1.customer_name);
	// fprintf(customer, "%d", customer1.balance_amount);
	fwrite(customer1.account_number, size, 1, customer);
	fwrite(customer1.customer_name, size, 1, customer);
	fwrite(&customer1.balance_amount, sizeof(int), 1, customer);
	fclose(customer);
}