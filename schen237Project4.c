/*
Program: Project 4 for CS211
Name: Clark Chen
NetID: schen237
Class: CS211
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define boolean type
typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;

/////////////////////////////////////////////////////////////////////////////////
// Struct for each customer
typedef struct CustomerStruct
{
	struct CustomerStruct* next;
	char name[30];
	int size;
	boolean isWaitHere;
} Customer;


/////////////////////////////////////////////////////////////////////////////////
// Struct for waitList contain a pointer to the head of the customer linked list
typedef struct WaitListStruct
{
	Customer* hd;
} WaitList;

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


/* forward definition of functions */
void clearToEoln();

/* Read in until the first Non-White-Space character is Read */
/* The white space characters are:
 *      space, tab \t, newline \n, vertical tab \v, 
 *      form feed \f, and carriage return \r
 */ 
int getNextNWSChar ()
{
	int ch;

	ch = getc(stdin);
	if (ch == EOF || ch == '\n')
		return ch;
	while (isspace (ch)){
		ch = getc(stdin);
		if (ch == EOF || ch == '\n')
		return ch;
	}
	return ch;
}

/* read in the next Positive Integer or error:    */
/* This is based on the Mathematical definition of a Postive Integer */
/*    zero is not counted as a positive number */ 
int getPosInt (){
	int value = 0;

	/* clear white space characters */
	int ch;
	ch = getc(stdin);
	while (!isdigit(ch)){
		if ('\n' == ch)  /* error \n ==> no integer given */
			return 0;
		if (!isspace(ch)) /* error non white space ==> integer not given next */
		{
			clearToEoln();
			return 0;
		}
		ch = getc(stdin);
	}

	value = ch - '0';
	ch = getc(stdin);
	while (isdigit(ch)){
		value = value * 10 + ch - '0';
		ch = getc(stdin);
	}

	ungetc (ch, stdin);  /* put the last read character back in input stream */

	/* Integer value of 0 is an error in this program */
	if (0 == value)
		clearToEoln();

	return value;
}

/* read in the name until the end of the input */
char *getName()
{
	/* skip over the white space characters */
	int ch;
	ch = getc(stdin);
	while (isspace(ch)){
		if ('\n' == ch)  /* error \n ==> no integer given */
			return NULL;
		ch = getc(stdin);
	}

	char *word;
	int size;
	size = 10;
	word = (char *) malloc (sizeof(char) * size);
	
	// read in character-by-character until the newline is encountered
	int count = 0;

	while (ch != '\n'){
		if (count+1 >= size){
			// to grow an array to make it "dynamically sized" using malloc
			char* temp;
		int i;
		size = size * 2;
		temp = (char *) malloc (sizeof(char) * size);

		// printf ("Growing array from size %d to size %d\n", count, size);
		// copy the characters to the new array
		for (i = 0 ; i < count ; i++)
			temp[i] = word[i];

		free (word);
		word = temp;
	}

	word[count] = ch;
	count++;
	word[count] = '\0';

	// read next character
	ch = getc(stdin);
	}

	if (count > 30){
		count = 30;
		word[count] = '\0';
	}
 
	/* clear ending white space characters */
	while (isspace (word[count-1])){
		count--;
		word[count] = '\0';
	}

	return word;
}

/* Clear input until next End of Line Character - \n */
void clearToEoln(){
	int ch;

	do {
		ch = getc(stdin);
	}
	while ((ch != '\n') && (ch != EOF));
}

/* Print out a list of the commands for this program */
void printCommands(){
	printf ("The commands for this program are:\n\n");
	printf ("q - to quit the program\n");
	printf ("? - to list the accepted commands\n");
	printf ("a <size> <name> - to add a group to the wait list\n");
	printf ("c <size> <name> - to add a call-ahead group to the wait list\n");
	printf ("w <name> - to specify a call-ahead group is now waiting in the restaurant\n");
	printf ("r <table-size> - to retrieve the first waiting group that can fit at the available table size\n");
	printf ("l <name> - list how many groups are ahead of the named group\n");
	printf ("d - display the wait list information\n");

	/* clear input to End of Line */
	clearToEoln();
}

