CFLAGS=-c -pedantic-errors -Wall
COMP=gcc
.PHONY: all clean install uninstall

all: lab6

lab6: main.o
	$(COMP) -o lab6 main.o mem.o memDebug.o mmapControl.o

main.o: mem.o memDebug.o main.c
	$(COMP) $(CFLAGS) main.c

mem.o: mem.c mmapControl.o
	$(COMP) $(CFLAGS) mem.c

memDebug.o: memDebug.c
	$(COMP) $(CFLAGS) memDebug.c

mmapControl.o: mmapControl.c
	$(COMP) $(CFLAGS) mmapControl.c

clean:
	rm -f main.o mem.o memDebug.o mmapControl.o
