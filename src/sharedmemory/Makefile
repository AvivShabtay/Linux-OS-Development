# -*- MakeFile -*-

all: HW1_PartB

HW1_PartB: HW1_PartB.o matrix.o util.o
	gcc HW1_PartB.o matrix.o util.o -o HW1_PartB -l m

HW1_PartB.o: HW1_PartB.c
	gcc -c HW1_PartB.c

matrix.o: matrix.c
	gcc -c matrix.c

util.o: util.c
	gcc -c util.c
