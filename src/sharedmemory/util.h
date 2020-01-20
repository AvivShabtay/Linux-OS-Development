/*
 ============================================================================
 Name        : HW_1 (Part B)
 Author      : Aviv Shabtay, Or Pinhas
 IDs		 : 313583619, 318865888
 ============================================================================
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "matrix.h"

#define NUM_OF_CHILDREN 3
#define WAIT_FOR_DATA -1
#define STOP -2
#define IDLE -3

struct Shared {
	int solution[ROW][COL];
	int status[3];
}typedef shared_t;

int isStatusChanged(shared_t* sharedMemory);
void updateStatusesValue(shared_t* sharedMemory, int status);
char** createFilesFromArgs(int argc, char* argv[]);
void printStatuses(shared_t* sharedMemory);
void waitForChildren();
void readFromTerminal(int mat[][COL]);
void getResultFromChildren(shared_t* sharedMemory, int* result);
void readMatrixFromTerminal(int mat[][COL]);
void cleanTerminal();

#endif /* UTIL_H_ */
