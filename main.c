#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "psuedokid.h"


/*
	Take commandline arguements, to file that needs to be solved.

	Take that arg, open the file.

	If there's a file, parse it into a grid.
*/




int main(int argc, char** argv){
	if(argc > 1){
		FILE* fp = fopen(*(++argv), "r");

		if(fp){
			int* board = parse_file_to_grid(fp);

			fclose(fp);

			compute_board(board);

			for(int i = 0, *pGrid = board; i < 81; ++i){
				if(i % 9 == 0){
					putchar('\n');
				}
				printf("%i", *(pGrid++));

			}
			free(board);
		}
		else{
			perror("File not found");
		}
	}
	else{
		puts("No arguements given.");
	}
	return 0;
}
