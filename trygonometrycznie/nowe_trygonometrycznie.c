#include "trygonometrycznie.h"
#include "../makespl.h"
#include "../points.h"
#include "../gaus/piv_ge_solver.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define PI 3.14159265

/* na podstawie http://kik.weii.tu.koszalin.pl/aproksymacja/aproks_tryg/page_dyp/aproksytr1.htm */



void drukuj_tablice (double tablica[], int n) {
   int i;
	printf( "Wczytane dane to:\n[");
   for( i = 0; i < n; i++ ) {
      printf( "%f\t", tablica[i] );
   }
   printf( "]\n" );
}



int main (int argc, char * argv[]) {
	int n = 0;	/* liczba punktów, czyli też elementów w tablicy */
	int m = 0;	/* stopień wielomianu trygonometrycznego; musi spełniać warunek n>2m+1*/
	int i = 0;
	double tablica [1024];
	double a0 = 0;
	double suma = 0;
	double a [1024];
	double b [1024];
	double y [1024];
	int j = 0;
	double wyn = 0;
	
	FILE *fwyrz1 = fopen ("wyniki", "w");
	
	FILE *in = fopen( argv[1], "r" );
	if (in == NULL) {
		printf ("Podaj proszę plik do wczytania przy uruchamianiu programu.\nUżycie: ./testy <nazwa-pliku>\n");
		return -1;
	}

	i = 0;

	while( fscanf( in, "%lf", &tablica[i] ) == 1 ) { /*pakuję dane do tablicy*/
		i++;
		n++;			/*liczę tutaj ile elementów spakowałem do tablicy*/
		}

	fclose (in);

	printf ("n = %d\n", n);

	if (n % 2 == 1) {
		m = (n-1)/2-1;
	} else {
		m = n/2-1;
	}

	printf ("m = %d\n", m);

	drukuj_tablice( tablica, i );

	i = 0;	
	for (i = 0; i < n; i++) {
		suma += tablica [i];
	}
	
	a0 = suma/n;
	
	/*printf ("suma = %f\n", suma);
	printf ("a0 = %f\n", a0);*/


	i = 0;					/*liczenie ai*/
	j = 0;
	wyn = 0;
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++)	{
			wyn += (tablica[j-1] * cos(2*PI*j*i/n));
		}
		a[i] = 2 * wyn / n;
		wyn = 0;
	}


	i = 0;					/*liczenie bi*/
	j = 0;
	wyn = 0;
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) {
			wyn += (tablica[j-1] * sin(2*PI*j*i/n));
		}	
	b[i] = 2 * wyn / n;
	wyn = 0;
	}


	i = 0;					/*liczenie y*/
	for (i = 1; i <= m; i++) {
		y[i] += a0 + (a[i]*cos(2*PI*i/n)) + (b[i]*sin(2*PI*i/n));
	}	

	i = 0;
	printf ("Obliczone x:\t Obliczone y:\n");
	for (i = 1; i <= m; i++) 		
		fprintf (stdout, "%d\t\t%f\n", i, y[i]);

   return EXIT_SUCCESS;
}


/*void
make_spl(points_t * pts, spline_t * spl)
{

	matrix_t       *eqs= NULL;
	double         *x = pts->x;
	double         *y = pts->y;
	double		a = x[0];
	double		b = x[pts->n - 1];
	int		i, j, k;
	int		nb = pts->n - 3 > 10 ? 10 : pts->n - 3;
  char *nbEnv= getenv( "APPROX_BASE_SIZE" );

	if( nbEnv != NULL && atoi( nbEnv ) > 0 )
		nb = atoi( nbEnv );

	eqs = make_matrix(nb, nb + 1);

#ifdef DEBUG
#define TESTBASE 500
	{
		FILE           *tst = fopen("debug_base_plot.txt", "w");
		double		dx = (b - a) / (TESTBASE - 1);
		for( j= 0; j < nb; j++ )
			xfi( a, b, nb, j, tst );
		for (i = 0; i < TESTBASE; i++) {
			fprintf(tst, "%g", a + i * dx);
			for (j = 0; j < nb; j++) {
				fprintf(tst, " %g", fi  (a, b, nb, j, a + i * dx));
				fprintf(tst, " %g", dfi (a, b, nb, j, a + i * dx));
				fprintf(tst, " %g", d2fi(a, b, nb, j, a + i * dx));
				fprintf(tst, " %g", d3fi(a, b, nb, j, a + i * dx));
			}
			fprintf(tst, "\n");
		}
		fclose(tst);
	}
#endif

	for (j = 0; j < nb; j++) {
		for (i = 0; i < nb; i++)
			for (k = 0; k < pts->n; k++)
				add_to_entry_matrix(eqs, j, i, fi(a, b, nb, i, x[k]) * fi(a, b, nb, j, x[k]));

		for (k = 0; k < pts->n; k++)
			add_to_entry_matrix(eqs, j, nb, y[k] * fi(a, b, nb, j, x[k]));
	}

#ifdef DEBUG
	write_matrix(eqs, stdout);
#endif

	if (piv_ge_solver(eqs)) {
		spl->n = 0;
		return;
	}
#ifdef DEBUG
	write_matrix(eqs, stdout);
#endif

	if (alloc_spl(spl, nb) == 0) {
		for (i = 0; i < spl->n; i++) {
			double xx = spl->x[i] = a + i*(b-a)/(spl->n-1);
			xx+= 10.0*DBL_EPSILON;  // zabezpieczenie przed ulokowaniem punktu w poprzednim przedziale
			spl->f[i] = 0;
			spl->f1[i] = 0;
			spl->f2[i] = 0;
			spl->f3[i] = 0;
			for (k = 0; k < nb; k++) {
				double		ck = get_entry_matrix(eqs, k, nb);
				spl->f[i]  += ck * fi  (a, b, nb, k, xx);
				spl->f1[i] += ck * dfi (a, b, nb, k, xx);
				spl->f2[i] += ck * d2fi(a, b, nb, k, xx);
				spl->f3[i] += ck * d3fi(a, b, nb, k, xx);
			}
		}
	}

#ifdef DEBUG
	{
		FILE           *tst = fopen("debug_spline_plot.txt", "w");
		double		dx = (b - a) / (TESTBASE - 1);
		for (i = 0; i < TESTBASE; i++) {
			double yi= 0;
			double dyi= 0;
			double d2yi= 0;
			double d3yi= 0;
			double xi= a + i * dx;
			for( k= 0; k < nb; k++ ) {
							yi += get_entry_matrix(eqs, k, nb) * fi(a, b, nb, k, xi);
							dyi += get_entry_matrix(eqs, k, nb) * dfi(a, b, nb, k, xi);
							d2yi += get_entry_matrix(eqs, k, nb) * d2fi(a, b, nb, k, xi);
							d3yi += get_entry_matrix(eqs, k, nb) * d3fi(a, b, nb, k, xi);
			}
			fprintf(tst, "%g %g %g %g %g\n", xi, yi, dyi, d2yi, d3yi );
		}
		fclose(tst);
	}
#endif

}*/
