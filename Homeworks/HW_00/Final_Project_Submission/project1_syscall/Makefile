output: find_roots_lib.o libroots.a
	gcc find_roots_lib.o -Wall -L. -lroots -o output

find_roots_lib.o: find_roots_lib.c
	gcc -c find_roots_lib.c -o find_roots_lib.o -Wall

libroots.a: roots.o
	ar rcs libroots.a roots.o

roots.o: roots.c roots.h
	gcc -c roots.c -o roots.o -Wall

clean: 
	rm *.o *.a output
