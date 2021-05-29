exec: main.o libmemory.a
	gcc main.o -L. -lmemory -o exec	

main.o: main.c 
	gcc -c main.c -o main.o

libmemory.a: allocate_mem.o deallocate_mem.o
	ar rcs libmemory.a allocate_mem.o deallocate_mem.o

allocate_mem.o: allocate_mem.c
	gcc -c allocate_mem.c -o allocate_mem.o   

deallocate_mem.o: deallocate_mem.c
	gcc -c deallocate_mem.c -o deallocate_mem.o

clean:
	rm *.o *.a
