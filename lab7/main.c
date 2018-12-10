#include "sepiaFilter.h"
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

#define REPEAT_TIMES 100

int main()
{
	struct rusage r;
	struct timeval start;
	struct timeval end;
	int i;
	uint64_t sumTime = 0;


	enum FileError result = FILE_OK;
	struct Image source, destSSE, destC;
	// open images
	result = openImage("image1.bmp", &source);
	if(result!=FILE_OK)
		printf("error %d\n", result);

	result = createImage("imageSSE.bmp", source.width, source.height, &destSSE);
	if(result!=FILE_OK)
		printf("error %d\n", result);

	result = createImage("imageC.bmp", source.width, source.height, &destC);
	if(result!=FILE_OK)
		printf("error %d\n", result);


	getrusage(RUSAGE_SELF, &r );
    start = r.ru_utime;

    getrusage(RUSAGE_SELF, &r );
    end = r.ru_utime;


    for(i = 0;i<REPEAT_TIMES;i++)
    {
	   	getrusage(RUSAGE_SELF, &r );
	    start = r.ru_utime;

	    sepiaFilterC(source, destC);

	    getrusage(RUSAGE_SELF, &r );
	    end = r.ru_utime;

	    sumTime+=((end.tv_sec - start.tv_sec) * 1000000L) +
        end.tv_usec - start.tv_usec;
    }

    printf( "Avg C sepia in microseconds: %ld\n", sumTime/REPEAT_TIMES );

	sumTime = 0;
    for(i = 0;i<REPEAT_TIMES;i++)
    {
    	getrusage(RUSAGE_SELF, &r );
	    start = r.ru_utime;

	    sepiaFilterSSE(source, destSSE);

	    getrusage(RUSAGE_SELF, &r );
	    end = r.ru_utime;

	    sumTime+=((end.tv_sec - start.tv_sec) * 1000000L) +
        end.tv_usec - start.tv_usec;
    }

    printf( "Avg SSE sepia in microseconds: %ld\n", sumTime/REPEAT_TIMES );


    return 0;
}