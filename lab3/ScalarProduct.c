#include <stdio.h>

 int g_array1[] = { 1,2,3,4,5,6,7,8,9, 0};
 int g_array2[] = { 1,4,8,8,2,2,8,4,2 };

int scalarProduct(const int* array1, const int* array2, size_t size)
{
	int result = 0;
	size_t i;
	for(i=0;i<size;i++)
	{
		result += array1[i] * array2[i];
	}
	return result;
}

int main(void)
{
	int product = 0;
	product = scalarProduct(g_array1, g_array2, sizeof(g_array1));
	printf("%d", product);

	return 0;
}
