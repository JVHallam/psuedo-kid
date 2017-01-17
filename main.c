#include <stdio.h>
#include <stdlib.h>

#define COLUMN 1
#define ROW 2
#define CHAMBER 3
#define CELL 4

typedef int BOOL;
#define TRUE 1;
#define FALSE 0;

/*
	0  1  2		3  4  5		6  7  8
	9  10 11	12 13 14	15 16 17 
	18 19 20	21 22 23 	24 25 26

	27 28 29	30 31 32	33 34 35
	36 37 38	39 40 41 	42 43 44
	45 46 47	48 49 50	51 52 53

	54 55 56	57 58 59	60 61 62
	63 64 65	66 67 68	69 70 71
	72 73 74	75 76 77	78 79 80

	
	=-=-=-Tested functions=-=-=-
	These functions work fine, assuming given legal input.
	No error checking has been done, to check legal input.
		grid_traverse

		get_area_start

		get_area

		is_present

		is_appropriate

		solve_area

		compute_board

	=-=-=-To Test =-=-=-

		is_full


*/

/*=-=-=-Traversing Functions.=-=-=-*/

/*Choice being column, row, chamber, cell*/
int* grid_traverse(int choice, int index, int* grid_start){
	/*int* destination = grid_start;*/
	int row_start, column_start, *destination = grid_start;

	switch(choice){
		case COLUMN:
			destination += index;
			break;

		case ROW:
			destination += (index * 9);
			break;

		case CHAMBER:
			row_start = (index / 3) * 27;
			column_start = (index % 3) * 3;
			destination += row_start;
			destination += column_start;
			break;

		case CELL:
			destination += index;
			break;
	}
	return destination;
}

/*Is called inside of get_area*/
int* get_area_start(int* current_cell, int choice, int* grid_start){

	int cell_index = current_cell - grid_start;

	int column_index = cell_index % 9;
	int row_index = cell_index / 9;
	int chamber_index = ((row_index / 3) * 3) + (column_index / 3);

	int *area_start = 0;

	switch(choice){
		case COLUMN:
			area_start = grid_traverse(choice, column_index, grid_start);
			break;

		case ROW:
			area_start = grid_traverse(choice, row_index, grid_start);
			break;

		case CHAMBER:
			area_start = grid_traverse(choice, chamber_index, grid_start);
			break;
	}

	return area_start;
}


/*All calls of get_area use calloc, therefore a partnering free must be called.*/
int** get_area(int *cell, int choice, int *grid_start){
	int **container_area = (int**)calloc(9, sizeof(int*));
	int **container_pointer = container_area;
	/*
	*	We have to get the start of the area.
	*	Then, we have to increment over that area, copying each cell into the container_area.
			use the double forloop system that we developed for the previous project.
	*		
	*	

		here's what the notes say:
											-
			-				-				|
			|get pa value 	| -> do 3 times	|
			|pa += main  	|				|
			-				-				| -> do 3 times.	
											|
			pa += secondary value			|
											-

		Have pA = start of area.
		return_area[0] = pA, where return_area is an array of pointers.

		increment pA by the main value (which will be 1 or 9);

		Do this 3 times.

		increment pA by the secondary value (which can be 1, 9, or 6);

	Do this entire thing, 3 times, retruning 9 entries.
	*/

	int *cell_pointer = get_area_start(cell, choice, grid_start);

	int main_increment = 0, secondary_increment = 0;

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

			*container_pointer = cell_pointer;
			++container_pointer;
			cell_pointer += main_increment;
		}

		cell_pointer += secondary_increment;
	}

	return container_area;
}

/*=-=-=-=-Logical Analysis Functions=-=-=-*/

/*Return true if a value is present in an area*/
BOOL is_present(int value, int **area){
	for(int area_index = 0; area_index < 9; ++area_index){
		if(**area == value){
			return TRUE;
		}
		++area;
	}
	return FALSE;
}

/*Function does not take into account if a cell is already a non zero value.*/
BOOL is_appropriate(int *cell, int value, int* grid_start){
	BOOL is_cell_appropriate = TRUE;
	for(int choice = 1; choice <= 3; ++choice){

		int **area = get_area(cell, choice, grid_start);

		BOOL is_value_present = is_present(value, area);

		free(area);

		if(is_value_present){
			is_cell_appropriate = FALSE;
			break;
		}
	}
	return is_cell_appropriate;
}

/*Should Be set to return TRUE if a value was changed, FALSE if not.*/
BOOL solve_area(int *cell, int choice, int* grid_start){
	int **area = get_area(cell, choice, grid_start);
	BOOL is_changed = FALSE;

	for(int value = 1; value <= 9; ++value){
		/*
			For each value, from 1 to 9
			Go over the area and find how many appropriate spots there are for the value.
			If there is only a single spot, that spot is to be equal to that value.

			Reset the value of value to 1, each time a spot is filled, as the newly filled spot
			may effect if a new spot is able to be calculated.
		*/
		if(is_present(value, area)){
			continue;
		}

		else{
			int *appropriate_cell = 0;
			
			for(int **cell_ptr = area; cell_ptr < (area + 9); ++cell_ptr){
				
				if(**cell_ptr == 0 && is_appropriate(*cell_ptr, value, grid_start)){
				
					if(appropriate_cell == 0){
						appropriate_cell = *cell_ptr;
					}
				
					else{
						appropriate_cell = 0;
						break;
					}

				}
			}

			if(appropriate_cell != NULL){
				*appropriate_cell = value;
				is_changed = TRUE;
			}
		}
	}

	free(area);
	area = 0;
	return is_changed;
}

BOOL is_full(int **area){
	for(int **cell_ptr = area; cell_ptr < (area + 9); ++cell_ptr){
		if(**cell_ptr == 0){
			return FALSE;
		}
	}
	return TRUE;
}

/*Returns true, if all grid values are non-zero*/
/*
BOOL is_complete(int *grid_start){
	for(int chamber_index = 0; chamber_index < 9; ++chamber_index){
		int *cell = grid_traverse(CHAMBER, chamber_index, grid_start);


	}
}
*/

void compute_board(int *grid_start){
	/*Until a loop over has made no changes, continue to call solve_area*/

	BOOL is_changed = TRUE;

	while(is_changed){
		is_changed = FALSE;

		for(int choice = 1; choice <= 3; ++choice){

			for(int area_index = 0; area_index < 9; ++area_index){
				int *cell_ptr =  grid_traverse(choice, area_index, grid_start);

				BOOL outcome = solve_area(cell_ptr, choice, grid_start);

				if(!is_changed){
					is_changed = outcome;
				}
			}
		}
	}
}

int main(){
	int grid[9][9] = {
		{ 3, 7, 6,		4, 9, 1,		2, 0, 0 }, //0
		{ 2, 0, 0,		0, 0, 0,		0, 0, 1 }, //1
		{ 0, 0, 5,		0, 2, 0,		4, 6, 0 }, //2

		{ 9, 6, 0,		8, 0, 0,		0, 0, 7 }, //3
		{ 0, 0, 3,		0, 0, 0,		5, 0, 0 }, //4
		{ 1, 0, 0,		0, 0, 2,		0, 9, 4 }, //5

		{ 0, 2, 7,		0, 1, 0,		8, 0, 0 }, //6
		{ 4, 0, 0,		0, 0, 0,		0, 0, 6 }, //7
		{ 0, 0, 1,		2, 4, 3,		9, 7, 5 }, //8
	};

	compute_board(&grid[0][0]);
	
	printf("Solve_area has completed\n");

	return 0;
}