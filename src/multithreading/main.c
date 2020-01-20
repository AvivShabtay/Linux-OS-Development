/*
 ============================================================================
 Author      : Aviv Shabtay
 ============================================================================
 */
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
//#include "matrix.h"
#include "util.h"

int main(int argc, char* argv[]) {

	int j;
	void* (*verify[])(void*) = {checkRow, checkColumn, checkSubMatrix };
	int results[NUM_OF_THREADS] = { 0 }; // 9-rows + 9-columns + 9-sub-matrixes
	myarg_t* argumentsArray[NUM_OF_THREADS];
	pthread_t threads[NUM_OF_THREADS];
	matrix_t* mat;
	int checkResult = -1;

	// Allocate memory:
	mat = (matrix_t*) malloc(sizeof(matrix_t));

	// Reads data into matrix:
	if (argc == 1) {
		readMatrixFromTerminal(mat);
	} else {
		readToMatrix(mat, argv[1]);
	}

	// Creates 27 threads:
	for (j = 0; j < NUM_OF_THREADS; j++) {
		myarg_t* arguments;

		int currentFunc = j % NUM_OF_FUNCS;		// 0-2
		int currentNumber = j / NUM_OF_FUNCS; 	//0-8

		// Assigns arguments for the current thread:
		arguments = (myarg_t*) malloc(sizeof(myarg_t));
		arguments->mat = mat;
		arguments->num = currentNumber;
		arguments->result = &results[j];
		argumentsArray[j] = arguments;

		// Creates the thread:
		pthread_create(&threads[j], NULL, verify[currentFunc], arguments);
	}

	// Wait for all the threads to finish:
	for (j = 0; j < NUM_OF_THREADS; j++)
		pthread_join(threads[j], NULL);

	// Prints the result to the user:
	checkResult = checkIfLegal(results, NUM_OF_THREADS);
	printf("%s is %s\n", (argc == 11 ? argv[1] : "Solution"),
			(checkResult == 1 ? "legal" : "not legal"));

	// Release memory:
	free(mat);

	for (j = 0; j < NUM_OF_THREADS; j++)
		free(argumentsArray[j]);

	return EXIT_SUCCESS;
}
