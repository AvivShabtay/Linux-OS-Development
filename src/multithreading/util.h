/*
 * util.h
 *
 *  Created on: May 14, 2019
 *      Author: aviv
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

//#include "matrix.h"

#define NUM_OF_THREADS 27
#define NUM_OF_FUNCS 3
#define ROW 9
#define COL 9
#define BUF_SIZE 162

struct Matrix {
	int data[ROW][COL];
}typedef matrix_t;

typedef struct {
	int num;
	matrix_t* mat;
	int* result;
} myarg_t;

void readFileIntoMatrix(matrix_t* mat, char* buffer, int bufferSize);
void printMatrix(matrix_t* mat);
void readToMatrix(matrix_t* mat, const char* fileName);
char** createFilesFromArgs(int argc, char* argv[]);
void readMatrixFromTerminal(matrix_t* mat);
void cleanTerminal();
void* checkColumn(void* args);
void* checkRow(void* args);
void* checkSubMatrix(void* args);
int checkIfLegal(int arr[], int size);

#endif /* UTIL_H_ */
