/*
 * util.c
 *
 *  Created on: May 14, 2019
 *      Author: aviv
 */

#include "util.h"

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

/* Validates if column is correct. */
void* checkColumn(void* args) {
	int row;
	int arr[9] = { 0 };

	// Get the arguments:
	myarg_t* arguments = (myarg_t*) args;
	int col = arguments->num;
	matrix_t* matrix = arguments->mat;
	int* result = arguments->result;

	// Do the work:
	for (row = 0; row < ROW; row++) {
		int currentDigit = matrix->data[row][col];

		if (arr[currentDigit - 1] == 0) {
			arr[currentDigit - 1]++;
		} else {
			*result = 0;
			//printf("Col:%d, check is:%d\n", row, *result);
			return NULL;
		}
	}
	*result = 1;
	//printf("Col:%d, check is:%d\n", row, *result);
	return NULL;
}

/* Validates if row is correct. */
void* checkRow(void* args) {
	int col;
	int arr[9] = { 0 };

	// Get the arguments:
	myarg_t* arguments = (myarg_t*) args;
	int row = arguments->num;
	matrix_t* matrix = arguments->mat;
	int* result = arguments->result;

	// Do the work:
	for (col = 0; col < COL; col++) {
		int currentDigit = matrix->data[row][col];

		if (arr[currentDigit - 1] == 0) {
			arr[currentDigit - 1]++;
		} else {
			*result = 0;
			//printf("Row:%d, check is:%d\n", row, *result);
			return NULL;
		}
	}
	*result = 1;
	//printf("Row:%d, check is:%d\n", row, *result);
	return NULL;
}

/* Validates if sub-matrix is correct. */
void* checkSubMatrix(void* args) {
	int i, j, row, col;
	int matLimit = 3;
	int arr[COL] = { 0 };

	// Get the arguments:
	myarg_t* arguments = (myarg_t*) args;
	int matNum = arguments->num;
	matrix_t* matrix = arguments->mat;
	int* result = arguments->result;

	// Sets the bounds for the check:
	col = (matNum % 3) * 3;
	row = (matNum >= 3) ? 1 : 0;
	row += (matNum >= 3 * 2) ? 1 : 0;
	row *= matLimit;

	for (i = row; i < row + matLimit; i++) {
		for (j = col; j < col + matLimit; j++) {
			int currentDigit = matrix->data[i][j];

			if (arr[currentDigit - 1] == 0) {
				arr[currentDigit - 1]++;
			} else {
				*result = 0;
				//printf("Mat:%d (%dx%d), check is:%d\n", matNum, row, col, *result);
				return NULL;
			}
		}
	}
	*result = 1;
	//printf("Mat:%d (%dx%d), check is:%d\n", matNum, row, col, *result);
	return NULL;
}

/* Validates no item == 0 in the given array. */
int checkIfLegal(int arr[], int size) {
	int i;

	for (i = 0; i < size; i++) {
		if (arr[i] == 0)
			return 0;
	}
	return 1;
}

void readFileIntoMatrix(matrix_t* mat, char* buffer, int bufferSize) {
	int i = 0;
	int row = 0, col = 0;
	for (i = 0; i < bufferSize; i++) {

		const char* current = &buffer[i];

		if (*current >= 48 && *current <= 57) {

			int currentDigit = atoi(current);

			mat->data[row][col] = currentDigit;
			col++;

			if (col == COL) {
				col = 0;
				row++;
			}
		}
	}
}

void printMatrix(matrix_t* mat) {
	int col, row;

	for (row = 0; row < ROW; row++) {
		for (col = 0; col < COL; col++) {
			printf("%d ", mat->data[row][col]);
		}
		printf("\n");
	}
}

void readToMatrix(matrix_t* mat, const char* fileName) {
	int inputFd;
	int numRead;
	char buf[BUF_SIZE];

	// Opens the input file:
	inputFd = open(fileName, O_RDONLY);
	if (inputFd == -1) {
		printf("\nERROR: could not open %s\n", fileName);
		exit(1);
	}

	// Reads the input file content into the matrix:
	while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
		readFileIntoMatrix(mat, buf, BUF_SIZE);
	}

	// Checks if successfully read:
	if (numRead == -1) {
		printf("\nERROR: could not read the file content.\n");
		exit(1);
	}

	// Closes the input file:
	if (close(inputFd) == -1) {
		printf("\nERROR: could not close the input file.\n");
		exit(1);
	}
}
