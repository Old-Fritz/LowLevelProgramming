CFLAGS=-c -pedantic-errors -Wall 
COMP=gcc
.PHONY: all clean install uninstall

all: lab5

lab5: main.o
	$(COMP) -o lab5 main.o bmpImage.o mmfile.o -lm

main.o: bmpImage.o main.c
	$(COMP) $(CFLAGS) main.c -lm

bmpImage.o: mmfile.o bmpImage.c
	$(COMP) $(CFLAGS) bmpImage.c -lm

mmfile.o: mmfile.c
	$(COMP) $(CFLAGS) mmfile.c -lm

clean:
	rm -f main.o bmpImage.o mmfile.o
