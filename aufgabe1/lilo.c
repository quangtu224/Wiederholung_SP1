#include <stdio.h>
#include <stdlib.h>

// TODO: structs, global variables, etc.
struct Node
{
	int value;
	struct Node *next;
};
typedef struct Node Node;
static struct Node *head = NULL;

int insertElement(int value)
{
	// TODO: implement me!
	if (value < 0)
	{
		return -1;
	}
	Node *current = head;
	Node *previous = NULL;
	while (current != NULL)
	{
		if (current->value == value)
		{
			return -1;
		}
		previous = current;
		current = current->next;
	}
	Node *newElement = malloc(sizeof(Node));
	if (newElement == NULL)
	{
		return -1;
	}
	newElement->value = value;
	newElement->next = NULL;
	if (previous == NULL)
	{
		head = newElement;
	}
	else
	{
		previous->next = newElement;
	}
	return value;
}

int removeElement(void)
{
	// TODO: implement me!
	return -1;
}

int main(void)
{
	printf("insert 47: %d\n", insertElement(47));
	printf("insert 11: %d\n", insertElement(11));
	printf("insert 23: %d\n", insertElement(23));
	printf("insert 11: %d\n", insertElement(11));

	printf("remove: %d\n", removeElement());
	printf("remove: %d\n", removeElement());

	// TODO: add more tests

	exit(EXIT_SUCCESS);
}
