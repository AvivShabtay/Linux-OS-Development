# -*- MakeFile -*-

all: v1

v1: v1.o util.o
	gcc v1.o util.o -o v1 -l m -pthread

v1.o: v1.c
	gcc -c v1.c

util.o: util.c
	gcc -c util.c
