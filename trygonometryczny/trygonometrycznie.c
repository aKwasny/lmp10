#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265


/* na podstawie http://kik.weii.tu.koszalin.pl/aproksymacja/aproks_tryg/page_dyp/aproksytr1.htm */

void drukuj_tablice (float tablica[], int n) {
   int i;
	printf( "Wczytane dane to:\n[");
   for( i = 0; i < n; i++ ) {
      printf( "%f\t", tablica[i] );
   }
   printf( "]\n" );
}


float licz_a0 (float tablica[], int n) { /*TODO: Poprawić liczenie współczynnika - zamiast -6,5 ma wychodzić -6,4.*/

	int i;
	float a0 = 0;
	float suma = 0;
	
	for (i = 1; i < n; i++) {
		suma += tablica [i];
	}

	a0 = suma/n;
	
	printf ("suma = %f\n", suma);
	printf ("a0 = %f\n", a0);

	return a0;
}


float licz_ai (float tablica [], int n, int m, int i) {
	
	float a [1000];
	int j = 0;
	float wyn = 0;
	FILE *fwyrz1 = fopen ("dane_ai", "w");

	i = 0;

	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++)	{
			wyn += (tablica[j-1] * cos(2*PI*j*i/n));
		}
		a[i] = 2 * wyn / n;
		wyn = 0;
	}
	
	for (i = 1; i <= m; i++) {
		fprintf (fwyrz1, "%f ", a[i]);
	} 

	return a[i];
		
}

float licz_bi (float tablica [], int n, int m, int i) {

	float b [1000];
	int j = 0;
	float wyn = 0;
	FILE *fwyrz2 = fopen ("dane_bi", "w");
	i = 0;

	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) {
			wyn += (tablica[j-1] * sin(2*PI*j*i/n));
		}	
	b[i] = 2 * wyn / n;
	wyn = 0;
	}

	for (i = 1; i <= m; i++) {
		fprintf (fwyrz2, "%f ", b[i]);
	}

	return b[i];
}


/*void make_spl(points_t * pts, spline_t * spl){

	matrix_t *eqs= NULL;
	double *x = pts->x;
	double *y = pts->y;
	double	a = x[0];
	double	b = x[pts->n - 1];
	int	i, j, k;
	int	nb = pts->n - 3 > 10 ? 10 : pts->n - 3;
	char *nbEnv= getenv( "APPROX_BASE_SIZE" );
	if( nbEnv != NULL && atoi( nbEnv ) > 0 ) {
		nb = atoi( nbEnv );
	}
	eqs = make_matrix(nb, nb + 1);
} 
*/

int main (int argc, char * argv[]) {
	int n = 25;	/* liczba punktów TODO: algorytm liczący liczbę punktów w pliku */
	int m;	/* stopień wielomianu trygonometrycznego; musi spełniać warunek n>2m+1 */
	int i;	/* zmienna robocza */

	if (n % 2 == 1) {
		m = (n-1)/2-1;
	} else {
		m = n/2-1;
	}

	printf ("m = %d\n", m);

	FILE *in = fopen( argv[1], "r" );
	if (in == NULL) {
		printf ("Podaj proszę plik do wczytania przy uruchamianiu programu.\nUżycie: ./a.out <nazwa-pliku>\n");
		return -1;
	}

	float tablica[1000];

	i = 0;

	while( fscanf( in, "%f", &tablica[i] ) == 1 ) { /*pakuję dane do tablicy*/
		i++;
		}

	fclose( in );

	drukuj_tablice( tablica, i );

	licz_a0 (tablica, n);

	/*printf("a0 = %g\n", licz_a0(tablica, n)); */

	licz_ai (tablica, n, m, i);

	licz_bi (tablica, n, m, i);

   return EXIT_SUCCESS;
}
