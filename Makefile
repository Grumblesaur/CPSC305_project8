westeros: westeros.o stephen.o test.o
	gcc -o westeros westeros.o stephen.o test.o

westeros.o: westeros.c westeros.h
	gcc -c westeros.c

stephen.o: stephen.c westeros.h
	gcc -c stephen.c

test.o: test.c westeros.h
	gcc -c test.c

run: westeros
	./westeros ec=false

runec: westeros
	./westeros ec=true

clean:
	rm -f westeros

unswap:
	rm *.swp
