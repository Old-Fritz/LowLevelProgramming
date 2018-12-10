CFLAGS=-c -pedantic-errors -Wall 
COMP=gcc
AFLAGS=-felf64
ASM=nasm
.PHONY: all clean install uninstall

all: lab7

lab7: main.o
	gcc -o lab7 main.o sepiaFilter.o sepia.o bmpImage.o mmfile.o

main.o: sepiaFilter.o main.c
	gcc -c main.c -o main.o



sepiaFilter.o: sepia.o bmpImage.o sepiaFilter.c
	gcc -c sepiaFilter.c -o sepiaFilter.o

sepia.o: sepia.asm
	nasm -felf64 sepia.asm -o sepia.o



bmpImage.o: mmfile.o bmpImage.c
	gcc -c bmpImage.c -o bmpImage.o

mmfile.o: mmfile.c
	gcc -c mmfile.c -o mmfile.o

clean:
	rm -f main.o sepiaFilter.o sepia.o bmpImage.o mmfile.o
