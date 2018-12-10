#include "ListIO.h"


struct List* list_scan()
{
	size_t size, i;
	int value;
	struct List* list, *listNext;

	scanf("%lu", &size);
	if (size == 0)
		return NULL;
	scanf("%d", &value);

	list = list_create(value);
	listNext = list;

	for (i = 1; i<size;i++)
	{
		scanf("%d", &value);
		listNext->next = list_create(value);
		listNext = listNext->next;
	}

	return list;
}

void list_print(size_t n, const struct List* list)
{
	int value;
	int result;

	result = list_get(&value, n, list);
	if (result)
		printf("%d", value);
	else
		printf("list is too short");
}



int save(struct List* list, const char* filename)
{
	FILE* file;

	file = fopen(filename, "w");
	if (!file)
		return 0;

	do
	{
		fprintf(file, "%d\n", list->value);
	} while ((list = list->next));

	fclose(file);

	return 1;
}

int load(struct List** list, const char* filename)
{
	FILE* file;
	int value;
	struct List* listNext;

	file = fopen(filename, "r");
	if (!file)
		return 0;

	fscanf(file, "%d\n", &value);
	*list = list_create(value);
	listNext = *list;

	while(fscanf(file, "%d\n", &value) != EOF)
	{
		listNext->next = list_create(value);
		listNext = listNext->next;
	}

	fclose(file);

	return 1;
}



int serialize(struct List* list, const char* filename)
{
	FILE* file;

	file = fopen(filename, "wb");
	if (!file)
		return 0;

	do
	{
		fwrite(&(list->value), sizeof(int), 1, file);
	} while ((list = list->next));

	fclose(file);

	return 1;
}

int deserialize(struct List** list, const char* filename)
{
	FILE* file;
	int value;
	struct List* listNext;

	file = fopen(filename, "rb");
	if (!file)
		return 0;

	fread(&value,sizeof(int),1, file);
	*list = list_create(value);
	listNext = *list;

	while (fread(&value, sizeof(int), 1, file) == 1)
	{
		listNext->next = list_create(value);
		listNext = listNext->next;
	}

	fclose(file);

	return 1;
}
