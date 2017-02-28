#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "psuedokid.h"

int main(int argc, char** argv){
	if(argc > 1){
		FILE* fp = fopen(*(++argv), "r");

		if(fp){
			int* board = parse_file_to_grid(fp);
			fclose(fp);

			if(board != NULL){
				compute_board(board);

				for(int i = 0, *pGrid = board; i < 81; ++i){
					if(i % 9 == 0){
						putchar('\n');
					}
					printf("%i", *(pGrid++));

				}
				free(board);
				printf("\n");
			}

			else{
				perror("File not correctly formatted.");
				exit(1);
			}

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
