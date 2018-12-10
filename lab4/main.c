#include<limits.h>

#include"List.h"
#include"HOListFunctions.h"
#include"SimpleFunctions.h"
#include"ListIO.h"


int main()
{
	struct List* list, *squared, *iteratedList, *textList, *binList;
	const char* filenameText = "file.txt";
	const char* filenameBinary = "file";

	list = list_scan();
	printf("sum = %d\n", list_sum(list));

	foreach(list, printWithSpaces);
	printf("\n");
	foreach(list, printWithNewLine);

	printf("sum(foldl) = %d\n", foldl(list, 0, sum));
	printf("min = %d\n", foldl(list, INT_MAX, min));
	printf("max = %d\n", foldl(list, INT_MIN, max));

	squared = map(list, square);
    printf("squared:\n");
	foreach (squared, printWithSpaces);
	printf("\n");

    printf("absoluted:\n");
	foreach(map_mut(list, abs), printWithSpaces);
	printf("\n");

    printf("iterated list:\n");
	iteratedList = iterate(10, 1, pow2);
	foreach(iteratedList, printWithSpaces);
	printf("\n");

    printf("from text file:\n");
	save(iteratedList, filenameText);
	if(load(&textList, filenameText))
		foreach(textList, printWithSpaces);
	printf("\n");

    printf("from binary file:\n");
	serialize(iteratedList, filenameBinary);
	if (deserialize(&binList, filenameBinary))
		foreach(binList, printWithSpaces);
	printf("\n");

	list_free(list);
	list_free(squared);
	list_free(iteratedList);
	list_free(textList);
	list_free(binList);


	getchar();
    
    return 0;
}

