westeros:
	gcc -o westeros westeros.c test.c stephen.c westeros.h

run: westeros
	./westeros ec=false

runec: westeros
	./westeros ec=true

clean:
	rm -f westeros

unswap:
	rm *.swp
