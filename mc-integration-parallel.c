#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "timer.h"
#include "mpi.h"

// Blakley Parker
// MPI_06 Monte-Carlo Integration PARALLEL

double f(double x) {
	return x*x;
}
int main(int argc, char *argv[])
{
  int a, b, i, n, myid, numprocs;
	int pointsUnderLine = 0;
	int totalPointsUnderLine = 0;
	double x, y;
	time_t t;
  double start, finish, elapsed, now;
	float underArea, wholeArea, percentArea;
	char processor_name[MPI_MAX_PROCESSOR_NAME];

  GET_TIME(start);

  if(argc < 4) {
      printf("Usage: ./mc-integration-serial <a> <b> <n>\n");
      exit(1);
  }

 	a = atoi(argv[1]);
  b = atoi(argv[2]);
  n = atoi(argv[3]);

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	GET_TIME(now);
	srand48(now*(double)myid+1*i);

  for( i = 0 ; i < n/numprocs ; i++ ) {

      x = drand48();
			x = (b-a)*x +a;
      y = drand48();
			y = y*f(b);

			if (y <= f(x)){
				pointsUnderLine++;
			}
  }
	MPI_Reduce(&pointsUnderLine, &totalPointsUnderLine, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

if (myid == 0){
	wholeArea = (b-a)*f(b);
	percentArea = ((float)totalPointsUnderLine/(float)n);
	underArea = wholeArea * percentArea;

  GET_TIME(finish);
  elapsed = finish - start;
	printf("a\tb\tn\tapproximation_of_integration\texec_time\tp\n%d\t%d\t%d\t%f\t\t\t%f\t%d\n",a,b,n, underArea, elapsed, numprocs);
}

	MPI_Finalize();
	return 0;
}
