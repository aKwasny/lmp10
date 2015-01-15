aprox: main.o splines.o points.o trygonometrycznie/trygonometrycznie.o gaus/libge.a
	$(CC) -o aprox  main.o splines.o points.o trygonometrycznie/trygonometrycznie.o -L gaus -l ge

intrp: main.o splines.o points.o interpolator.o gaus/libge.a
	$(CC) -o intrp  main.o splines.o points.o interpolator.o -L gaus -l ge

prosta: main.o splines.o points.o prosta.o
	$(CC) -o prosta  main.o splines.o points.o prosta.o	

trygonometrycznie.o: makespl.h points.h gaus/piv_ge_solver.h
	$(CC) -I gaus -c trygonometrycznie/trygonometrycznie.c

interpolator.o: makespl.h points.h gaus/piv_ge_solver.h
	$(CC) -I gaus -c interpolator.c

.PHONY: clean

clean:
	-rm *.o aprox intrp prosta
