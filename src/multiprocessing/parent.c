/*
 ============================================================================
 Name        : parent.c
 Author      : Aviv Shabtay
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include "matrix.h"
#include "util.h"

int main(int argc, char* argv[]) {

	int i;
	int* fd;
	int parentFd[2];
	int firstChildFd[2];
	int secondChildFd[2];
	int thirdChildFd[2];
	int* childrenFd[3] = { firstChildFd, secondChildFd, thirdChildFd };
	pid_t parentPID = getpid();

	// Validates pipe creation:
	if ((pipe(parentFd) == -1) || (pipe(firstChildFd) == -1)
			|| (pipe(secondChildFd) == -1) || (pipe(thirdChildFd) == -1)) {
		fprintf(stderr, "Could not create pipe: %s\n", strerror(errno));
		return 1;
	}

	for (i = 0; i < NUM_OF_CHILDREN; i++) {
		// Child process:
		if (fork() == 0) {

			char op = i + '0'; // Cast integer to char
			char* childProcessArgs[3];

			childProcessArgs[0] = strdup(CHILD_PROGRAM);
			childProcessArgs[1] = strdup(&op);
			childProcessArgs[2] = NULL;

			fd = childrenFd[i];

			close(fd[WRITE_TO_PIPE]);
			close(parentFd[READ_FROM_PIPE]);

			dup2(fd[READ_FROM_PIPE], STDIN_FILENO);	// Read-from
			dup2(parentFd[WRITE_TO_PIPE], STDOUT_FILENO);	// Write-to

			execvp(childProcessArgs[0], childProcessArgs);

			// In any case of error:
			fprintf(stderr, "Failed to execute operation \n");
			exit(1);

		} // End of if - validate child process code segment
	} // End of for - open child processes

	// Parent code:
	if (getpid() == parentPID) {

		matrix_t* input;
		int* result;
		char* buffer;
		char** inputFiles = NULL;
		int i;
		int numOfFiles;

		// Allocating variables:
		input = (matrix_t*) malloc(sizeof(matrix_t));
		result = (int*) malloc(sizeof(int));
		buffer = (char*) malloc(sizeof(char));

		// Close writing to parent pipe:
		close(parentFd[WRITE_TO_PIPE]);

		// Close reading from child pipe:
		close(firstChildFd[READ_FROM_PIPE]);
		close(secondChildFd[READ_FROM_PIPE]);
		close(thirdChildFd[READ_FROM_PIPE]);

		// Get the file name from the terminal:
		if (argc > 1) {
			inputFiles = createFilesFromArgs(argc, argv);
			numOfFiles = argc - 1;
		}
		// If there are no arguments, ready to read file:
		else {
			numOfFiles = 1;
		}

		for (i = 0; i < numOfFiles; i++) {

			// Reads data from input file into matrix:
			if (argc > 1) {
				readToMatrix(input, inputFiles[i]);
			}
			// Read data from the terminal:
			else {
				readMatrixFromTerminal(input);
			}

			// Writes the data to children:
			writeToChildren(childrenFd, input, sizeof(matrix_t));

			// Reads the result from children:
			readFromChildren(parentFd, result, buffer, sizeof(char));

			printf("%s is %s\n",
					(inputFiles ? inputFiles[i] : "The input matrix"),
					((*result == CORRECT_RESULT) ? "legal" : "not legal"));
		} // End of for

		// Free unused memory:
		free(input);
		free(result);
		free(buffer);
	} // End of parent logic

	// Validate closing all pipes:
	close(firstChildFd[READ_FROM_PIPE]);
	close(firstChildFd[WRITE_TO_PIPE]);
	close(secondChildFd[READ_FROM_PIPE]);
	close(secondChildFd[WRITE_TO_PIPE]);
	close(thirdChildFd[READ_FROM_PIPE]);
	close(thirdChildFd[WRITE_TO_PIPE]);
	close(parentFd[READ_FROM_PIPE]);
	close(parentFd[WRITE_TO_PIPE]);

	return EXIT_SUCCESS;
}

/* Reads results from children. */
int readFromChildren(int* parentPipe, int* result, char* buffer, size_t size) {
	int i;
	*result = 0;
	int sum;

	for (i = 0; i < NUM_OF_CHILDREN; i++) {
		sum += read(parentPipe[READ_FROM_PIPE], buffer, size);
		*result += atoi(buffer);
	}
	return sum;
}

