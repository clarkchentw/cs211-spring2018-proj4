#include "header.h"

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
	int groupAhead = countGroupsAhead(waitList, name);
	if (NULL == name){
                printf ("Error: List command requires a name to be given\n");
                printf ("List command is of form: l <name>\n");
                printf ("  where: <name> is the name of the group to inquire about\n");
                return;
        }

	if (groupAhead == -1){
		// Group doesn't exist
		return;
	}
	if (NULL == name){
		printf ("Error: List command requires a name to be given\n");
		printf ("List command is of form: l <name>\n");
		printf ("  where: <name> is the name of the group to inquire about\n");
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
