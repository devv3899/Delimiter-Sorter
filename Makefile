all: first

first: pointersorter.c
	gcc -O -g -o pointersorter pointersorter.c

clean:
	rm -rf pointersorter 

