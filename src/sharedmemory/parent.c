/*
 ============================================================================
 Author      : Aviv Shabtay
 ============================================================================
 */

#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "util.h"

int main(int argc, char* argv[]) {
	pid_t parentPID = getpid();
	shared_t* sharedMemory = NULL;
	int (*verify[])(int[][COL]) = {verifyRows, verifyCols, verifyMatrixes };

	// Shared memory allocation:
	sharedMemory = (shared_t*) mmap( NULL, sizeof(shared_t),
	PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);

	// Check the shared memory allocation:
	if (sharedMemory == MAP_FAILED) {
		printf("Cannot allocate shared memory\n");
		exit(1);
	}

	// Initialize the statuses:
	updateStatusesValue(sharedMemory, IDLE);

	// Creating the children processes:
	for (int i = 0; i < NUM_OF_CHILDREN; i++) {

		// Child code:
		if (fork() == 0) {
			int result;

			//printf("[son] PID %d from [parent] PID %d\n", getpid(), getppid());

			// Do until tell to stop:
			while (1) {
				if (sharedMemory->status[i] == STOP) {
					//printf("[son] PID %d from [parent] PID %d exits\n", getpid(), getppid());
					exit(EXIT_SUCCESS);

				} else if (sharedMemory->status[i] == WAIT_FOR_DATA) {
					result = verify[i](sharedMemory->solution);
					sharedMemory->status[i] = result;
					//printf("[son] PID %d verify result: %d\n", getpid(), sharedMemory->status[i]);
				} else if (sharedMemory->status[i] == IDLE) {
					// Just wait...
				}
			}
		}
	}

	// Parent code:
	if (getpid() == parentPID) {
		int i;
		int result;
		char** fileNames = NULL;
		int numOfFiles;

		// Get the file name from the terminal:
		if (argc > 1) {
			fileNames = createFilesFromArgs(argc, argv);
			numOfFiles = argc - 1;
		}
		// If there are no arguments, ready to read file:
		else {
			numOfFiles = 1;
		}

		for (i = 0; i < numOfFiles; i++) {

			// Read data from file into matrix:
			if (argc > 1) {
				readToMatrix(sharedMemory->solution, fileNames[i]);
			}
			// Read data from the terminal:
			else {
				readMatrixFromTerminal(sharedMemory->solution);
			}

			// Tell the children to start working:
			updateStatusesValue(sharedMemory, WAIT_FOR_DATA);

			// Wait for the children to finish:
			while (!isStatusChanged(sharedMemory))
				;

			// Calculate the result value from children:
			getResultFromChildren(sharedMemory, &result);

			// Print message to the user:
			printf("%s is %s.\n",
					(fileNames ? fileNames[i] : "The input matrix"),
					(result ? "legal" : "not legal"));

			// Initialize the statuses:
			updateStatusesValue(sharedMemory, IDLE);
		}
		// Stop the children:
		updateStatusesValue(sharedMemory, STOP);
	}

	// Wait for children to exit:
	waitForChildren();
	exit(EXIT_SUCCESS);
}
