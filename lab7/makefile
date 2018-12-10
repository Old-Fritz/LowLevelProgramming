CFLAGS=-c -O -O2 -O3 -Ofast
COMP=gcc
AFLAGS=-felf64
ASM=nasm
.PHONY: all clean install uninstall

all: lab7

lab7: main.o
	gcc -o lab7 main.o sepiaFilter.o sepia.o bmpImage.o mmfile.o

main.o: sepiaFilter.o main.c
	gcc $(CFLAGS) main.c -o main.o

sepiaFilter.o: sepia.o bmpImage.o sepiaFilter.c
	gcc $(CFLAGS) sepiaFilter.c -o sepiaFilter.o

sepia.o: sepia.asm
	nasm -felf64 sepia.asm -o sepia.o

bmpImage.o: mmfile.o bmpImage.c
	gcc $(CFLAGS) bmpImage.c -o bmpImage.o

mmfile.o: mmfile.c
	gcc $(CFLAGS) mmfile.c -o mmfile.o

clean:
	rm -f main.o sepiaFilter.o sepia.o bmpImage.o mmfile.o sepiaOne.o
