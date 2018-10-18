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
boolean doesNameExist(WaitList* waitList, char name[30]);

/////////////////////////////////////////////////////////////////////////////////
// Add to List
// Takein waitlist Struct, name, party size, and isWaithere
void addToList(WaitList* waitList, char name[30], int size, boolean isWaitHere);

/////////////////////////////////////////////////////////////////////////////////
// Update customer status to isWaitHere == True
// Use for the call ahead customer arrival at the restaurant
boolean updateStatus(WaitList* waitList, char name[30]);

/////////////////////////////////////////////////////////////////////////////////
// Retrieve and Remove
// Find the best fit party for the current available table size, then remove
// it from the list
boolean retrieveAndRemove(WaitList* waitList, int tableSize);

/////////////////////////////////////////////////////////////////////////////////
// Count how many group ahead of the given name, return int
int countGroupsAhead(WaitList* waitList, char name[30]);

/////////////////////////////////////////////////////////////////////////////////
// Display the list of client waiting in front of the given name.
void displayGroupSizeAhead(WaitList* waitList, char name[30]);

/////////////////////////////////////////////////////////////////////////////////
// Display all the client in the waiting list
void displayListInformation(WaitList* waitList);

void clearToEoln();
/* Read in until the first Non-White-Space character is Read */
/* The white space characters are:
 *      space, tab \t, newline \n, vertical tab \v, 
 *      form feed \f, and carriage return \r
 */
int getNextNWSChar ();

/* read in the next Positive Integer or error:    */
/* This is based on the Mathematical definition of a Postive Integer */
/*    zero is not counted as a positive number */
int getPosInt ();


/* read in the name until the end of the input */
char *getName();


/* Clear input until next End of Line Character - \n */
void clearToEoln();

/* Print out a list of the commands for this program */
void printCommands();

/* Do Function*/
void doAdd (WaitList* waitList);
void doCallAhead (WaitList* waitList);
void doWaiting (WaitList* waitList);
void doRetrieve (WaitList* waitList);
void doList (WaitList* waitList);
void doDisplay (WaitList* waitList);

