/*
 * matrix.c
 *
 *  Created on: Apr 28, 2019
 *      Author: aviv
 */

#include "matrix.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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

void zeroArray(int* arr, int size) {
	int i;

	for (i = 0; i < size; i++)
		arr[i] = 0;
}

int verifyRows(matrix_t* mat) {
	int row = 0, col = 0;
	int arr[COL] = { 0 };

	for (row = 0; row < ROW; row++) {
		for (col = 0; col < COL; col++) {
			int currentDigit = mat->data[row][col];

			if (arr[currentDigit - 1] == 0) {
				arr[currentDigit - 1]++;
			} else {
				return 0;
			}
		}
		zeroArray(arr, COL);
	}
	return 1;
}

int verifyCols(matrix_t* mat) {
	int row = 0, col = 0;
	int arr[COL] = { 0 };

	for (col = 0; col < COL; col++) {
		for (row = 0; row < ROW; row++) {
			int currentDigit = mat->data[row][col];

			if (arr[currentDigit - 1] == 0) {
				arr[currentDigit - 1]++;
			} else {
				return 0;
			}
		}
		zeroArray(arr, COL);
	}
	return 1;
}

int verifyMatrixes(matrix_t* mat) {
	int i = 0, j = 0;
	int matLimit = 3;
	int result;

	for (i = 0; i < matLimit; i++) {
		for (j = 0; j < matLimit; j++) {
			result = verifyMat(mat, i * 3, j * 3);
			if (!result)
				return 0;
		}
	}
	return 1;
}

int verifyMat(matrix_t* mat, int row, int col) {
	int i, j;
	int matLimit = 3;
	int arr[COL] = { 0 };

	for (i = row; i < row + matLimit; i++) {
		for (j = row; j < row + matLimit; j++) {
			int currentDigit = mat->data[i][j];

			if (arr[currentDigit - 1] == 0) {
				arr[currentDigit - 1]++;
			} else {
				return 0;
			}
		}
	}
	return 1;
}

