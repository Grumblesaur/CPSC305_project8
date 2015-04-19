westeros: westeros.o test.o stephen.o
	gcc -o westeros westeros.h westeros.c test.c stephen.c

clean:
	rm *.o westeros

unswap:
	rm *.swp
