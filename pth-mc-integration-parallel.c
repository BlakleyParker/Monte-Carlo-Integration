#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include "timer.h"

// Blakley Parker
// pthread_07 Monte-Carlo Integration PARALLEL
//COMPILE: gcc -g -Wall -o pth-mc-integration-parallel pth-mc-integration-parallel.c -lm -lpthread

int thread_count;
int globalSum;
pthread_mutex_t mutex;
int a;
int b;
long long n;


void* integrate(void* rank);

double f(double x) {
	return x*x;
}

int main(int argc, char *argv[])
{
  double start, finish, elapsed;
	float underArea, wholeArea, percentArea;
	pthread_t* thread_handles;
	long thread;  /* Use long in case of a 64-bit system */


	if(argc < 5) {
      printf("Usage: ./pth-mc-integration-parallel <num_threads> <a> <b> <n>\n");
      exit(1);
  }
	a = atoi(argv[2]);
	b = atoi(argv[3]);
	n = atoll(argv[4]);

	pthread_mutex_init(&mutex, NULL);
  GET_TIME(start);

	thread_count = strtol(argv[1], NULL, 10);
	thread_handles = malloc(thread_count*sizeof(pthread_t));

	GET_TIME(start);

	for (thread = 0; thread < thread_count; thread++){
		 pthread_create(&thread_handles[thread], NULL,
				 integrate, (void*)thread);
  }
	for (thread = 0; thread < thread_count; thread++){
		 pthread_join(thread_handles[thread], NULL);
	 }

	wholeArea = (b-a)*f(b);
	percentArea = ((float)globalSum/(float)n);
	underArea = wholeArea * percentArea;
	GET_TIME(finish);
	elapsed = finish - start;

	printf("a\tb\tn\tapproximation_of_integration\texec_time\tp\n%d\t%d\t%lld\t%f\t\t\t%f\t%d\n",a,b,n, underArea, elapsed, thread_count);

	pthread_mutex_destroy(&mutex);
	free(thread_handles);

	return 0;
}

//function for the threads to do
void* integrate(void* rank){
	long my_rank = (long) rank;
	int i;
	int pointsUnderLine = 0;
	double x, y, now;
	GET_TIME(now);

	unsigned short xsubi[3];
	xsubi[0] = my_rank*now;

	for(i=0; i < n/thread_count; i++) {
			x = erand48(xsubi);
			x = (b-a)*x +a;
			y = erand48(xsubi);
			y = y*f(b);

			if (y <= f(x)){
				pointsUnderLine++;
			}

	}
	pthread_mutex_lock(&mutex);
	globalSum += pointsUnderLine;
	pthread_mutex_unlock(&mutex);

	return NULL;
}
