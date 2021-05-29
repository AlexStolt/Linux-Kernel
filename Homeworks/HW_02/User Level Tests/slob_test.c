//********************************************//
//          ECE318 Operating Systems          //
//                                            //
//                Assignment 3                //
//                                            //
//         Linux SLOB Memory allocator        //
//           First Fit VS Best Fit            //
//                                            //
// Date: 18/05/2021                           //
//                                            //
// Authors:                                   //
// Kyritsis Spyridon 2697                     //
// Stoltidis Alexandros 2824                  //
// Koutsoukis Nikolaos 2907                   //
//********************************************//

#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "measurements.h"

// The program takes 2 arguments total number of iterations and max           //
// allocation size. If any of the 2 specified arguments does not exist both   //
// get their default parameters.                                              //
int main(int argc, char *argv[])
{
  int i, j;
  int total_iterations;
  int max_allocation_size;
  int block_size;
  int free_table_size;
  int free_table_index;
  void **free_ptr_array;
  void *ret_ptr;
  long page_mem = 0;
  long unused_page_mem = 0;
  double ratio = 0.0;

  srand(1000);

  // Argument parsing //
  if (argc == 3)
    {
      total_iterations = atoi(argv[1]);
      max_allocation_size = atoi(argv[2]);

      printf("Number of total iterations: %d\n Max allocation block: %d\n\n", total_iterations, max_allocation_size);
    }
  else
    { 
      total_iterations = 25;
      max_allocation_size = 1000;      
     
      printf("*** Default arguments ***\nNumber of total iterations: %d\nMax allocation block: %d\n\n", total_iterations, max_allocation_size);
    }

  // Initializing the free pointer array //
  free_table_size =  total_iterations / 4;
  free_table_index = 0;
  free_ptr_array = (void **) calloc(free_table_size, sizeof(void *));

  // Main loop that all //
  for (i = 0; i < total_iterations; i++)
    {
      block_size = (rand() % max_allocation_size) + 1;

      // kmalloc syscall //
      ret_ptr = (void *) allocate_mem(block_size);
      
	  page_mem = slob_get_total_alloc_mem();
	  unused_page_mem = slob_get_total_free_mem();
	  ratio = (double) unused_page_mem / (double) page_mem;

      fprintf(stderr, "page_mem %ld\tunused_mem %ld\tratio %lf\n", page_mem, unused_page_mem, ratio);

      printf("Allocating %d bytes...\nret_ptr = %p\n", block_size, ret_ptr);
	  
      if (free_table_index == free_table_size)
        {
          for (j = 0; j < free_table_size; j++)
            {
              // free syscall //
              printf("Freeing ptr = %p\n", free_ptr_array[j]);

			  	  
			  
			  deallocate_mem(free_ptr_array[j]);
			  page_mem = slob_get_total_alloc_mem();
			  unused_page_mem = slob_get_total_free_mem();
              ratio = (double) unused_page_mem / (double) page_mem;
			  fprintf(stderr, "page_mem %ld\tunused_mem %ld\tratio %lf\n", page_mem, unused_page_mem, ratio);	
              free_ptr_array[j] = NULL;
            }

          free_table_index = 0;
        }

      // Placing kmalloc pointer to the free_ptr_array //
      free_ptr_array[free_table_index] = ret_ptr;
      free_table_index++;
    }

  // Freeing leftover pointers //
  for (j = 0; j < free_table_index; j++)
    {
      // free syscall //
      printf("Freeing ptr = %p\n", free_ptr_array[j]);

	  
      deallocate_mem(free_ptr_array[j]);
	  page_mem = slob_get_total_alloc_mem();
      unused_page_mem = slob_get_total_free_mem();
      ratio = (double) unused_page_mem / (double) page_mem;
      fprintf(stderr, "page_mem %ld\tunused_mem %ld\tratio %lf\n", page_mem, unused_page_mem, ratio);

      free_ptr_array[j] = NULL;
    }

  free(free_ptr_array);
}

