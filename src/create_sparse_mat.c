/**
 * Author: Jack Robbins
 * This simple program creates a sparse matrix in a binary file, according to
 * the user's specification
 */

#include <stdio.h>
#include <stdlib.h>
//Include time for randomness
#include <string.h>
#include <time.h>

int main(int argc, char** argv){
	//rows and columns are to be provided by the user
	unsigned int rowNum, colNum;
	//Define ratio as 0.2
	float ratio= 0.2;

	if(argc < 3 || strlen(argv[1]) == 0 || strlen(argv[2]) == 0) {
		printf("Error: Invalid number of arguments or invalid arguments\n");
		return 1;
	}

	//Grab the rowNum and colNum from the command line
	rowNum = atoi(argv[1]);
	colNum = atoi(argv[2]);

	//Create a binary file matrix.bin
	FILE* fl = fopen("matrix.bin", "wb");

	//If we can't create the file, exit the program
	if(fl == NULL){
		printf("File creation failed\b");
		return 1;	
	}

	//As our standard, rowNum and colNum are the first two ints in the file
	fwrite(&rowNum, sizeof(unsigned int), 1, fl);	
	fwrite(&colNum, sizeof(unsigned int), 1, fl);

	//Set the RNG seed using current time
	srand(time(NULL));

	unsigned int value;

	//Use a double for loop to keep track of how much we need to write
	for(unsigned int i = 0; i < rowNum; i++){
		for(unsigned int j = 0; j < colNum; j++){
			//Here is our chance element, this won't happen very often
			//making our matrix sparse
			if((double)rand() / (double)RAND_MAX < ratio){
				value = rand();	
			} else {
				//Most of the time, value will be 0
				value = 0;
			}
			//Write the unsigned int into the file
			fwrite(&value, sizeof(unsigned int), 1, fl);
		}
	}

	//We are done writing the file now
	fclose(fl);
	printf("Sparse matrix created successfully in: 'matrix.bin'\n\n");

	return 0;
}

