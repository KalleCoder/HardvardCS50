#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int number;
	struct node *next;
}
node;

int main(int argc, char *argv[])
{

	// making the nodes
	node *list = NULL;
	for (int i = 1; i < argc; i++)
	{
		int number = atoi(argv[i]); //convert string

		node *n = malloc(sizeof(node));
		if (n == NULL)
		{
			return 1;
		}
		n->number = number;
		n->next = NULL;

		n->next = list; // new nodes points to list
		list = n; // list to point at this node
	}

	//printing the list node values
	node *ptr = list; // pointing at the first node
	while (ptr != NULL)
	{
		printf("%i\n", ptr->number);
		ptr = ptr->next; //getting the next address
	}


	// free memory
	ptr = list;
	while (ptr != NULL)
	{
		node *next = ptr->next; //duplicate
		free(ptr); //now you can use without bugg
		ptr = next; // changing ptr to next value
	}

	return 0;
}
