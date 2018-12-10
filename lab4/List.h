#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>

struct List
{
	int value;
	struct List* next;
};

struct List* list_create(int value);
void list_add_front(int value, struct List** list);
void list_add_back(int value, struct List** list);
int list_get(int* value, size_t index, const struct List* list);
void list_free(struct List* list);
int list_length(const struct List* list);
struct List* list_node_at(size_t index, const struct List* list);
int list_sum(const struct List* list);

