 // Read and show account details of one customer.

#include <stdio.h>

#define size 20

struct customer_account_details
{
	char account_number[size];
	char customer_name[size];
	int deposit_amount;
};

void main()
{
	struct customer customer1;
	printf("Enter account details of customer: \n");
	printf("Enter the name of customer: ");
	fgets(customer1.account_number, size, stdin);
	printf("Enter the account number of: ");
	fgets(customer1.customer_name, size, stdin);
	printf("Enter deposit amount: ");
	scanf("%d", &deposit_amount);
	printf("Account details of customer: \n");
	printf("Name of customer: %s", customer1.customer_name);
	printf("Account number of customer: %s", customer1.account_number);
	printf("Deposit amount of customer: %s", customer1.deposit_amount);
}