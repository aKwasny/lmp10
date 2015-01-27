aprox: main.o points.o trygonometrycznie/najnowsze_trygonometrycznie.o
	$(CC) -o aprox  main.o points.o trygonometrycznie/najnowsze_trygonometrycznie.o -lm -ggdb

trygonometrycznie.o: makespl.h points.h
	$(CC) -I gaus -c trygonometrycznie/najnowsze_trygonometrycznie.c -ggdb


.PHONY: clean

clean:
	-rm *.o aprox
