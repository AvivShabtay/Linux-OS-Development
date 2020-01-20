/*
 ============================================================================
 Name        : child.c
 Author      : Aviv Shabtay
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {

	int operation;
	int numRead;
	matrix_t* inputMatrix;
	//int* result;
	char* result;
	char (*verify[])(matrix_t*) = {verifyRows, verifyCols, verifyMatrixes };

	// Get the operation to commit:
	operation = atoi(argv[1]);

	// Allocate variables:
	inputMatrix = (matrix_t*) malloc(sizeof(matrix_t));
	result = (char*) malloc(sizeof(int));

	do {
		// Read from parent matrix to check:
		numRead = read(STDIN_FILENO, inputMatrix, sizeof(matrix_t));

		// If we cannot read anything, or parent finish writing:
		if (numRead <= 0) {
			exit(1);
		}

		*result = verify[operation](inputMatrix);

		// Send the result to the parent:
		write(STDOUT_FILENO, result, sizeof(char));

	} while (numRead > 0);

	// Free unused memory:
	free(inputMatrix);
	free(result);

	return EXIT_SUCCESS;
}
