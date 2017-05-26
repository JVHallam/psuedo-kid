#include "../include/porcelain.h"
#include "../include/minunit.h"
#include "../include/stdio.h"

int tests_run = 0;

static char* run_all_tests();


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
int main(){
	char* result = run_all_tests();

	if(result){
		printf("\n%s\n\n", result);
	}

	printf("Tests run: %i\n", tests_run);
	return result != 0;
}
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

static char* test_new_puzzle(){
	char* test_puzzle = "test/resources/valid1.puzzle";
	BOOL is_puzzle_added = new_puzzle(test_puzzle);

	mu_assert(\
		"A valid puzzle was not added.",\
		is_puzzle_added == TRUE
	);

	return 0;
}

//BOOL set_value(int choice, int choice_index, int cell_index, int value, char* key);
static char* test_set_value(){
	char* test_puzzle = "test/resources/only_zeroes.puzzle";

	if(new_puzzle(test_puzzle)){
		//Set the first cell to be 1.
		set_value(ROW, 0, 0, 1, test_puzzle);

	}
	else{
		return "Test puzzle wasn't added to the puzzle list.";
	}
}

/*
	Testing set value:
		Test that it can't take invalid:
			choice
			choice_index
			cell_index
			values
			keys

		Test that it can't change the value of an occupied cell

		Test that the value is no longer valid in any of the cells in the surrounding areas

		Test that it can't change the value of a cell it's not valid for.
*/	

static char* run_all_tests(){

	mu_run_test(test_new_puzzle);

	porcelain_cleanup();
	return 0;
}
