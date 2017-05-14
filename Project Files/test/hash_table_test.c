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

static char* run_all_tests(){
	mu_run_test(test_new_key_list);
	mu_run_test(test_new_key_node);

	return 0;
}