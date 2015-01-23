aprox: main.o points.o trygonometrycznie/najnowsze_trygonometrycznie.o gaus/libge.a
	$(CC) -o aprox  main.o points.o trygonometrycznie/najnowsze_trygonometrycznie.o -lm -L gaus -l ge

trygonometrycznie.o: makespl.h points.h gaus/piv_ge_solver.h
	$(CC) -I gaus -c trygonometrycznie/najnowsze_trygonometrycznie.c


.PHONY: clean

clean:
	-rm *.o aprox
