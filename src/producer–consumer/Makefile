# -*- MakeFile -*-

all: v2

v2: v2.o util.o
	gcc v2.o util.o -o v2 -l m -pthread

v2.o: v2.c
	gcc -c v2.c

util.o: util.c
	gcc -c util.c
