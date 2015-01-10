#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/* na podstawie http://kik.weii.tu.koszalin.pl/aproksymacja/aproks_tryg/page_dyp/aproksytr1.htm */

void czytaj (int argc, char *argv []) {
	FILE *in = argc > 1 ? fopen(argv[1], "r") : stdin;
	if( in == NULL ) {
		fprintf( stderr, "%s: Nie mogę czytać %s\n", argv[0], argv[1] );
		return EXIT_FAILURE;
   }
}

void pakuj_do_tablicy (int argc, char *argv []) {
	int tablica [1000];
	i = 0;
	int l;
	while( fscanf( &in, "%d", &l ) == 1 ) {
		tablica[i++]= l;
		}
}

void wypisz_tablice( int t[], int n ) {
	printf( "[ " );
	int i;
	i = 0;
	for( i = 0; i < n; i++ ) {
		printf( "%d\t", t[i] );
	}
	printf( "]\n" );
}

/*void sum_a0 () {
	j = 0;
	a0 = 0;
	double sum = 0;
	for (j=1; j<n, j++) {
		sum += ;
	}
}*/

int main (int argc, char * argv[]) {
	double a0;
	double ai;
	double bi;
	double n;	/* liczba punktów */
	double m;	/* stopień wielomianu trygonometrycznego; musi spełniać warunek n>2m+1 */
	double x;
	double y;
	int j;
	int i;

	czytaj ();

	pakuj_do_tablicy ();

	fclose (in);	

	wypisz_tablice (tablica, i);

	return EXIT_SUCCESS;
}
