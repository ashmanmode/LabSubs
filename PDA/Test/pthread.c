#include <stdlib.h>
#include <stdio.h>
#include "pthread.h"
int sum=0; //Global variable touched by all threads

//Function to be called by each thread
void *adder() 
{
	printf("%d\n",sum );
	sleep(1);
	sum = sum + 1;
	return NULL;
}

int main() 
{
	const int numThreads=24;
	int i;
	pthread_t threads[numThreads];
	for (i=0; i<numThreads; i++) //Start threads
	if (pthread_create(threads+i, NULL, adder, NULL) != 0)
	return i+1;
	for (i=0; i<numThreads; i++) //Stop threads
	if (pthread_join(threads[i], NULL) != 0)
	return numThreads+i+1;
	printf("Sum computed: %d\n",sum);
	return 0;
}