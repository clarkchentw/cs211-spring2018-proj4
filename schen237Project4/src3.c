#include "header.h"

/////////////////////////////////////////////////////////////////////////////////
// Add to List
// Takein waitlist Struct, name, party size, and isWaithere
void addToList(WaitList* waitList, char name[30], int size, boolean isWaitHere){
	if (waitList->hd == NULL){
		waitList->hd = (Customer*) malloc(sizeof(Customer));
		strcpy(waitList->hd->name, name);
		waitList->hd->size = size;
		waitList->hd->isWaitHere = isWaitHere;
	}
	else{
		if (doesNameExist(waitList, name) == TRUE){
			printf("The name \"%s\"  already exists in the wait list\n", name);
			return;
		}
		Customer* tmp = (Customer*) malloc(sizeof(Customer));
		strcpy(tmp->name, name);
		tmp->size = size;
		tmp->isWaitHere = isWaitHere;
		Customer* customer = waitList->hd;
		while (customer != NULL){
			if (customer->next == NULL){
				customer->next = tmp;
				break;
			}
			else{
				customer = customer->next;
			}
		}
	}

}

/////////////////////////////////////////////////////////////////////////////////
// Check if name exist in the list
// Return boolean
boolean doesNameExist(WaitList* waitList, char name[30]){
	Customer* customer = waitList->hd;
	while (customer != NULL){
		if (strcmp(customer->name, name) == 0){
			return TRUE;
		}
		else{
			customer = customer->next;
		}
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////
// Update customer status to isWaitHere == True
// Use for the call ahead customer arrival at the restaurant
boolean updateStatus(WaitList* waitList, char name[30]){
	if (waitList->hd == NULL || doesNameExist(waitList, name) == FALSE){
		printf("The name \"%s\"  doesn't exists in the wait list\n", name);
		return FALSE;
	}
	else{
		// Searching for Customer
		Customer* customer = waitList->hd;
		while (customer != NULL){
			if (strcmp(customer->name, name) == 0){
				// When Found
				if (customer->isWaitHere == FALSE){
					customer->isWaitHere = TRUE;
					return TRUE;
				}
				else{
					printf("Customer \"%s\" already here in the restaurant.\n", name);
					return FALSE;
				}
			}
			else{
				customer = customer->next;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////
// Retrieve and Remove
// Find the best fit party for the current available table size, then remove
// it from the list
boolean retrieveAndRemove(WaitList* waitList, int tableSize){
	int i; // for use of for loop
	Customer* customer = waitList->hd;
	if (customer == NULL){
		printf("We do not have any customer waiting.\n");
		return FALSE;
	}
	
	for (i = tableSize; i > 0; i--){
		customer = waitList->hd;
		if (customer->isWaitHere && customer->size == i){
			Customer* tmp = customer;
			waitList->hd = waitList->hd->next;
			printf("Customer \"%s\" with party of %d is ready to be seat!\n", customer->name, customer->size);
			free(tmp);
			return TRUE;
		}
		while (customer != NULL){
			if (customer->next != NULL && customer->next->isWaitHere == TRUE && customer->next->size == i){
				Customer* tmp = customer->next;
				customer->next = customer->next->next;
				printf("Customer \"%s\" with party of %d is ready to be seat!\n", tmp->name, tmp->size);
				free(tmp);
				return TRUE;
			}
			else{
				customer = customer->next;
			}
		}
	}
	
	printf("Non of the customer is qualify for this table size.\n");
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////
// Count how many group ahead of the given name, return int
int countGroupsAhead(WaitList* waitList, char name[30]){
	Customer* customer = waitList->hd;
	int customerAhead = 0;
	while (customer != NULL){
		if (strcmp(customer->name, name) == 0){
			return customerAhead;
		}
		else{
			customerAhead++;
			customer = customer->next;
		}
	}
	printf("The name \"%s\"  doesn't exists in the wait list\n", name);
	return -1;
}

/////////////////////////////////////////////////////////////////////////////////
// Display the list of client waiting in front of the given name.
void displayGroupSizeAhead(WaitList* waitList, char name[30]){
	Customer* customer = waitList->hd;
	int customerNum = 1;
	while (customer != NULL){
		if (strcmp(customer->name, name) == 0){
			return;
		}
		else{
			printf("Group #%d: Party of %d\n", customerNum, customer->size);
			customerNum++;
			customer = customer->next;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////
// Display all the client in the waiting list
void displayListInformation(WaitList* waitList){
	Customer* customer = waitList->hd;
	int customerNum = 1;
	while (customer != NULL){
		if (customer->isWaitHere){
			printf("Group #%d: %s Party of %d is waiting here.\n", customerNum, customer->name, customer->size);
		}
		else{
			printf("Group #%d: %s Party of %d has called ahead.\n", customerNum, customer->name, customer->size);
		}
			
			customerNum++;
			customer = customer->next;
	}
}