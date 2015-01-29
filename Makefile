aprox: main.o splines.o points.o aproksymator_na_bazie.o gaus/libge.a
	$(CC) -o aprox  main.o splines.o points.o aproksymator_na_bazie.o -L gaus -l ge

aprox_tryg: main_tryg.o points.o trygonometrycznie/trygonometrycznie.o
	$(CC) -o aprox_tryg  main_tryg.o points.o trygonometrycznie/trygonometrycznie.o -lm

trygonometrycznie.o: makespl.h points.h
	$(CC) -I gaus -c trygonometrycznie/trygonometrycznie.o

intrp: main.o splines.o points.o interpolator.o gaus/libge.a
	$(CC) -o intrp  main.o splines.o points.o interpolator.o -L gaus -l ge

prosta: main.o splines.o points.o prosta.o
	$(CC) -o prosta  main.o splines.o points.o prosta.o	

aproksymator_na_bazie.o: makespl.h points.h gaus/piv_ge_solver.h
	$(CC) -I gaus -c aproksymator_na_bazie.c

interpolator.o: makespl.h points.h gaus/piv_ge_solver.h
	$(CC) -I gaus -c interpolator.c




.PHONY: clean

clean:
	-rm *.o trygonometrycznie/*.o aprox intrp prosta aprox_tryg
