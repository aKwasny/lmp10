#ifndef TRYGONOMETRYCZNIE_H_
#define TRYGONOMETRYCZNIE_H_

double *licz_wartosci_wspolczynnikow_ai (points_t pts);

double *licz_wartosci_wspolczynnikow_bi (points_t pts);

double licz_wartosci_y (points_t pts, double x, double *licz_wartosci_wspolczynnikow_ai, double *licz_wartosci_wspolczynnikow_bi);

#endif
