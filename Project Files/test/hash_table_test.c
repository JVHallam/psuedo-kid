#include "../include/hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include "../include/minunit.h"
#include <string.h>

int tests_run = 0;

static char* run_all_tests();

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
int main(){
	char* result = run_all_tests();

	if(result){
		printf("\n\n%s\n", result);
	}

	printf("Tests run: %i\n", tests_run);
	return result != 0;
}
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

static char* test_new_key_list(){
	key_list* current_list = new_key_list();

	mu_assert("Pointer returned from new_key_list was null", current_list != 0);
	mu_assert("Head has not been initialised to null", current_list->head == 0);
	mu_assert("Tail has not been initialised to null", current_list->tail == 0);

	free(current_list);
	return 0;
}


static char* test_new_key_node(){
	const char* test_key = "test_key";
	key_node* current_node = new_key_node("test_key");

	mu_assert("new_key_node() has returned null", current_node != 0);

	mu_assert(\
		"current_node-> key is different from the test_key",\
		strcmp(current_node->key, test_key) == 0
	);

	mu_assert("The next pointer has not been initialised to null", current_node->next == 0);

	free(current_node);

	return 0;
}

//cell*** new_table_array(int table_size);
static char* test_new_table_array(){
	int table_size = 100;
	cell*** current_table = new_table_array(table_size);

	mu_assert("cell*** being returned from new_table_array is nulled.", current_table != 0);

	for(cell*** table_ptr = current_table; table_ptr < (current_table + table_size); ++table_ptr){
		mu_assert(\
			"Each value on the grid table hasn't been initialised to zero.",\
			*table_ptr == 0
		);
	}

	free(current_table);
	return 0;
}
//grid_table* new_grid_table();
static char* test_new_grid_table(){
	/*
		So, a grid table should:
			have a grid table of a specified size.

			have a key list, with a nulled head and tail.

			have a table_size member of the specified size
	*/
	int test_table_size = 100;
	grid_table* current_grid_table = new_grid_table(test_table_size);

	mu_assert(\
		"new_grid_table is returning a null pointer",\
		current_grid_table != 0
	);

	mu_assert(\
		"Table has been set to the wrong size.",\
		current_grid_table->table_size == test_table_size
	);

	mu_assert(\
		"table's key_list is null",\
		current_grid_table->keys != 0
	);

	mu_assert(\
		"table->key_list head or tail is not initialised to null",
		((current_grid_table->keys->head == 0) && (current_grid_table->keys->tail == 0))
	);

	//Check the grid_array has been set up
	mu_assert(\
		"grid_array for the table is null",\
		current_grid_table->grid_array != 0
	);

	//Cycle over the table, checking each value is null
	for(\
		cell*** grid_array_ptr = current_grid_table->grid_array;\
		grid_array_ptr < (current_grid_table->grid_array + current_grid_table->table_size);\
		++grid_array_ptr
	){
		mu_assert(\
			"Tables values haven't been initialised to zero",\
			*grid_array_ptr == 0
		);	
	}

	//Finally, free the table in use.
	free_grid_table(current_grid_table);
	return 0;
}

static char* run_all_tests(){
	mu_run_test(test_new_key_list);
	mu_run_test(test_new_key_node);
	mu_run_test(test_new_table_array);
	mu_run_test(test_new_grid_table);

	return 0;
}