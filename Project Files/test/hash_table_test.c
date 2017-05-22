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

char* test_keys_array[] = {
	"test/resources/valid1.puzzle",
	"test/resources/valid2.puzzle",
	"test/resources/is_present_chamber_test.puzzle",
	"test/resources/only_zeroes.puzzle"
};

cell** test_puzzles_array[4] = {0, 0, 0, 0};

	
const int test_list_size = 4;

grid_table* initialise_grid_table();

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

void initalise_test_puzzles_array(){
	for(int i = 0; i < 4; ++i){
		test_puzzles_array[i] = parse_file_to_grid(test_keys_array[i]);
	}
}

grid_table* create_table_with_test_values(){
	grid_table* current_table = new_grid_table();

	for(int i = 0; i < test_list_size; ++i){
		add_to_table(test_keys_array[i], test_puzzles_array[i], current_table);
	}

	return current_table;
}

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

		mu_assert(\
			"The first value in the chain has been changed, when it should remain the same.",\
			(strcmp((*(grid_holder->value_array))->key, key_list[0]) == 0)
		);
	}

	/*
		go to the grid
		check the first node's key is what it should be.
	*/

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

static char* test_duplicate_key_handling(){
	grid_table* grid_holder = new_grid_table();

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
	}

	//Try to add duplicates into the table:
	for(int j = 0; j < 2; ++j){
		for(int i = 0; i < 4; ++i){
			BOOL is_added = add_to_table(key_list[i], test_puzzles[i], grid_holder);
			mu_assert(\
				"It shouldn't be allowing duplicates to be added.",\
				is_added == FALSE
			);
		}
	}
	
	//Now count the keys:
	int key_count = 0;
	key_node* walker = grid_holder->keys->head;

	while(walker) {
		++key_count;
		walker = walker->next;
	}

	mu_assert(\
		"Key count isn't 4, as expected.",\
		key_count == 4
	);

	//Check for duplicate keys.

	key_node* primary_walker = grid_holder->keys->head;

	while(primary_walker){
		key_node* secondary_walker = primary_walker->next;
		
		while(secondary_walker){
			BOOL are_keys_the_same = (strcmp(primary_walker->key, secondary_walker->key) == 0);

			mu_assert(\
				"Duplicate keys found in the key list",\
				are_keys_the_same == FALSE
			);

			secondary_walker = secondary_walker->next;
		}

		primary_walker = primary_walker->next;
	}

	//Finally, check that there are only 4 puzzles on the value_array
	int puzzle_counter = 0;
	value_node** array_walker = grid_holder->value_array;

	for(int i = 0; i < grid_holder->size; ++i){
		//If we find a puzzle.
		if(*array_walker){
			value_node* chain_walker = *array_walker;
			while(chain_walker){
				++puzzle_counter;
				chain_walker = chain_walker->next;
			}
		}
		++array_walker;
	}
	
	mu_assert(\
		"The correct number of puzzles weren't found to be stored in the grid.",\
		puzzle_counter == 4
	);

	return 0;
}



static char* test_key_handling(){
	/*
		Add all puzzles to the table

		Check that there's only 4 keys.

		Check that only the keys we've given it are there.

		Check that all of our keys are there.
	*/
	grid_table* grid_holder = new_grid_table();

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
		BOOL is_added = add_to_table(key_list[i], test_puzzles[i], grid_holder);
		mu_assert(\
			"Valid key-value pair hasn't been added",
			is_added == TRUE
		);
	}

	//Check all of our test values have been added.
	int key_counter = 0;
	key_node* key_walker = grid_holder->keys->head;
	while(key_walker){
		++key_counter;
		key_walker = key_walker->next;
	}

	mu_assert(\
		"Incorrect number of keys found",\
		key_counter == 4
	);

	//Double check that all of the values in our array are in our list
	for(int i = 0; i < 4; ++i){
		char* current_key = key_list[i];

		BOOL is_current_key_present = FALSE;

		key_walker = grid_holder->keys->head;
		while(key_walker){
			if(strcmp(current_key, key_walker->key) == 0){
				is_current_key_present = TRUE;
				break;
			}
			key_walker = key_walker->next;
		}
		mu_assert(\
			"Key that should have been added was not found.",\
			is_current_key_present == TRUE
		);
	}

	//Double check that the list only contains keys that are in our array.
	key_walker = grid_holder->keys->head;

	while(key_walker){
		//For each key, check it's in there.
		BOOL is_key_in_array = FALSE;

		for(int i = 0; i < 4; ++i){
			if(strcmp(key_list[i], key_walker->key) == 0){
				is_key_in_array = TRUE;
				break;
			}
		}

		mu_assert(\
			"Key in the key list was not found in the array.",\
			is_key_in_array == TRUE
		);

		key_walker = key_walker->next;
	}

	return 0;
}

static char* run_all_tests(){
	initalise_test_puzzles_array();

	//Testing to make sure that a new table has all of it's values nulled.
	mu_run_test(test_new_table);

	//Make sure it can store values
	mu_run_test(test_table_storage);
	mu_run_test(test_multiple_grid_storage);
	mu_run_test(test_collision_handling);
	mu_run_test(test_duplicate_key_handling);
	mu_run_test(test_key_handling);

	return 0;
}