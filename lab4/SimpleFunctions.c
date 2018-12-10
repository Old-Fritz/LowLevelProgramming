#include"SimpleFunctions.h"
#include <stdio.h>

void printWithSpaces(int x)
{
	printf("%d ", x);
}

void printWithNewLine(int x)
{
	printf("%d\n", x);
}

int square(int x)
{
	return x*x;
}

int pow2(int x)
{
	return x * 2;
}

int min(int x, int a)
{
	if (x < a)
		return x;
	return a;
}

int max(int x, int a)
{
	if (x > a)
		return x;
	return a;
}

int sum(int x, int a)
{
	return a + x;
}
