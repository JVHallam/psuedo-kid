#include "../include/hash_table.h"
#include "../include/minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
	Notes - Tests left to write:
		The table:
			We can use it:
				> Collision handling is occuring when needed
			

*/

int tests_run = 0;

static char* test_new_table();

static char* test_table_storage();

static char* test_multiple_grid_storage();

static char* run_all_tests();

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
int main(){
	const char* result = run_all_tests();

	if(result){
		printf("\n\n%s\n", result);
	}

	printf("tests run: %i\n", tests_run);
	return result != 0;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

static char* test_new_table(){
	grid_table* test_table = new_grid_table();

	mu_assert("Table pointer is null", test_table != 0);

	//> The key list is empty before use
	mu_assert("Key_list* keys is null", test_table->keys != 0);

	mu_assert(\
		"Key list is not empty",\
		(test_table->keys->head == 0 && test_table->keys->tail == 0)
	);

	//> The table is empty before use
	mu_assert("table's array pointer is null!", test_table->value_array != 0);

	for(\
		value_node** array_ptr = test_table->value_array;
		array_ptr < (test_table->value_array + DEFAULT_ARRAY_SIZE);
		++array_ptr
	){
		mu_assert(\
			"Values in the table aren't initialised to 0",\
			*array_ptr == 0
		);
	}

	free_table(test_table);
	return 0;
}

//BOOL add_to_table(const char* key, cell** grid_to_add, grid_table* target_table);
static char* test_table_storage(){

	cell** second_level = parse_file_to_grid("test/resources/valid1.puzzle");

	grid_table* test_table = new_grid_table();
	const char* test_key = "my key";

	//Add the value to the table.
	add_to_table(test_key, second_level, test_table);

	//> The key list is storing the values
	//The key list should be empty before hand. so head and tail should point to it.

	mu_assert("The key isn't being stored.", (test_table->keys->head) != 0);

	mu_assert(\
		"The key isn't being stored correctly!",\
		(strcmp(test_table->keys->head->key, test_key) == 0)
	);

	mu_assert(\
		"Head and tail should be the same when there is one value in the list",\
		test_table->keys->head == test_table->keys->tail
	);

	//Cycle along the table and find if it's there.
	//> The values are in the table when stored
	BOOL value_found = FALSE;
	for(\
		value_node** value_ptr = test_table->value_array;\
		value_ptr < (test_table->value_array + DEFAULT_ARRAY_SIZE);\
		++value_ptr
	 ){
		if(*value_ptr){
			value_found = TRUE;

			//(*value_ptr)->key is the same as test key.
			mu_assert(\
				"The stored key and the test key are different.",\
				(strcmp((*value_ptr)->key, test_key) == 0)
			);

			//check that (*value_ptr)->grid == second_level;
			mu_assert(\
				"The stored cell** differs after storage",\
				(*value_ptr)->grid == second_level
			);
		}
	}

	mu_assert("Nothing was found in the table.", value_found == TRUE);

	//cell** get_from_table(const char* key, grid_table* target_table);
	//> we can get the values out when needed

	
	cell** value_from_table = get_from_table(test_key, test_table);

	mu_assert("Value gotten from table is null.", value_from_table != 0);

	mu_assert(\
		"Value from table is not the value stored.",\
		value_from_table == second_level
	);
	
	free_table(test_table);
	return 0;
}

static char* test_multiple_grid_storage(){
	/*
		We need to make sure that we can store and use multiple grids at once.
		Then free the board.

		Create 4 different grids.
		Store them.
		call them.
	*/

	grid_table* grid_holder = new_grid_table();

	//cell** parse_file_to_grid(char* file_name);
	char* key_list[] = {
		"test/resources/valid1.puzzle",
		"test/resources/valid2.puzzle",
		"test/resources/is_present_chamber_test.puzzle",
		"test/resources/only_zeroes.puzzle"
	};

	cell** test_puzzles[] = {
		parse_file_to_grid(key_list[0]),
		parse_file_to_grid(key_list[1]),
		parse_file_to_grid(key_list[2]),
		parse_file_to_grid(key_list[3])
	};

	for(int i = 0; i < 4; ++i){
		add_to_table(key_list[i], test_puzzles[i], grid_holder);
	}

	//Then retrieve each puzzle and compare them to their stored counterparts.

	for(int i = 0; i < 4; ++i){
		//Get the grid from the table.
		//cell** get_from_table(const char* key, grid_table* target_table);
		cell** retrieved_grid = get_from_table(key_list[i], grid_holder);
		mu_assert("Retrieved grid isn't correct.", *retrieved_grid == *(test_puzzles[i]) );

		cell** retrieved_ptr = retrieved_grid;
		cell** actual_grid = test_puzzles[i];
		//Fun little test where we compare the 2 grids.
		for(int i = 0; i < 81; ++i){
			mu_assert(\
				"The stored and retrieved grids have differing cells.",\
				*(retrieved_ptr++) == *(actual_grid++)
			);
		}
	}

	//Let's just double check that we only have 4 grids in our table.
	//value_node** value_array
	int grid_count = 0;
	for(\
		value_node** array_ptr = grid_holder->value_array;\
		array_ptr < (grid_holder->value_array + grid_holder->size);
		++array_ptr
	){
		if(*array_ptr){
			++grid_count;
			//Check that it's one of our values
			BOOL is_puzzle_in_test_list = FALSE;
			for(\
				cell*** test_puzzles_ptr = test_puzzles;\
				test_puzzles_ptr < &(test_puzzles[4]);
				++test_puzzles_ptr
			){
				if( (*array_ptr)->grid == *test_puzzles_ptr ){
					is_puzzle_in_test_list = TRUE;
				}
			}
			mu_assert("Value found is not one of our test puzzles", is_puzzle_in_test_list);
		}
	};
	mu_assert("There are more than 4 grids in the table.", grid_count == 4);
	
	/*
		Make a change to one of our test puzzles and double check that that is also happening
		inside the one in the table. Just for kicks.
	*/

	cell** changes_test = test_puzzles[0];
	(*changes_test)->value = 100;
	cell** grid_from_table = get_from_table(key_list[0], grid_holder);
	mu_assert(\
		"The changed value isn't being reflected in the stored table.",\
		(*grid_from_table)->value == 100
	);

	/*
		Double check that the change didn't happen to any of the other puzzles.
	*/
	for(int i = 1; i <= 3; ++i){
		cell** actual_puzzle = test_puzzles[i];
		cell** new_check = get_from_table(key_list[i], grid_holder);
		
		mu_assert(\
			"Actual puzzle's value was changed to 100 when it shouldn't have",\
			(*actual_puzzle)->value != 100
		);

		mu_assert(\
			"Puzzle from the table's value was changed to 100 when it shouldn't have",\
			(*new_check)->value != 100
		);
	}

	free_table(grid_holder);
	return 0;
}

static char* test_collision_handling(){
	/*
		Force a collision by setting the table size to 1
		Make sure it handles it correctly.
	*/
	//uint32_t FNV32(const char *s)

	/*
		Set table size to 1.

		Store 3 values in the table

		Recall all 3, again, without issues.
	*/
	grid_table* grid_holder = new_grid_table();

	grid_holder->size = 1;

	char* key_list[] = {
		"test/resources/valid1.puzzle",
		"test/resources/valid2.puzzle",
		"test/resources/is_present_chamber_test.puzzle",
		"test/resources/only_zeroes.puzzle"
	};

	cell** test_puzzles[] = {
		parse_file_to_grid(key_list[0]),
		parse_file_to_grid(key_list[1]),
		parse_file_to_grid(key_list[2]),
		parse_file_to_grid(key_list[3])
	};

	//It will crash here if there is no code to handle collisions.
	for(int i = 0; i < 4; ++i){
		add_to_table(key_list[i], test_puzzles[i], grid_holder);

		//First value in the table:
		const char* first_value = (*(grid_holder->value_array))->key;
		printf("First Values key: %s\n", first_value);
	}

	for(int i = 0; i < 4; ++i){
		cell** retrieved_from_table = get_from_table(key_list[i], grid_holder);

		mu_assert(\
			"Retrieved value doesn't match stored value",\
			retrieved_from_table == test_puzzles[i]
		);
	}

	free_table(grid_holder);
	return 0;
}

static char* test_key_handling(){

	return 0;
}

static char* test_duplicate_key_handling(){

	return 0;
}

static char* run_all_tests(){

	mu_run_test(test_new_table);
	mu_run_test(test_table_storage);
	mu_run_test(test_multiple_grid_storage);
	mu_run_test(test_collision_handling);
	//mu_run_test(test_key_handling);

	return 0;
}