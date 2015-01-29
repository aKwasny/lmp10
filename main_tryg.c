#include "points.h"
#include "trygonometrycznie/trygonometrycznie.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>



/*od aKwasny: zmienione teksty i nazwy niektórych zmiennych na język polski, ponieważ zwiększało to komfort mojej pracy */

char *uzycie =
		"Użycie: (opcjonalnie APPROX_BASE_SIZE=m) %s -p plik-z-punktami -g plik-gnuplot (wyjście) -o od_x -d do_x -n n_punktów\n"
		"            Jeżeli plik z punktami został podany to\n"
		"               czyta z niego\n"
		"               - liczba punktów powinna wynosić >= 4\n"
		"            endfi\n"
		"            Jeżeli dany jest plik-gnuplot to\n"
		"               program tworzy tabelę n-punktów z zakresu <od_x , do_x>\n"
		"               - od_x - pierwsza dana z pliku z punktami do aproksymacji\n"
		"               - do_x - jako ostatnia dana do aproksymacji\n"
		"               - n-punktów domyślnie 100\n"
		"               - n-punktów musi być > 1\n"
		"            Jeżeli zdefiniowano m w APPROX_BASE_SIZE to taka będzie liczba funkcji bazowych.\n"
		"               Domyślnie m jest definiowane w programie na podstawie algorytmu m = ((n-1)/2) - 1 (gdzie n - liczba punktów w pliku p).\n"
		"            endif\n";

int main (int argc, char **argv) {
	int opt;								
	char *in = NULL;
	char *gnuplot = NULL;
	double odX = 0;
	double doX = 0;
	int n = 100; 	/* domyślne ustawienie potrzebne do działania programu */
	double *dane_a = NULL;
	double *dane_b = NULL;

	points_t pts;
	pts.n = 0;

	if (argv[1] == NULL) {
		fprintf (stderr, uzycie, argv[0]);
	}

	while ((opt = getopt (argc, argv, "p:g:o:d:n:")) != -1) { 		/* opcje działanie + zapisywanie wyborów użytkownika */
		switch (opt) {
		case 'p':
			in = optarg;
			break;
		case 'g':
			gnuplot = optarg;
			break;
		case 'o':
			odX = atof (optarg);
			break;
		case 'd':
			doX = atof (optarg);
			break;
		case 'n':
			n = atoi (optarg);
			break;
		default:
			fprintf (stderr, uzycie, argv[0]);
			return EXIT_FAILURE;
		}
	}


	if( optind < argc ) {							
		fprintf( stderr, "\nPodano złe parametry!\n" );
		for( ; optind < argc; optind++ )
			fprintf( stderr, "\t\"%s\"\n", argv[optind] );
		fprintf( stderr, "\n" );
		fprintf( stderr, uzycie, argv[0] );
		return EXIT_FAILURE;
	}


	if (in != NULL) {
		FILE *inf = fopen (in, "r");
		if (inf == NULL) {
			fprintf (stderr, "%s: brak możliwości czytania pliku z danymi: %s\n\n", argv[0], in);
			return EXIT_FAILURE;
		}

		if (read_pts_failed (inf, &pts)) {
			fprintf (stderr, "%s: nieprawidłowa zawartość pliku z danymi: %s\n\n", argv[0], in);
			return EXIT_FAILURE;
		}
		else
			fclose (inf);		


										/*od tego miejsca program "na nowo" */

		if (n > 1 && gnuplot != NULL) {					/* Sprawdzanie czy było żądanie wykresu + ew. rysowanie*/

			FILE *plik_gnuplota = fopen (gnuplot, "w");

			double przetworzony_zakres;					/*wzięte z oryginalnej wersji, delikatnie zmienione; dobrze działa z nową wersją */
			int i = 0;

			przetworzony_zakres = (doX-odX)/(n-1);			
			
			if( doX == 0 && odX == 0 ) { 				/* obliczanie wykresu */
				if( pts.n > 1 ) {
					odX= pts.x[0];
					doX= pts.x[pts.n-1];
				} else {
					odX= 1;
					doX= 2;
				}
			}	
			
			if (plik_gnuplota == NULL) {
				printf ("Nie można stworzyć gnuplot'owego pliku: %s\n\n", gnuplot);
				return EXIT_FAILURE;
			}
	
			dane_a = licz_wartosci_wspolczynnikow_ai(pts);
			dane_b = licz_wartosci_wspolczynnikow_bi(pts);

			for (i = 0; i < n; i++) {
				fprintf (plik_gnuplota, "%f\t%f\n", (odX+i*przetworzony_zakres), licz_wartosci_y(pts, odX + i*przetworzony_zakres, dane_a, dane_b));
			}
			
			fclose (plik_gnuplota);
		}
	}
	return EXIT_SUCCESS;
}
