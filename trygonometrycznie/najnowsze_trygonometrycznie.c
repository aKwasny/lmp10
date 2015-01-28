#include "../points.h"
#include "najnowsze_trygonometrycznie.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* na podstawie http://kik.weii.tu.koszalin.pl/aproksymacja/aproks_tryg/page_dyp/aproksytr1.htm */


#define PI 3.14159265


/*int maxm (int n) { 
	if (n % 2 == 1) {
		return (n-1)/2-1;
	} else {
		return n/2-1;
	}
}*/

double *licz_a(points_t pts) {
	int n = pts.n;
	int j = 1;
	int i;
	double wyn;
	double *a = NULL;
	int m = 0;


	/*if (n % 2 == 1) {
		m = ((n-1)/2);
	} else {
		m = (n/2)-1;
	}*/

	m = ((n-1)/2) - 1;


	for(i = 0; i < m; i++) {

		wyn = 0;

		if(i == 0) {
			a = malloc(m*sizeof(double));	/* ustalanie wartości a0 */
			for(j = 1; j <= n; j++) {
				wyn += pts.y[j - 1] ;
			}

			wyn = wyn / n;

			a[i] = wyn;
		} else {

			for(j = 1; j <= n; j++) {
				wyn += pts.y[j - 1] * cos((2 * PI * i * j)/n);
			}

			wyn = 2 * wyn / n;
			a[i] = wyn;
		}

	}

	return a;
}

double *licz_b(points_t pts) {
	int n = pts.n;
	int j = 1;
	int i;
	double wyn;
	double *b = NULL;
	int m = 0;
	

	/*if (n % 2 == 1) {
		m = ((n-1)/2)-1;
	} else {
		m = (n/2)-1;
	}*/


	m = ((n-1)/2) - 1;

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
				wyn += pts.y[j - 1] * sin((2 * PI * i * j)/n);
			}

			wyn = 2 * wyn / n;

			b[i] = wyn;
		}

	}

	return b;
}

double y(points_t pts, double x, double *licz_a, double *licz_b) {			/*trzeba wywołać razem z wartościami x, inaczej wyniki będą złe */
	int n = pts.n;
	int m;
	double y = 0;
	int i;

	if (n % 2 == 1) {
		m = ((n-1)/2)-1;
	} else {
		m = (n/2)-1;
	}
	
	y += licz_a[0]; /*dodanie do y wartości a0 */

	for(i = 1; i <= m; i++) {
		y += (licz_a[i] * (cos(2*PI*i/n*x))) + (licz_b[i] * (sin(2*PI*i/n*x)));
	}

	return y;
}