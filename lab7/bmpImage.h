#include <stdint.h>
#include <stdio.h>

struct Pixel
{
	uint8_t b,g,r;
};

struct Image{
	uint32_t width, height;
	uint32_t length;
	uint32_t align;
	struct Pixel* data;
};

enum FileError{
	FILE_OK = 0,
	OPEN_ERROR,
	MMAP_ERROR,
	CLOSE_ERROR,
	WRITE_ERROR,
	CREATE_ERROR,
	SEEK_ERROR,
	READ_ERROR
};

#pragma pack(push,2)
struct BmpHeader {
        uint16_t bfType;
        uint32_t  bfileSize;
        uint32_t bfReserved;
        uint32_t bOffBits;
        uint32_t biSize;
        uint32_t biWidth;
        uint32_t  biHeight;
        uint16_t  biPlanes;
        uint16_t biBitCount;
        uint32_t biCompression;
        uint32_t biSizeImage;
        uint32_t biXPelsPerMeter;
        uint32_t biYPelsPerMeter;
        uint32_t biClrUsed;
        uint32_t  biClrImportant;
};
#pragma pack(pop)

enum FileError openImage(const char* filename, struct Image* image);

enum FileError createImage(const char* filename, uint32_t width, uint32_t height, struct Image* image);

enum FileError closeImage(struct Image image);

enum FileError readHeader(FILE* file, uint32_t* width, uint32_t* height, uint32_t* offset, uint32_t* length);

enum FileError writeHeader(FILE* file, uint32_t width, uint32_t height);


enum FileError rotate(const char* sourceFilename, const char* destFilename);