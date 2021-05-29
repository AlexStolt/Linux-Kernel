exec: slob_test.o libmeasurements.a libmemory.a
	gcc slob_test.o -L. -lmeasurements -lmemory -o exec

slob_test.o: slob_test.c
	gcc -c slob_test.c -o slob_test.o

libmemory.a: allocate_mem.o deallocate_mem.o
	ar rcs libmemory.a allocate_mem.o deallocate_mem.o

allocate_mem.o: allocate_mem.c
	gcc -c allocate_mem.c -o allocate_mem.o

deallocate_mem.o: deallocate_mem.c
	gcc -c deallocate_mem.c -o deallocate_mem.o

libmeasurements.a: slob_get_total_alloc_mem.o slob_get_total_free_mem.o
	ar rcs libmeasurements.a slob_get_total_alloc_mem.o slob_get_total_free_mem.o

slob_get_total_alloc_mem.o: slob_get_total_alloc_mem.c
	gcc -c slob_get_total_alloc_mem.c -o slob_get_total_alloc_mem.o

slob_get_total_free_mem.o: slob_get_total_free_mem.c
	gcc -c slob_get_total_free_mem.c -o slob_get_total_free_mem.o

clean:
	rm *.o *.a
