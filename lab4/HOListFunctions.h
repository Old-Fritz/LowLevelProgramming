#pragma once
#include "List.h"

void foreach(const struct List* list, void (*f)(int x));
struct List* map(const struct List* list, int (*f)(int x));
struct List* map_mut(struct List* list, int (*f)(int x));
int foldl(const struct List* list, int value, int (*f)(int x, int a));
struct List* iterate(int length, int value, int (*f)(int x));