#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "timer.h"

// Blakley Parker
// MPI_06 Monte-Carlo Integration SERIAL

double f(double x) {
	return x*x;
}
int main(int argc, char *argv[])
{
  int a, b, i, n;
	int pointsUnderLine = 0;
	double x, y;
	time_t t;
  double start, finish, elapsed;
	float underArea, wholeArea, percentArea;
  GET_TIME(start);

  if(argc !=4) {
      printf("Usage: ./mc-integration-serial <a> <b> <n>\n");
      exit(1);
  }

 	a = atoi(argv[1]);
  b = atoi(argv[2]);
  n = atoi(argv[3]);
	srand48((unsigned)time(&t));

  for( i = 0 ; i < n ; i++ ) {
      x = drand48();
			x = (b-a)*x +a;
      y = drand48();
			y = y*f(b);
			//printf("Point %d - X:%f, Y:%f\n", i+1, x, y);

			if (y <= f(x)){
				pointsUnderLine++;
			}
  }
	wholeArea = (b-a)*f(b);
	percentArea = ((float)pointsUnderLine/(float)n);
	underArea = wholeArea * percentArea;


  GET_TIME(finish);
  elapsed = finish - start;
	printf("a\tb\tn\tapproximation_of_integration\texec_time\n");
	printf("%d\t%d\t%d\t%f\t\t\t%f",a,b,n, underArea, elapsed);
}
