#include "bmpImage.h"

#ifndef SEPIA_FILTER
#define SEPIA_FILTER

void sepiaFilterSSE(struct Image source,struct Image dest);
void sepiaFilterC(struct Image source,struct Image dest);

#endif