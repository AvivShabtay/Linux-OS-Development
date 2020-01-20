# -*- MakeFile -*-

all: parent child

parent: parent.o matrix.o util.o
	gcc parent.o matrix.o util.o -o parent -l m

parent.o: parent.c
	gcc -c parent.c

matrix.o: matrix.c
	gcc -c matrix.c

util.o: util.c
	gcc -c util.c

child: child.o matrix.o
	gcc child.o matrix.o -o child -l m

child.o: child.c
	gcc -c child.c
