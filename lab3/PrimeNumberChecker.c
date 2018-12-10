#include <stdio.h>
#include <math.h>
#include <time.h>

unsigned long fib[] = {39088169,63245986,102334155,165580141,267914296,433494437,701408733,1134903170,1836311903,2971215073};

int is_prime(unsigned long n)
{
	unsigned long del;
    unsigned long limit;
    limit = ceil(sqrt(n))+1;
	if ((n % 2 == 0 && n!=2) || n==1)
		return 0;
    
	for(del = 3;del<limit;del+=2)
	{
		if (n%del == 0)
			return del;
	}
	return 1;
}

int is_primePer(unsigned long n)
{
	unsigned long del;
    
	for(del = 2;del<n;del++)
	{
		if (n%del == 0)
			return 0;
	}
	return 1;
}

int main(void)
{
	size_t i;
    unsigned long sum1 = 0;
    unsigned long sum2 = 0;
    unsigned long tempTime;
    size_t fibSize = 10;
   

	for(i = 0; i< fibSize;i++)
    {
        tempTime = clock();
        is_prime(fib[i]);
        sum1+=clock()-tempTime;
        
        tempTime = clock();
        is_primePer(fib[i]);
        sum2+=clock()-tempTime;
    }
    
        printf("norm method avg time - %lu\nperebor method avg time - %lu\n", sum1/fibSize, sum2/fibSize);
    
	return 0;
}
