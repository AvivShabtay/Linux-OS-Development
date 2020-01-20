/*
 ============================================================================
 Author      : Aviv Shabtay
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include "util.h"

#define N 4 // Number of threads to be created

void pullTask(tasksPool_t* pool, taskArgs_t** task);
void* doTask(void* args);

// Global variables:
pthread_cond_t work = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tasksMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t exitedThreadMutex = PTHREAD_MUTEX_INITIALIZER;
int* wrong;

int main(int argc, char* argv[]) {
	int i;
	pthread_t thread;
	matrix_t* mat;
	tasksPool_t* taskPool;

	// Allocates memory:
	taskPool = (tasksPool_t*) malloc(sizeof(taskPool));
	mat = (matrix_t*) malloc(sizeof(matrix_t));
	wrong = (int*) malloc(sizeof(int));

	// Reads data into matrix:
	if(argc == 1){
		readMatrixFromTerminal(mat);
	} else{
		readToMatrix(mat, argv[1]);
	}

	// Initializes the tasks:
	initTaskPool(taskPool);
	initTasks(taskPool->tasks, mat, wrong);

	// Creates the threads:
	for (i = 0; i < N; i++) {
		pthread_create(&thread, NULL, doTask, taskPool);
	}

	// Wait for threads to finish:
	pthread_cond_wait(&work, &m);

	// Prints the result to the user:
	printf("%s is %s\n",(argc==1 ? argv[1] : "Solution")
			, (*wrong == 0 ? "leagl" : "not legal"));

	// Release memory:
	free(mat);
	free(wrong);

	return EXIT_SUCCESS;
}

void* doTask(void* args) {

	tasksPool_t* taskPool = (tasksPool_t*) args;
	taskArgs_t* arguments = NULL;
	matrix_t* mat;
	int (*verify)(matrix_t*, int*);
	int* num;

	// Pulls task to process:
	pullTask(taskPool, &arguments);

	while (arguments != NULL) {
		int verifyResult;

		// Setups task arguments:
		mat = arguments->mat;
		verify = arguments->verify;
		num = &arguments->num;
		wrong = arguments->result;

		// Do thread works:
		verifyResult = verify(mat, num);
		if(!verifyResult){
			*wrong = 1;
		}

		// Pulls task to process:
		pullTask(taskPool, &arguments);
	}

	// Performs exit:
	if (pthread_mutex_lock(&exitedThreadMutex) != 0) {
		fprintf(stderr, "Could not lock exitedThreadMutex: %s\n",
				strerror(errno));
		exit(1);
	}

	taskPool->exitedThreads++;

	if (pthread_mutex_unlock(&exitedThreadMutex) != 0) {
		fprintf(stderr, "Could not unlock exitedThreadMutex: %s\n",
				strerror(errno));
		exit(1);
	}

	// If it the last thread, notify the parent:
	if (taskPool->exitedThreads == N) {
		pthread_cond_signal(&work);
	}

	return NULL;
}

/* Extracts task from the pool, otherwise return null. */
void pullTask(tasksPool_t* pool, taskArgs_t** task) {

	// Enters critical section:
	if (pthread_mutex_lock(&tasksMutex) != 0) {
		fprintf(stderr, "Could not lock taskMutext: %s\n", strerror(errno));
		exit(1);
	}

	int currTask = pool->currentTask;
	if (currTask < NUM_OF_TASKS) {
		// Extracts task:
		*task = pool->tasks[currTask];

		// Updates the task counter:
		pool->currentTask = ++currTask;
	}
	// In case all the task have been taken:
	else {
		*task = NULL;
	}
	// Exits critical section:
	if (pthread_mutex_unlock(&tasksMutex) != 0) {
		fprintf(stderr, "Could not unlock taskMutext: %s\n", strerror(errno));
		exit(1);
	}
}
