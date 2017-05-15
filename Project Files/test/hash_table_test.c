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

			We can free it:
				> call free on it
*/

int tests_run = 0;

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
	cell* first_level = new_cell();
	cell** second_level = &first_level;
	grid_table* test_table = new_grid_table();
	const char* test_key = "my key";

	first_level->value = 10;
	first_level->occupied = 1;

	//Add the value to the table.
	add_to_table(test_key, second_level, test_table);

	//> The key list is storing the values
	//The key list should be empty before hand. so head and tail should point to it.

	mu_assert("The key isn't being stored.", test_table->keys->head != 0);

	mu_assert(\
		"The key isn't being stored correctly!",\
		strcmp(test_table->keys->head->key, test_key)
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
				strcmp((*value_ptr)->key, test_key)
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

static char* run_all_tests(){

	mu_run_test(test_new_table);
	mu_run_test(test_table_storage);

	return 0;
}