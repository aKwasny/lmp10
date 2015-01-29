#include "../points.h"
#include "trygonometrycznie.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* na podstawie http://kik.weii.tu.koszalin.pl/aproksymacja/aproks_tryg/page_dyp/aproksytr1.htm */

double *licz_wartosci_wspolczynnikow_ai(points_t pts) {
	int n = pts.n;
	int j = 1;
	int i;
	double wyn;
	double *a = NULL;
	int m = 0;

	char *mEnv= getenv( "APPROX_BASE_SIZE" );

	if( mEnv != NULL && (( atoi( mEnv ) > 0 ) && ( atoi ( mEnv ) < (n-1)/2) ) ) {
		m = atoi( mEnv );
	} else {
		m = ((n-1)/2) - 1;
	}


	for(i = 0; i < m; i++) {

		wyn = 0;

		if(i == 0) {
			a = malloc(m*sizeof(double));	/* ustalanie wartości a0 */
			for(j = 1; j <= n; j++) {
				wyn += pts.y[j - 1] ;
			}

			wyn = wyn / n;

			a[i] = wyn;
		} else {				/* ustalanie kolejnych wartości ai */

			for(j = 1; j <= n; j++) {
				wyn += pts.y[j - 1] * cos((2 * M_PI * i * j)/n);
			}

			wyn = 2 * wyn / n;
			a[i] = wyn;
		}

	}

	return a;
}

double *licz_wartosci_wspolczynnikow_bi(points_t pts) {
	int n = pts.n;
	int j = 1;
	int i;
	double wyn;
	double *b = NULL;
	int m = 0;
	
	char *mEnv= getenv( "APPROX_BASE_SIZE" );

	if( mEnv != NULL && (( atoi( mEnv ) > 0 ) && ( atoi ( mEnv ) < (n-1)/2) ) ) {
		m = atoi( mEnv );
	} else {
		m = ((n-1)/2) - 1;
	}

	for(i = 0; i < m; i++) {

		wyn = 0;				/* konieczne wyzerowanie wartości wyn do poprawnego obliczania współczynnika */

		if(i == 0) {
			b = malloc(m*sizeof(double));
			for(j = 1; j <= n; j++) {
				wyn += pts.y[j - 1];
			}

			wyn = wyn / n;

			b[i] = wyn;

		} else {
			
			for(j = 1; j <= n; j++) {
				wyn += pts.y[j - 1] * sin((2 * M_PI * i * j)/n);
			}

			wyn = 2 * wyn / n;

			b[i] = wyn;
		}

	}

	return b;
}

double licz_wartosci_y(points_t pts, double x, double *licz_wartosci_wspolczynnikow_ai, double *licz_wartosci_wspolczynnikow_bi) {	/*trzeba wywołać razem z wartościami x, inaczej wyniki będą złe */
	int n = pts.n;
	int m;
	double y = 0;
	int i;

	char *mEnv= getenv( "APPROX_BASE_SIZE" );

	if( mEnv != NULL && (( atoi( mEnv ) > 0 ) && ( atoi ( mEnv ) < (n-1)/2) ) ) {
		m = atoi( mEnv );
	} else {
		m = ((n-1)/2) - 1;
	}
	
	y += licz_wartosci_wspolczynnikow_ai[0]; /*dodanie do y wartości a0 */

	for(i = 1; i <= m; i++) {
		y += (licz_wartosci_wspolczynnikow_ai[i] * (cos(2*M_PI*i/n*(x+1)))) + (licz_wartosci_wspolczynnikow_bi[i] * (sin(2*M_PI*i/n*(x+1))));
	}
	return y;
}
