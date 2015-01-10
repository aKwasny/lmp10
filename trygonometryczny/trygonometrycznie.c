#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/* na podstawie http://kik.weii.tu.koszalin.pl/aproksymacja/aproks_tryg/page_dyp/aproksytr1.htm */

void drukuj_tablice (double tablica[], int n) {
   printf( "Wczytane dane to:\n[ " );
   int i;
   for( i = 0; i < n; i++ ) {
      printf( "%g\t", tablica[i] );
   }
   printf( "]\n" );
}

double licz_a0 (double tab[], int n) {

	double		s = tab[0];

	while (--n) {
		s += tab[n];
	}

	double a;

	a = s/n;
	
	return a;
}



/*double sum_a0 (double tab[], int n) {
	j = 0;
	a0 = 0;
	double sum = 0;
	for (j=1; j<n, j++) {
		sum += ;
	}
}*/

int main (int argc, char * argv[]) {
	/*double a0;
	double ai;
	double bi;
	double n;*/	/* liczba punktów */
	/*double m;	 stopień wielomianu trygonometrycznego; musi spełniać warunek n>2m+1 */
	/*double x;
	double y; */
 

	FILE *in = fopen( argv[1], "r" );
	if (in == NULL) {
		printf ("Podaj proszę plik do wczytania przy uruchamianiu programu.\nUżycie: ./a.out <nazwa-pliku>\n");
		return -1;
	}

	double tablica[1000];  /* zakładam, że w pliku będzie max. 1000 liczb */

	int i = 0;

	while( fscanf( in, "%lf", &tablica[i] ) == 1 ) { /*pakuję dane do tablicy*/
		i++;
		}

	fclose( in );

	drukuj_tablice( tablica, i );

	printf("a0 = %g\n", licz_a0(tablica, i));

   return EXIT_SUCCESS;
}
