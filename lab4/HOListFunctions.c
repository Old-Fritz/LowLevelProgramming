#include "HOListFunctions.h"

void foreach(const struct List* list, void(*f)(int x))
{
	do
	{
		f(list->value);
	} while ((list = list->next));

}

struct List* map(const struct List* list, int(*f)(int x))
{
	struct List* newListNext;
	struct List* newList = list_create(f(list->value));
	newListNext = newList;
	while ((list = list->next))
	{
		newListNext->next = list_create(f(list->value));
		newListNext = newListNext->next;
	}

	return newList;
}

struct List* map_mut(struct List* list, int(*f)(int x))
{
	struct List* listNext = list;
	do
	{
		listNext->value = f(listNext->value);
	} while ((listNext = listNext->next));

	return list;
}
int foldl(const struct List* list, int value, int(*f)(int x, int a))
{
	do
	{
		value = f(list->value, value);
	} while ((list = list->next));

	return value;
}

struct List* iterate(int length, int value, int(*f)(int x))
{
	struct List* newList, *newListNext;
	int i;

	newList = list_create(value);
	newListNext = newList;
	for(i = 1;i<length;i++)
	{
		value = f(value);
		newListNext->next = list_create(value);
		newListNext = newListNext->next;
	}

	return  newList;
}
