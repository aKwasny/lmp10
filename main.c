#include "points.h"
#include "trygonometrycznie/najnowsze_trygonometrycznie.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>


char *uzycie =
		"Użycie: %s -p plik-z-punktami -g plik-gnuplot (wyjście) -o od_x -d do_x -n n_punktów -m m_numer \n"
		"            Jeżeli plik z punktami został podany to\n"
		"               czyta z niego\n"
		"               - liczba punktów powinna wynosić >= 4\n"
		"            endfi\n"
		"            Jeżeli dany jest plik-gnuplot to\n"
		"               program tworzy tabelę n-punktów z zakresu <od_x,do_x>\n"
		"               - od_x domyślnie ustawiona w wartościach x jako pierwsza dana z pliku z punktami\n"
		"               - do_x domyślnie ustawiona w wartościach x jako ostatnia dana\n"
		"               - n-punktów domyślnie 100\n"
		"               - n-punktów musi być > 1\n"
		"            endif\n";

int main (int argc, char **argv) {
	int opt;								
	char *in = NULL;
	char *gnuplot = NULL;
	double odX = 0;
	double doX = 0;
	int n = 100;
	int m = 1;
	double *dane_a = NULL;
	double *dane_b = NULL;

	points_t pts;
	pts.n = 0;

	if (argv[0] == NULL) {
		fprintf (stderr, uzycie, argv[0]);
	}

	while ((opt = getopt (argc, argv, "p:s:g:f:t:n:m:")) != -1) { 		/* opcje działanie + zapisywanie wyborów użytkownika */
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
		case 'm':
			m = atoi (optarg);
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
			fprintf (stderr, "%s: can not read points file: %s\n\n", argv[0], in);
			return EXIT_FAILURE;
		}

		if (read_pts_failed (inf, &pts)) {
			fprintf (stderr, "%s: bad contents of points file: %s\n\n", argv[0], in);
			return EXIT_FAILURE;
		}
		else
			fclose (inf);		


										/*od tego miejsca program "na nowo" */

		if (n > 1 && gnuplot != NULL) {					/* Sprawdzanie czy było żądanie wykresu + ew. rysowanie*/

			FILE *plik_gnuplota = fopen (gnuplot, "w");

			double przetworzony_zakres;
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
	
			dane_a = licz_a(pts);
			dane_b = licz_b(pts);

			for (i = 0; i < n; i++) {
				fprintf (plik_gnuplota, "%f\t%f\n", (odX+i*przetworzony_zakres), y(pts, odX+i*przetworzony_zakres, dane_a, dane_b, m));
			}
			
		}
	}
	return EXIT_SUCCESS;
}
