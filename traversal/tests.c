#include "traversal.h"
#include <stdio.h>
#include "minunit.h"
#include "../constants/constants.h"

int tests_run = 0;

//int* grid_traverse(int choice, int index, int* grid_start)

/*
	#define COLUMN 1
	#define ROW 2
	#define CHAMBER 3
	#define CELL 4
*/

static int test_grid[9][9] = {
	{1,  2,  3,  4,  5,  6,  7,  8,  9},
	{10, 11, 12, 13, 14, 15, 16, 17, 18},
	{19, 20, 21, 22, 23, 24, 25, 26, 27},
	{28, 29, 30, 31, 32, 33, 34, 35, 36},
	{37, 38, 39, 40, 41, 42, 43, 44, 45},
	{46, 47, 48, 49, 50, 51, 52, 53, 54},
	{55, 56, 57, 58, 59, 60, 61, 62, 63},
	{64, 65, 66, 67, 68, 69, 70, 71, 72},
	{73, 74, 75, 76, 77, 78, 79, 80, 81}
};

static char* test_grid_traverse_column(){
	//0 -> 0 0
	//1 -> 1 0
	//2 -> 2 0

	for(int col_index = 0; col_index < 9; ++col_index){

		int* area_start = grid_traverse(COLUMN, col_index, &test_grid[0][0]);

		

		mu_assert("Error, test_grid_traverse_column not working correctly.",\
					area_start != test_grid[0][col_index]);
	}

	return "Yes";
}
/*
static * char test_grid_traverse_row(){

}

static * char test_grid_traverse_chamber(){

}
*/

int main(){

	
	int result =  mu_run_test(test_grid_traverse_column);

	test_grid_traverse_column();
	
	return result != 0;
}