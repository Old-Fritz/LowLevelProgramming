#include "sepiaFilter.h"

void setSepiaRegisters(float[static 4], float [static 4], float[static 4]);
void setRGBRegistersAndCalc(float[static 4], float [static 4], float[static 4], float[static 4]);

static unsigned char sat( uint64_t x) {
    if (x < 256) return x; return 255;
}

static void sepiaOne( struct Pixel* const sourcePixel, struct Pixel* const destPixel ) 
{
    static const float c[3][3] =  {
    { .393f, .769f, .189f },
    { .349f, .686f, .168f },
    { .272f, .543f, .131f } };
	struct Pixel const old = *sourcePixel;
	destPixel->r = sat(old.r * c[0][0] + old.g * c[0][1] + old.b * c[0][2]);
	destPixel->g = sat(old.r * c[1][0] + old.g * c[1][1] + old.b * c[1][2]);
	destPixel->b = sat(old.r * c[2][0] + old.g * c[2][1] + old.b * c[2][2]);
}
  

static void calcPack(float rgbData[3][12], int ind, float* out)
{
    static const float c[3][12] =  {
    { .393f, .349f, .272f,.393f, .349f, .272f,.393f, .349f, .272f,.393f, .349f, .272f},
    { .769f, .686f, .543f,.769f, .686f, .543f,.769f, .686f, .543f,.769f, .686f, .543f},
    { .189f, .168f, .131f,.189f, .168f, .131f,.189f, .168f, .131f,.189f, .168f, .131f}};

    setSepiaRegisters(c[0]+ind,c[1]+ind,c[2]+ind);
    setRGBRegistersAndCalc(rgbData[0] +ind,rgbData[1] +ind,rgbData[2] +ind, out);
}

static void calculateChank(struct Pixel** pixelChankSource, struct Pixel** pixelChankDest)
{
	float pixels[3][4];
	float result[12];
	int i, j;


	for(i = 0;i<4;i++)
	{
		for(j = 0;j<3;j++)
		{
			pixels[0][i*3+j] = pixelChankSource[i]->r;
			pixels[1][i*3+j] = pixelChankSource[i]->g;
			pixels[2][i*3+j] = pixelChankSource[i]->b;
		}
	}
	
	for(i = 0;i<12;i+=4)
		calcPack(pixels, i, result+i);

	
	for(i = 0;i<4;i++)
	{
		pixelChankDest[i]->r = sat(result[i*3]);
		pixelChankDest[i]->g = sat(result[i*3+1]);
		pixelChankDest[i]->b = sat(result[i*3+2]);
	}

	
}

void sepiaFilterSSE(struct Image source,struct Image dest)
{
	struct Pixel *sourceChank[4], *destChank[4];
	int i,j, pixelInd, chankInd=0;

	for(i = 0;i<source.height;i++)
	{
		for(j = 0;j<source.width;j++)
		{
			pixelInd =(source.width*3+source.align)*i+j*3;
			sourceChank[chankInd] = (struct Pixel*)((uint8_t*)source.data+pixelInd);
			destChank[chankInd] = (struct Pixel*)((uint8_t*)dest.data+pixelInd);
			chankInd++;
			if(chankInd==4)
			{
				chankInd = 0;
				calculateChank(sourceChank, destChank);
			}
		}
	}
	for(i = chankInd;i>=0;i--)
		sepiaOne(sourceChank[i], destChank[i]);
}


void sepiaFilterC(struct Image source,struct Image dest)
{
	int i,j, pixelInd;

	for(i = 0;i<source.height;i++)
	{
		for(j = 0;j<source.width;j++)
		{
			pixelInd =(source.width*3+source.align)*i+j*3;
			sepiaOne((struct Pixel*)((uint8_t*)source.data+pixelInd),
			 (struct Pixel*)((uint8_t*)dest.data+pixelInd));
		}
	}
}