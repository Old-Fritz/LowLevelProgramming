#include"List.h"


struct List* list_create(int value)
{
	struct List* newList = (struct List*)malloc(sizeof(struct List));
	newList->next = NULL;
	newList->value = value;

	return newList;
}

void list_add_front(int value, struct List** list)
{
	struct List* newList = list_create(value);
	newList->next = *list;
	*list = newList;
}

void list_add_back(int value, struct List** list)
{
	struct List* newList = *list;
	while (newList->next)
		newList = newList->next;
	newList->next = list_create(value);
}

int list_get(int* value, size_t index, const struct List* list)
{
	struct List* node = list_node_at(index, list);
	if (node)
	{
		*value = node->value;
		return 1;
	}
	return 0;
}

void list_free(struct List* list)
{
	struct List* nextNode;
	while((nextNode = list))
	{
		list = list->next;
		free(nextNode);
	}

}

int list_length(const struct List* list)
{
	int n = 1;
	while((list = list->next))
		n++;

	return n;
}

struct List* list_node_at(size_t index, const struct List* list)
{
	size_t i;
	for(i = 0;i<index;i++)
	{
		list = list->next;
		if (!list)
			return NULL;
	}

	return (struct List*)list;
}

int list_sum(const struct List* list)
{
	int sum = list->value;
	while ((list = list->next))
		sum += list->value;

	return sum;
}



