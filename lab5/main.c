#include "bmpImage.h"
#include  <stdlib.h>

#define SIZE 1

void createBigImage()
{
	struct Pixel red[SIZE];
	struct Pixel green[SIZE];
	struct Pixel blue[SIZE];
	struct Pixel* randP;
	int i, j,randN;
	FILE* file;

	srand(12);

	for(i = 0;i<SIZE;i++)
	{
		red[i].r=255;
		green[i].g=255;
		blue[i].b=255;
		red[i].g = red[i].b = green[i].r = green[i].b = blue[i].r = blue[i].g = 0;
	}
	
	file = fopen("bigImages.bmp","w");
	writeHeader(file,SIZE,SIZE);

	

	for(i=0;i<SIZE;i++)
	{
		randN = rand()%3;
		if(randN == 0)
			randP =red;
		else if(randN == 1)
			randP = green;
		else
			randP = blue;

		for(j = 0;j<100;j++)
		{
			fwrite(randP, sizeof(struct Pixel), SIZE, file);
		}
	}
}


int main()
{
	//createBigImage();
	enum FileError result;
	result = rotate("image1.bmp", "image2.bmp");
	if(result==OPEN_ERROR)
		printf("OPEN_ERROR\n");
	result = rotate("image2.bmp", "image3.bmp");
	if(result==OPEN_ERROR)
		printf("OPEN_ERROR\n");
	printf("%d", result);
}