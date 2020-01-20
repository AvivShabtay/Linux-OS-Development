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
#include <pthread.h>

//#include "matrix.h"

#define NUM_OF_TASKS 27
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
	int (*verify)(matrix_t*, int*);
} taskArgs_t;

typedef struct {
	taskArgs_t** tasks;
	int currentTask;
	int exitedThreads;
} tasksPool_t;

void readFileIntoMatrix(matrix_t* mat, char* buffer, int bufferSize);
void printMatrix(matrix_t* mat);
void readToMatrix(matrix_t* mat, const char* fileName);
char** createFilesFromArgs(int argc, char* argv[]);
void readMatrixFromTerminal(matrix_t* mat);
void cleanTerminal();
int checkColumn(matrix_t* matrix, int* col);
int checkRow(matrix_t* matrix, int* row);
int checkSubMatrix(matrix_t* matrix, int* matNum);
int checkIfLegal(int arr[], int size);
void initTasks(taskArgs_t* taskArguments[], matrix_t* mat, int* result);
void initTaskPool(tasksPool_t* taskPool);

#endif /* UTIL_H_ */
