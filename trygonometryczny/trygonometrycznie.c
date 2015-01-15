#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265



/* na podstawie http://kik.weii.tu.koszalin.pl/aproksymacja/aproks_tryg/page_dyp/aproksytr1.htm */

void drukuj_tablice (float tablica[], int n) {
   int i;
   for( i = 0; i < n; i++ ) {
      printf( "%f\t", tablica[i] );
   }
   printf( "]\n" );
}

float licz_a0 (float tablica[], int n) {

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


double licz_ai (float tablica [], int n, int m, int i) {		/*TODO: funkcja licząca każdy współczynnik i wypisująca go do pliku */
	
	float a [1000];
	int j = 0;
	float wyn [1000];
	FILE *fwyrz = fopen ("dane_ai", "w");
	i = 0;
	
	for (i = 1; i < m; i++) {
		for (j = 1; j < n; j++)	{
			wyn [j] = (tablica[j] * cos (PI*j*i/n));
		}
		j = j;
		a[i] = 2 * wyn[j] / n;
	}

	for (i = 1; i < n; i++) {
		fprintf (fwyrz, "%f ", a[i]);
	} 
		
}

/* double licz_bn () {			TODO: funkcja licząca każdy współczynnik i wypisujaca go do pliku

} */


int main (int argc, char * argv[]) {
	int n = 25;	/* liczba punktów TODO: algorytm liczący liczbę punktów w pliku */
	int m;	/* stopień wielomianu trygonometrycznego; musi spełniać warunek n>2m+1 TODO: algorytm obliczający m ze wzoru m=(n-1)/2 -1 */
	int i;	/* zmienna robocza */
	/*double x;
	double y; */

	m = ((n-1)/2) - 1;
 
	printf ("m = %d\n", m);

	FILE *in = fopen( argv[1], "r" );
	if (in == NULL) {
		printf ("Podaj proszę plik do wczytania przy uruchamianiu programu.\nUżycie: ./a.out <nazwa-pliku>\n");
		return -1;
	}

	float tablica[1000];  /* zakładam, że w pliku będzie max. 1000 liczb */

	i = 0;

	while( fscanf( in, "%f", &tablica[i] ) == 1 ) { /*pakuję dane do tablicy*/
		i++;
		}

	fclose( in );

	drukuj_tablice( tablica, i );

	licz_a0 (tablica, n);

	/*printf("a0 = %g\n", licz_a0(tablica, n)); */

	licz_ai (tablica, n, m, i);

   return EXIT_SUCCESS;
}