void doAdd (WaitList* waitList){
	/* get group size from input */
	int size = getPosInt();
	if (size < 1)
	{
		printf ("Error: Add command requires an integer value of at least 1\n");
		printf ("Add command is of form: a <size> <name>\n");
		printf ("  where: <size> is the size of the group making the reservation\n");
		printf ("         <name> is the name of the group making the reservation\n");
		return;
	}

	/* get group name from input */
	char *name = getName();
	if (NULL == name){
		printf ("Error: Add command requires a name to be given\n");
		printf ("Add command is of form: a <size> <name>\n");
		printf ("  where: <size> is the size of the group making the reservation\n");
		printf ("         <name> is the name of the group making the reservation\n");
		return;
	}

	printf ("Adding In-restaurant group \"%s\" of size %d\n", name, size);

	// add code to perform this operation here
	addToList(waitList, name, size, TRUE);
}


void doCallAhead (WaitList* waitList){
	/* get group size from input */
	int size = getPosInt();
	if (size < 1){
		printf ("Error: Call-ahead command requires an integer value of at least 1\n");
		printf ("Call-ahead command is of form: c <size> <name>\n");
		printf ("  where: <size> is the size of the group making the reservation\n");
		printf ("         <name> is the name of the group making the reservation\n");
		return;
	}

	/* get group name from input */
	char *name = getName();
	if (NULL == name){
		printf ("Error: Call-ahead command requires a name to be given\n");
		printf ("Call-ahead command is of form: c <size> <name>\n");
		printf ("  where: <size> is the size of the group making the reservation\n");
		printf ("         <name> is the name of the group making the reservation\n");
		return;
	}

	printf ("Adding Call-ahead group \"%s\" of size %d\n", name, size);

	// add code to perform this operation here
	addToList(waitList, name, size, FALSE);
}

void doWaiting (WaitList* waitList){
	/* get group name from input */
	char *name = getName();
	if (NULL == name)
	{
		printf ("Error: Waiting command requires a name to be given\n");
		printf ("Waiting command is of form: w <name>\n");
		printf ("  where: <name> is the name of the group that is now waiting\n");
		return;
	}

	printf ("Call-ahead group \"%s\" is now waiting in the restaurant\n", name);

	// add code to perform this operation here
	updateStatus(waitList, name);
}

void doRetrieve (WaitList* waitList)
{
	/* get table size from input */
	int size = getPosInt();
	if (size < 1){
		printf ("Error: Retrieve command requires an integer value of at least 1\n");
		printf ("Retrieve command is of form: r <size>\n");
		printf ("  where: <size> is the size of the group making the reservation\n");
		return;
	}
	clearToEoln();
	printf ("Retrieve (and remove) the first group that can fit at a table of size %d\n", size);

	// add code to perform this operation here
	retrieveAndRemove(waitList, size);
}

void doList (WaitList* waitList)
{
	/* get group name from input */
	char *name = getName();
	if (NULL == name){
                printf ("Error: List command requires a name to be given\n");
                printf ("List command is of form: l <name>\n");
                printf ("  where: <name> is the name of the group to inquire about\n");
                return;
        }

	int groupAhead = countGroupsAhead(waitList, name);
	if (groupAhead == -1){
		// Group doesn't exist
		return;
	}

	printf ("Group \"%s\" is behind %d groups\n", name, groupAhead);

	// add code to perform this operation here
	displayGroupSizeAhead(waitList, name);
}
 
void doDisplay (WaitList* waitList){
	clearToEoln();
	printf ("Display information about all groups\n");

	// add code to perform this operation here
	displayListInformation(waitList);
}


int main (int argc, char **argv){
	WaitList* waitList = (WaitList*) malloc(sizeof(WaitList));
	char *input;
	int ch;
	
	printf ("Starting Restaurant Wait List Program\n\n");
	printf ("Enter command: ");
	
	while ((ch = getNextNWSChar ()) != EOF){
	/* check for the various commands */
    if ('q' == ch){
		printf ("Quitting Program\n");
		return (0);
	}
    else if ('?' == ch){
		printCommands();
	}
    else if('a' == ch){
       doAdd(waitList);
	} 
	else if('c' == ch){
		doCallAhead(waitList);
	} 
	else if('w' == ch){
		doWaiting(waitList);
	} 
	else if('r' == ch){
		doRetrieve(waitList);
	} 
	else if('l' == ch){
		doList(waitList);
	} 
	else if('d' == ch){
		doDisplay(waitList);
	}
	else if('\n' == ch){
		/* nothing entered on input line     *
		* do nothing, but don't give error  */
	} 
	else{
		printf ("%c - in not a valid command\n", ch);
		printf ("For a list of valid commands, type ?\n");
		clearToEoln();
	}

		printf ("\nEnter command: ");
	}

	printf ("Quiting Program - EOF reached\n");
	return 1;
}
