/*
 * util.c
 *
 *  Created on: May 14, 2019
 *      Author: aviv
 */

#include "util.h"

/* Writes data to children. */
int writeToChildren(int* childrenPipes[], matrix_t* data, size_t size) {
	int i;
	int* fd;
	int sum;

	for (i = 0; i < NUM_OF_CHILDREN; i++) {
		fd = childrenPipes[i];
		sum += write(fd[WRITE_TO_PIPE], data, size);
	}
	return sum;
}

char** createFilesFromArgs(int argc, char* argv[]) {

	int i;
	char** inputFiles = malloc(sizeof(char*) * (argc - 1));

	for (i = 1; i < argc; i++) {
		inputFiles[i - 1] = strdup((argv[i]));
	}

	return inputFiles;
}

/* Read matrix solution from the terminal line by line. */
void readMatrixFromTerminal(matrix_t* mat) {

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
			mat->data[i][j] = atoi(temp);

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
