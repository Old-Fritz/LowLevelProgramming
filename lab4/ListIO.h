#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "List.h"
#include <stdio.h>

struct List* list_scan();
void list_print(size_t n, const struct List* list);

int save(struct List* list, const char* filename);
int load(struct List** list, const char* filename);

int serialize(struct List* list, const char* filename);
int deserialize(struct List** list, const char* filename);
