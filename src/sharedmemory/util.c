/*
 ============================================================================
 Name        : HW_1 (Part B)
 Author      : Aviv Shabtay, Or Pinhas
 IDs		 : 313583619, 318865888
 ============================================================================
 */

#include "util.h"

/* 1 = change, 0 = no change */
int isStatusChanged(shared_t* sharedMemory) {
	int i;

	for (i = 0; i < NUM_OF_CHILDREN; i++) {
		int temp = sharedMemory->status[i];
		if (temp == WAIT_FOR_DATA)
			return 0;
	}
	return 1;
}

/* Get status number and updates the shared memory statuses. */
void updateStatusesValue(shared_t* sharedMemory, int status) {
	int i;
	for (i = 0; i < NUM_OF_CHILDREN; i++)
		sharedMemory->status[i] = status;
}

/* Get the arguments from argv and creates dynamic allocated array. */
char** createFilesFromArgs(int argc, char* argv[]) {

	int i;
	char** inputFiles = malloc(sizeof(char*) * (argc - 1));

	for (i = 1; i < argc; i++) {
		inputFiles[i - 1] = strdup((argv[i]));
	}

	return inputFiles;
}

/* Helper function */
void printStatuses(shared_t* sharedMemory) {
	int i;
	for (i = 0; i < NUM_OF_CHILDREN; i++)
		printf("Status #%d is: %d\n", i, sharedMemory->status[i]);
}

/* Helper function */
void waitForChildren() {
	int i;
	for (i = 0; i < NUM_OF_CHILDREN; i++)
		wait(NULL);
}

/* Reads matrix data from STDIN */
void readFromTerminal(int mat[][COL]) {
	int row, col;

	for (row = 0; row < ROW; row++) {
		for (col = 0; col < COL; col++) {
			scanf("%d", &mat[row][col]);
		}
	}
}

/* Get children result from shared memory. */
void getResultFromChildren(shared_t* sharedMemory, int* result) {
	int i;
	int temp = 0;

	for (i = 0; i < NUM_OF_CHILDREN; i++)
		temp += sharedMemory->status[i];

	*result = ((temp == 3) ? 1 : 0);
}

/* Read matrix solution from the terminal line by line. */
void readMatrixFromTerminal(int mat[ROW][COL]) {

	int i, j;
	int bufferSize = 18;
	char buffer[bufferSize];
	char* current;
	char temp[2];

	printf("Please enter the solution:\n");

	for (i = 0; i < ROW; i++) {
		// Read 18 characters from standard input (white spaces + solution numbers):
		fgets(buffer, bufferSize, stdin);
		current = buffer;

		cleanTerminal();

		for (j = 0; j < COL; j++) {
			// Get the current character:
			temp[0] = *current;
			temp[1] = '\n';

			// Insert the value to the matrix:
			mat[i][j] = atoi(temp);

			// Pass unwanted character:
			current += 2;
		}
	}
}

/* Clean the terminal from any character. */
void cleanTerminal() {
	int c;
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
}
