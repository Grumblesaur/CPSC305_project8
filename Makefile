westeros: westeros.o test.o stephen.o
	gcc -o westeros.h westeros.c test.c stephen.h

clean:
	rm *.o *.swp
