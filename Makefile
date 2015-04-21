westeros: westeros.c stephen.c test.c
	gcc -o westeros westeros.c stephen.c test.c

run: westeros
	./westeros ec=false

runec: westeros
	./westeros ec=true

clean:
	rm -f westeros

unswap:
	rm *.swp
