#include <stdlib.h>
#include "../include/constants.h"

int* grid_traverse(int choice, int index, int* grid_start){
	int *destination = grid_start;

	switch(choice){
		case COLUMN:
			destination += index;
			break;
		case ROW:
			destination += (index * 9);
			break;
		case CHAMBER:
			/*desination += (row chamber starts on ) + (column chamber starts on)*/
			destination += ((index / 3) * 27) + ((index % 3) * 3);
			break;

		case CELL:
			destination += index;
			break;
	}
	return destination;
}

//Is called inside of get_area
int* get_area_start(int* current_cell, int choice, int* grid_start){
	int cell_index = current_cell - grid_start;
	
	int choice_index = 0;

	switch(choice){
		case COLUMN:
			choice_index = cell_index % 9;
			break;

		case ROW:
			choice_index = cell_index / 9;
			break;

		case CHAMBER:
			
			//Remember, this is integer division. These can't be cancelled out.
			choice_index = (((cell_index / 27) * 3)) + ((cell_index % 9) / 3);
			break;
	}

	return grid_traverse(choice, choice_index, grid_start);
}


//get_area has calls to Calloc, must always be paired with free.
int** get_area(int *cell, int choice, int *grid_start){
	int **container_area = (int**)calloc(9, sizeof(int*));
	int **container_pointer = container_area;

	int *cell_pointer = get_area_start(cell, choice, grid_start);

	int main_increment = 0, secondary_increment = 0;
	/*
		Incrementing over a row or a column is 8 same equal steps.
		Incrementing over a chamber is 3 small steps, then a jump to the next row (6 cells).
	*/
	switch(choice){
		case COLUMN:
			main_increment = 9;
			break;

		case ROW:
			main_increment = 1;
			break;

		case CHAMBER:
			main_increment = 1;
			secondary_increment = 6;
			break;
	}


	for(int secondary_loop = 0; secondary_loop < 3; ++secondary_loop){
	
		for(int main_loop = 0; main_loop < 3; ++main_loop){

			*(container_pointer++) = cell_pointer;
			cell_pointer += main_increment;

		}

		cell_pointer += secondary_increment;
	}

	return container_area;
}