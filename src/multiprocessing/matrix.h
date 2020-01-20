/*
 * matrix.h
 *
 *  Created on: Apr 28, 2019
 *      Author: aviv
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#define ROW 9
#define COL 9
#define BUF_SIZE 162

struct Matrix {
	int data[ROW][COL];
}typedef matrix_t;

void readFileIntoMatrix(matrix_t* mat, char* buffer, int bufferSize);
void printMatrix(matrix_t* mat);
void readToMatrix(matrix_t* mat, const char* fileName);
void zeroArray(int* arr, int size);
int verifyRows(matrix_t* mat);
int verifyCols(matrix_t* mat);
int verifyMatrixes(matrix_t* mat);
int verifyMat(matrix_t* mat, int row, int col);

#endif /* MATRIX_H_ */
