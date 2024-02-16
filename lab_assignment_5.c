#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{
	// Declare num_nodes, an int variable to store the number of nodes in the linked list.
	int num_nodes = 0;

	// Traverse the linked list.
	node* traverse = head;
	while (traverse != NULL) {
		// Increment num_nodes to count the number of nodes as the list is traversed, then move to the next node.
		num_nodes++;
		traverse = traverse->next;
	}

	// Return the number of nodes in the linked list, that is the length of the linked list.
	return num_nodes;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{
	// Declare a pointer to char
	char* strng = NULL;
	
	// Alloc mem for the string, using ( length(head) + 1), to account for the null char.
	int len = length(head) + 1;
	strng = malloc( len * sizeof(char) );
	
	// Traverse the list
	node* traverse = head;
	// Declare an int to hold the current index position of the char array during the following traversal.
	int arr_num = 0;

	// The while loop will traverse the list...
	while (traverse != NULL) {
		// Input the current node's stored letter into its corresponding index position of the char array...
		strng[arr_num] = traverse->letter;
		// Traverse to the next node...
		traverse = traverse->next;
		// Incrementing the index number for the next iteration.
		arr_num ++;
	}

	// Having traversed to the last node of the list, a null char is entered to denote the end of the string.
	strng[arr_num] = '\0';

	// Return the parsed string
	return strng;
}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
	// Declare tmp node to alias *pHead for traversal
	node* tmp = *pHead;
	
	// If the list is empty...
	if (*pHead == NULL) {
		// Create the first node...
		*pHead = malloc(sizeof(node));
		// Insert the first char into that node...
		(*pHead)->letter = c;
		// Mark this first node as the end of the list by assigning NULL to its next pointer.
		(*pHead)->next = NULL;
	}

	// Else, traverse the list for the last node, create the next node, and initialize that node with the char value.
	else {
		// Traverse the entire list to the end.
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		
		// Create a new node and assign it to the current node's next pointer.
		tmp->next = malloc(sizeof(node));
		// Input the letter for this new node.
		tmp->next->letter = c;
		// Mark this new node as the new end of the list by assigning NULL to its next pointer.
		tmp->next->next = NULL;
	}
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	// Traverse the list
	node* traverse = *pHead;

	// While traversing the list, free each node
	while (traverse != NULL) {
		// Alias the next node as node* nxt.
		node* nxt = traverse->next;
		// Free the current node.
		free(traverse);
		// Traverse to the next node in the list.
		traverse = nxt;
	}
	
	// Re-assign head pointer value to NULL to mark the list as empty.
	*pHead = NULL;
}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}