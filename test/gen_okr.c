#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double fun( double x, int n ) {
				double r= ((double)rand() - RAND_MAX/2.0)/RAND_MAX/5; // +-10%
				return n*(sin(x*2*M_PI));
}

int main( int argc, char **argv ) {
				FILE *out= argc > 1 ? fopen( argv[1], "w" ) : stdout;
				int n= argc > 2 ? atoi( argv[2] ) : 100;
				double a= argc > 3 ? atof( argv[3] ) : 0;
				double b= argc > 4 ? atof( argv[4] ) : 2;
				
				srand( argc > 5 ? atoi(argv[5]) : time(NULL) );

				int i;
				double dx = (b-a)/(n-1);

				for( i =0; i < n; i++ ) {
								fprintf( out, "%d %g\n", i, fun(a+i*dx, n) );
				}
				fclose( out );

				return 0;
}
