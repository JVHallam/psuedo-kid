#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "psuedokid.h"

int main(){
	
	int* file_holder = parse_file_grid("abc.puzzle");

	compute_board(file_holder);

	for(int i = 0, *pGrid = file_holder; i < 81; ++i){
		if(i % 9 == 0){
			putchar('\n');
		}
		printf("%i", *(pGrid++));

	}
	putchar('\n');

	printf("Board solving has completed.\n");

	free(file_holder);

	return 0;
}
