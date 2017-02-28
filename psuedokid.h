#ifndef PSUEDOKID_H_
#define PSUEDOKID_H_

//Choices
#define COLUMN 1
#define ROW 2
#define CHAMBER 3
#define CELL 4

typedef int BOOL;
#define TRUE 1
#define FALSE 0

//Calls Calloc, returns a 9 x 9 int array representing the sudoku board.
int* parse_file_grid(char* file_path);

/*
	Traversing Functions
	All of these will return pointers to areas. Don't change that actual state of the board.
*/

//Traverse to the start of the choice, of index number "index".
int* grid_traverse(int choice, int index, int* grid_start);


//Return the pointer to the cell at the start of choice, in the current area.
int* get_area_start(int* current_cell, int choice, int* grid_start);


//Calls Calloc, creates a 9 x 1 array containing pointers to each cell in given area.
int** get_area(int *cell, int choice, int *grid_start);


/*
	Logical Analysis functions
	All of these are designed to logically analyse an area and change it based on the results.
*/

//Returns either TRUE or FALSE based on whether a value is present in an area.
BOOL is_present(int value, int **area);


//returns TRUE or FALSE based on whether a zero value is found in an area.
BOOL is_full(int **area);


//Return TRUE or FALSE based on whether a cell is suitable to hold a value.
BOOL is_appropriate(int *cell, int value, int* grid_start);


//Goes over an area, if it changes a value, it return TRUE. Else, returns false.
BOOL solve_area(int *cell, int choice, int* grid_start);


//Takes a pointer to a board and attempts to solve it to the best of the algorithm's abilites.
void compute_board(int *grid_start);


#endif