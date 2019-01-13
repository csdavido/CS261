CC=gcc
CFLAGS=-Wall -std=c99

all: prog

prog: linkedList.o linkedListMain_timing.o
	gcc -g -Wall -std=c99 -o prog linkedList.o linkedListMain_timing.o
linkedList.o: linkedList.c linkedList.h
	gcc -g -Wall -std=c99 -c linkedList.c
linkedListMain_timing.o: linkedListMain_timing.c linkedList.h
	gcc -g -Wall -std=c99 -c linkedListMain_timing.c

clean:
	-rm *.o

cleanall: clean
	-rm prog