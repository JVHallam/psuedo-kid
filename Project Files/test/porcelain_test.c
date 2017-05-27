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
		const int valid_choice = ROW;
		const int valid_choice_index = 0;
		const int valid_cell_index = 0;
		const int valid_value = 1;

		int invalid_choice[2] = {0, 5};
		int invalid_choice_index[2] = {-1, 9};
		int invalid_cell_index[2] = {-1, 9};
		int invalid_value[2] = {0, 10};
		char* invalid_keys[2] = {
			0,
			"garbage"
		};

		//Valid everything first:
		BOOL is_all_valids_valid = FALSE;

		is_all_valids_valid = set_value(valid_choice, valid_choice_index, valid_cell_index, \
										valid_value, test_puzzle);

		mu_assert(\
			"Returning false, even when all values are valid.",\
			is_all_valids_valid == TRUE
		);

		//test that choice can't take values outside of 1 - 4
		BOOL is_invalid_choice_allowed = TRUE;

		for(int i = 0; i < 2; ++i){
			is_invalid_choice_allowed = set_value(	invalid_choice[i], valid_choice_index, \
													valid_cell_index, valid_value, \
													test_puzzle);

			mu_assert(\
				"set value is allowing invalid choices",\
				is_invalid_choice_allowed == FALSE
			);
		}

		//test that choice_index can't take values outside of 0 - 8
		BOOL is_invalid_choice_index_allowed = TRUE;

		for(int i = 0; i < 2; ++i){
			is_invalid_choice_index_allowed = set_value(valid_choice, \
														invalid_choice_index[i], \
														valid_cell_index, valid_value, \
														test_puzzle);

			mu_assert(\
				"Invalid choice index is allowed",\
				is_invalid_choice_index_allowed == FALSE
			);
		}

		//test that cell_index can't take values outside of 0 -8
		BOOL is_invalid_cell_index_allowed = TRUE;

		for(int i = 0; i < 2; ++i){
			is_invalid_cell_index_allowed = set_value(	valid_choice, valid_choice_index,\
														invalid_cell_index[i], valid_value, \
														test_puzzle);

			mu_assert(\
				"Invalid cell indexes are allowed.",\
				is_invalid_cell_index_allowed == FALSE
			);
		}

		//test that value can't be outside of 1 - 9
		BOOL is_invalid_value_allowed = TRUE;

		for(int i = 0; i < 2; ++i){
			is_invalid_value_allowed = set_value( 	valid_choice, valid_choice_index, \
													valid_cell_index, invalid_value[i],\
													test_puzzle);

			mu_assert(\
				"Invalid values are allowed",\
				is_invalid_value_allowed == FALSE
			);
		}

		//Test that it returns false if key isn't valid
		BOOL is_invalid_key_allowed = TRUE;

		for(int i = 0; i < 2; ++i){
			is_invalid_key_allowed = set_value(valid_choice, valid_choice_index, \
												valid_cell_index, valid_value, \
												invalid_keys[i]);

			mu_assert(\
				"Invalid keys are allowed",\
				is_invalid_key_allowed == FALSE
			);
		}

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

/*
BOOL set_value(int choice, int choice_index, int cell_index, int value, char* key);

int get_value(int choice, int choice_index, int cell_index, char* key);
*/
static char* test_get_value(){
	char* test_puzzle = "test/resources/test_get_value.puzzle";

	if(new_puzzle(test_puzzle)){
		for(int cell_index = 0; cell_index < 9; ++cell_index){
			int value = cell_index + 1;

			set_value(CHAMBER, 0, cell_index, value, test_puzzle);

			int received_value = get_value(CHAMBER, 0, cell_index, test_puzzle);

			if(received_value){
				mu_assert(\
					"Set value and recieved value are different.",\
					value == received_value
				);
			}
			else{
				return "received_value is coming back null, after being set.";
			}
		}
	}

	return 0;
}

