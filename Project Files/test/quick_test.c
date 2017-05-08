#include <stdio.h>


int main(){

	for(int chamber_row = 0; chamber_row < 3; ++chamber_row){
		for(int row_in_chamber = 0; row_in_chamber < 3; ++row_in_chamber){
			for(int each_chamber = 0; each_chamber < 3; ++each_chamber){
				for(int i = 0; i < 3; ++i){

					int chamber_were_in = (chamber_row * 3) + each_chamber;

					int cell_index = (chamber_row * 27) + (row_in_chamber * 9) + (each_chamber * 3) + i;

					printf("Chamber_were_in = %i, cell_index = %i\n", chamber_were_in, cell_index);

				}
			}
		}
	}
	return 0;
}