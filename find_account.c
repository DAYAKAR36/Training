 // Function to find account.

#include <stdio.h>
#include <string.h>
#include "account.h"

extern ACCOUNT customer;

int find_account(FILE *fp_accounts, char *account_number)
{
	int found = 0;
	while ((fread(&customer, sizeof(customer), 1, fp_accounts)) == 1)
	{
		if (strcmp(customer.account_number, account_number) == 0)
		{
			found = 1;
			return found;
		}
	}
	return found;
}