/*
	#define ROW 1
	#define COLUMN 2
	#define CHAMBER 3
*/
static char* test_is_value_present(){
	char* puzzle_keys[3] = {
		"test/resources/is_present_row_test.puzzle",
		"test/resources/is_present_column_test.puzzle",
		"test/resources/is_present_chamber_test.puzzle"
	};

	for(int choice_type = 1; choice_type <= 3; ++choice_type){
		int puzzle_index = choice_type - 1;

		char* current_puzzle = puzzle_keys[puzzle_index];

		if(new_puzzle(current_puzzle)){
			for(int area_index = 0; area_index < 9; ++area_index){
				for(int value = 1; value <= 9; ++value){
					BOOL was_value_present = is_value_present(	choice_type, area_index, \
																value, current_puzzle);

					if(value == (area_index + 1)){
						mu_assert(\
							"Value was found to be present, even though it shouldn't",\
							was_value_present == FALSE
						);
					}
					else{
						mu_assert(\
							"Value was not found, even though it should be.",\
							was_value_present == TRUE
						);
					}
				}
			}
		}
		else{
			return "Valid puzzle couldn't be added to the puzzle list.";
		}
	}
	return 0;
}

//This test needs finishing, see the comment at the end of the function.
static char* test_is_value_valid(){

	/*
		Have a zero grid.
		All values should be valid.

		set cell 0 to 1.
		cell 1 should not be allowed 1, but be allowed 2.

		cell 2 should not be allowed < 2, but be allowed 3.

		cell 3 should not be allowed valued < 3, but be allowed 4.

		cell n should not be allowed values < n, but be allowed n + 1.
	*/

	//All of these are zero grids.
	char* puzzle_keys[3] = {
		"test/resources/test_is_value_valid_rows.puzzle",
		"test/resources/test_is_value_valid_columns.puzzle",
		"test/resources/test_is_value_valid_chambers.puzzle"
	};

	for(int puzzle_index = 0; puzzle_index < 3; ++puzzle_index){
		char* puzzle_key = puzzle_keys[puzzle_index];

		if(new_puzzle(puzzle_key)){
			int area_index = 0;
			int choice = puzzle_index + 1;
			/*
				For each cell in the area:
					Check that the cell can't hold any number below
					It's (index + 1). E.g.:
						cell of index 6 (the 7th cell in the row) can't hold 1 - 6.
						But it can hold 7. So set it's value to 7.

					Then finally, set it's value to it's index + 1.
			*/
			for(int cell_index = 0; cell_index < 9; ++cell_index){
				BOOL was_value_valid = FALSE;

				for(int value = 0; value <= cell_index; ++value){
					//We're checking that the current cell can't hold any of the previous
					//Values.
					was_value_valid = is_value_valid(	choice, area_index, cell_index, \
														value, puzzle_key);

					mu_assert(\
						"Value was found to be valid, when it should not be.",\
						was_value_valid == FALSE
					);
				}

				//Check that the cell CAN hold cell_index + 1;
				int new_value = cell_index + 1;
				was_value_valid = is_value_valid(	choice, area_index, cell_index, \
													new_value, puzzle_key);

				mu_assert(\
					"is_value_valid is returning false, when the value"\
					"isn't already in the area.",\
					was_value_valid == TRUE
				);

				BOOL was_value_set = set_value(	choice, area_index, cell_index,\
												new_value, puzzle_key);

				mu_assert(\
					"New value wasn't set, even though it was a valid value.",\
					was_value_set == TRUE
				);

				/*
					Finally, check that all other cells in the other areas (if row, 
					check the columns and chambers cells) have had their valid values for
					the new_value, set to FALSE.
				*/

			}
		}
		else{
			return "Puzzle was not added. Even though it was valid.";
		}
	}
	return 0;
}

static char* run_all_tests(){

	mu_run_test(test_new_puzzle);
	mu_run_test(test_set_values_input_validation);
	mu_run_test(test_set_value);
	mu_run_test(test_get_value);
	mu_run_test(test_is_value_present);
	//This test works and runs, but is not comprehensive.
	//See the comment at the end of the function.
	mu_run_test(test_is_value_valid);
	
	porcelain_cleanup();
	return 0;
}

