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
static char* test_set_values_input_validation(){
	char* test_puzzle = "test/resources/set_values_input_validation.puzzle";

	if(new_puzzle(test_puzzle)){
		//test that choice can't take values outside of 1 - 4
		//test that choice_index can't take values outside of 0 - 8
		//test that cell_index can't take values outside of 0 -8
		//test that value can't be outside of 1 - 9
		//Test that it returns false if key isn't valid
	}
	else{
		return "Test puzzle couldn't be added to the puzzle list";
	}
	return 0;
}

static char* test_set_value(){
	char* test_puzzle = "test/resources/only_zeroes.puzzle";

	if(new_puzzle(test_puzzle)){

		int test_value = 1;

		//Set the first cell to be 1.
		mu_assert(\
			"Can't set the value of the first cell on an empty puzzle",\
			set_value(CHAMBER, 0, 0, test_value, test_puzzle) == TRUE
		);

		//Check we can't overwrite values.
		mu_assert(\
			"Able to set values of already set cells",\
			set_value(CHAMBER, 0, 0, 2, test_puzzle) == FALSE
		);

		//Check that we can't set any other values in the surrounding area to 1.
		for(int cell_index = 1; cell_index <= 8; ++cell_index){
			mu_assert(\
				"Able to make other values in the cells chamber the same as one another",\
				set_value(CHAMBER, 0, cell_index, test_value, test_puzzle) == FALSE
			);

			mu_assert(\
				"Able to make other values in the cells row the same as on another",\
				set_value(ROW, 0, cell_index, test_value, test_puzzle) == FALSE
			);

			mu_assert(\
				"Able to make other values in the cells column the same as on another",\
				set_value(COLUMN, 0, cell_index, test_value, test_puzzle) == FALSE
			);
		}

		print_grid(test_puzzle);
	}
	else{
		return "Test puzzle wasn't added to the puzzle list.";
	}

	return 0;
}

static char* run_all_tests(){

	mu_run_test(test_new_puzzle);
	mu_run_test(test_set_values_input_validation);
	mu_run_test(test_set_value);

	porcelain_cleanup();
	return 0;
}

