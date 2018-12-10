#include "bmpImage.h"
#include "mmfile.h"

enum FileError openImage(const char* filename, struct Image* image)
{
	uint32_t offset;
	FILE* file;
	enum FileError result = FILE_OK;
	void * ptr;

	file = fopen(filename, "r+");
	if(!file)
		return OPEN_ERROR;

	result = readHeader(file, &image->width, &image->height, &offset, &image->length);
	if(result!=FILE_OK)
		return result;

	// map file in memory
	ptr = openMMFile(file, image->length, 0);
	if(!ptr)
		return MMAP_ERROR;

	image->data = (struct Pixel*)((char*)ptr + offset);
	image->align = (4-image->width*3%4)%4;

	return result;
}

enum FileError createImage(const char* filename, uint32_t width, uint32_t height, struct Image* image)
{
	enum FileError result = FILE_OK;
	FILE* file;
	void * ptr;
	uint32_t length = (width*3%4==0 ? width : width + 4 - width*3%4)*height*3;

	file = fopen(filename, "w+b");
	if(!file)
		return OPEN_ERROR;

	result = writeHeader(file, width, height);
	if(result!=FILE_OK)
		return WRITE_ERROR;

	// expand file size
	if(fseek(file, length+sizeof(struct BmpHeader), SEEK_SET))
		return CREATE_ERROR;
			
	if(!fputs("w", file))
		return CREATE_ERROR;

	if(fseek(file, 0, SEEK_SET))
		return SEEK_ERROR;
	
	// map file in memory
	ptr = openMMFile(file, length + sizeof(struct BmpHeader)+1, 0);
	if(!ptr)
		return MMAP_ERROR;

	image->data = (struct Pixel*)((char*)ptr + sizeof(struct BmpHeader));


	image->width = width;
	image->height = height;
	image->length = length;
	image->align = (4-width*3%4)%4;

	return result;
}

enum FileError closeImage(struct Image image)
{
	if(!closeMMFile(image.data, image.length))
		return CLOSE_ERROR;

	return FILE_OK;
}

enum FileError readHeader(FILE* file, uint32_t* width, uint32_t* height, uint32_t* offset, uint32_t* length)
{
	struct BmpHeader header;
	if(!fread(&header, sizeof(struct BmpHeader), 1, file))
		return READ_ERROR;
	*width = header.biWidth;
	*height = header.biHeight;
	*offset = header.bOffBits;
	*length = header.biSizeImage;


	if(fseek(file, 0, SEEK_SET))
		return SEEK_ERROR;

	return FILE_OK;
}

enum FileError writeHeader(FILE* file, uint32_t width, uint32_t height)
{
	struct BmpHeader header;
	int align = (4-width*3%4)%4;
	header.bfType = 19778;
    header.bfileSize = (width*3+align)*height+sizeof(struct BmpHeader);
    header.bfReserved = 0;
    header.bOffBits = sizeof(struct BmpHeader);
    header.biSize =  40;
    header.biWidth = width;
    header.biHeight = height;
    header.biPlanes = 1;
    header.biBitCount = 24;
    header.biCompression = 0;
    header.biSizeImage = header.bfileSize-sizeof(struct BmpHeader);
    header.biXPelsPerMeter = 2795;
    header.biYPelsPerMeter = 2795;
    header.biClrUsed = 0;
    header.biClrImportant = 0;

    if(!fwrite(&header, sizeof(struct BmpHeader), 1, file))
		return WRITE_ERROR;

	return FILE_OK;
}


enum FileError rotate(const char* sourceFilename, const char* destFilename)
{
	struct Image source, dest;
	enum FileError result = FILE_OK;
	uint32_t i, j, sourceInd, destInd;;

	result = openImage(sourceFilename, &source);
	if(result!=FILE_OK)
		return result;

	result = createImage(destFilename, source.height,source.width,&dest);
	if(result!=FILE_OK)
		return result;

	for(i = 0;i<source.height;i++)
	{
		for(j = 0;j<source.width;j++)
		{
			sourceInd = (source.width*3+source.align)*i+j*3;
			destInd = (dest.width*3+dest.align)*(source.width-j-1)+i*3;;

			*(struct Pixel*)((char*)dest.data+destInd) = *(struct Pixel*)((char*)source.data+sourceInd);
		}
	}

	result = closeImage(source);
	if(result!=FILE_OK)
		return result;

	result = closeImage(dest);
	if(result!=FILE_OK)
		return result;

	return result;
}
