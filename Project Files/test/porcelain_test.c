#include <stdio.h>
#include <stdlib.h>
#include "../include/porcelain.h"
#include "../include/minunit.h"


int main(){
	key_list* grid_keys = new_key_list();
	grid_keys->head = new_key_node("test");

	free(grid_keys->head);
	free(grid_keys);

	puts("We're A okay!");
	return 0;
}