#include <stdlib.h>
#include <stdio.h>
#include "measurements.h"
#include <string.h>
int main(){
	char command[50];
	strcpy(command, "/home/alexstolt/memory_alloc/exec");
	printf("Total Allocated Memory: %ld\n", slob_get_total_alloc_mem());
	printf("Total Free Memory: %ld Bytes\n", slob_get_total_free_mem());

	for(int i = 0; i < 25; i++){
		system(command);	
		printf("Total Allocated Memory: %ld\n", slob_get_total_alloc_mem());
		printf("Total Free Memory: %ld Bytes\n", slob_get_total_free_mem());
	}	
	return 0;
}
