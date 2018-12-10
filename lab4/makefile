CFLAGS=-c -ansi -pedantic-errors -Wall -Werror 
COMP=gcc
.PHONY: all clean install uninstall

all: lab4

lab4: main.o
	$(COMP) -o lab4 main.o SimpleFunctions.o List.o ListIO.o HOListFunctions.o

main.o: SimpleFunctions.o ListIO.o HOListFunctions.o main.c
	$(COMP) $(CFLAGS) main.c

ListIO.o: List.o ListIO.c
	$(COMP) $(CFLAGS) ListIO.c

HOListFunctions.o: List.o HOListFunctions.c
	$(COMP) $(CFLAGS) HOListFunctions.c

SimpleFunctions.o: SimpleFunctions.c
	$(COMP) $(CFLAGS) SimpleFunctions.c

List.o: List.c
	$(COMP) $(CFLAGS) List.c

clean:
	rm -f main.o SimpleFunctions.o List.o ListIO.o HOListFunctions.o
