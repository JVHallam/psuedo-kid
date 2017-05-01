#include "../include/grid.h"
#include <stdio.h>

int main(int argc, char** argv){
	char* filename = *(argv + 1);

	cell** holder = parse_file_to_grid(filename);

	cell** grid_ptr = 0;

	if(holder != 0){
		grid_ptr = holder;
		for(int i = 0; i < 9; ++i){
			for(int j = 0; j < 9; ++j){
				printf("%i ", (*grid_ptr)->value);
				++grid_ptr;
			}
			printf("\n");
		}	
	}

	if(holder != 0){
		grid_ptr = holder;
		puts("Occupied:");
		for(int i = 0; i < 9; ++i){
			for(int j = 0; j < 9; ++j){
				printf("%i ", (*grid_ptr)->occupied);
				++grid_ptr;
			}
			printf("\n");
		}	
	}

	else{
		puts("holder is null");
	}

	return 0;
}