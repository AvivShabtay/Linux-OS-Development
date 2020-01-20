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

volatile void readFileIntoMatrix(int mat[][COL], char* buffer, int bufferSize);
volatile void printMatrix(int mat[][COL]);
volatile void readToMatrix(int mat[][COL], const char* fileName);
volatile void zeroArray(int* arr, int size);
volatile int verifyRows(int mat[][COL]);
volatile int verifyCols(int mat[][COL]);
volatile int verifyMatrixes(int mat[][COL]);
volatile int verifyMat(int mat[][COL], int row, int col);

#endif /* MATRIX_H_ */
