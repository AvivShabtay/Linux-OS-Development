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
#include "matrix.h"

#define NUM_OF_CHILDREN 3
#define CHILD_PROGRAM "./child"
#define READ_FROM_PIPE 0
#define WRITE_TO_PIPE 1
#define CORRECT_RESULT 3

char** createFilesFromArgs(int argc, char* argv[]);
int writeToChildren(int* childrenPipes[], matrix_t* data, size_t size);
int readFromChildren(int* parentPipe, int* result, char* buffer, size_t size);
void readMatrixFromTerminal(matrix_t* mat);
void cleanTerminal();

#endif /* UTIL_H_ */
