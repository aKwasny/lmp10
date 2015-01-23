#include "../points.h"
#include "najnowsze_trygonometrycznie.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define PI 3.14159265


int maxm (int n) { 
	if (n % 2 == 1) {
		return (n-1)/2-1;
	} else {
		return n/2-1;
	}
}

double *licz_a(points_t pts) {
	int n = pts.n;
	int j = 1;
	int i;
	double *t;
	double wyn;
	double *a = NULL;


	for(i = 0; i < n; i++) {
		wyn = 0;

		if(i == 0) {
			a = malloc(sizeof(double));
			for(j = 1; j <= n; j++) {
				wyn += pts.y[j - 1];
			}

			wyn = wyn / n;

			a[i] = wyn;
		} else {
			t = realloc( a, (i+1) * sizeof(double));
			if(t != NULL) {
				a = t;
			}

			for(j = 0; j <= n; j++) {
				wyn += pts.y[j - 1] * cos(2 * PI * i * j/n);
			}

			wyn = wyn / 2*n;
			a[i] = wyn;
		}

	}

	return a;
}

double *licz_b(points_t pts) {
	int n = pts.n;
	int j = 1;
	int i;
	double *t;
	double wyn;
	double *b = NULL;


	for(i = 0; i < n; i++) {

		wyn = 0;

		if(i == 0) {
			b = malloc(sizeof(double));
			for(j = 1; j <= n; j++) {
				wyn += pts.y[j - 1];
			}

			wyn = wyn / n;

			b[i] = wyn;
		} else {
			t = realloc( b, (i+1) * sizeof(double));
			if(t != NULL) {
				b = t;
			}
			for(j = 0; j <= n; j++) {
				wyn += pts.y[j - 1] * sin(2 * PI * i * j/n);
			}

			wyn = wyn / 2*n;
			b[i] = wyn;
		}

	}

	return b;
}

double y(points_t pts, double x, double *licz_a, double *licz_b, int maxm) {
	int n = pts.n;
	int m;
	double y = 0;
	int i;

	if(maxm == 0) {
		maxm = m;
	}

	y += licz_a[0];

	for(i = 1; i <= m; i++) {
		y += licz_a[i] * (cos(2*PI*i/n)*x) + licz_b[i] * (sin(2*PI*i/n)*x);
	}

	return y;
}
