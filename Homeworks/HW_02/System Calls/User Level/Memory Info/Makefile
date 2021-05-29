exec: main.o libmeasurements.a
	gcc main.o -L. -lmeasurements -o exec	

main.o: main.c 
	gcc -c main.c -o main.o

libmeasurements.a: slob_get_total_alloc_mem.o slob_get_total_free_mem.o
	ar rcs libmeasurements.a slob_get_total_alloc_mem.o slob_get_total_free_mem.o

slob_get_total_alloc_mem.o: slob_get_total_alloc_mem.c
	gcc -c slob_get_total_alloc_mem.c -o slob_get_total_alloc_mem.o   

slob_get_total_free_mem.o: slob_get_total_free_mem.c
	gcc -c slob_get_total_free_mem.c -o slob_get_total_free_mem.o

clean:
	rm *.o *.a
