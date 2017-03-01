int* parse_file_to_grid(FILE* fp){

	int* grid = (int*)calloc(81, sizeof(int));
	int* grid_pointer = grid;

	int cell_counter = 0;

	for(int c = 0; (c = fgetc(fp)) != EOF;){
		if(c != '\n' && c != ' '){
			/*
				This is a minor hack to convert ascii numbers into their integer
				counterparts, as atoi wouldn't conform.
			*/
			int d = c - '0'; 

			//If it's valid
			if( (d >= 0 && d <= 9) && (cell_counter < 81)){
				*(grid_pointer++) = d;
				++cell_counter;
			}
			else{
				free(grid);
				printf("d: %i\n", d);
				grid = NULL;
				break;
			}
		}
	}

	if(cell_counter != 81 && grid != NULL){
		free(grid);
		char* exact_error = (cell_counter > 81) ? "more" : "less";
		printf("There are %s than 81 cell values\n", exact_error);
		grid = NULL;
	}

	return grid;
}

/*
	if file contains 81 numbers only.
	return pointer to 9 x 9 array.
	else: return null
*/
int* parse_file_to_grid(FILE* fp){
	int* board = (int*)calloc(81, sizeof(int));
	int* grid_pointer = grid;
	int cell_counter = 0;

	for(int input = 0; (input = fgetc(fp)) != EOF;){
		if(c != '\n' && c != ' '){
			//Minor hack to convert ascii number characters to their integer counterparts.
			int current_char = input - '0';

			if((current_char >= 0 && current_char <= 9) && (cell_counter < 81)){
				*(grid_pointer++) = current_char;
				++cell_counter;
			}
			else{
				//file format invalid.
				if(current_char < 0 || current_char > 9){
					printf("Invalid character '%c' present\n", input);
				}
				else{
					puts("More than 81 valid characters present.");
				}
				free(board);
				board = NULL;
				break;
			}
		}
	}
	return board;
}