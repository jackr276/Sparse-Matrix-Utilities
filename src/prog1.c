/**
 * @Author: Jack Robbins
 * Homework 3, problem 1
 */

#include <stdio.h>
#include <string.h>

/*
 * The main(and only) function in this program opens a file, and reads
 * the unsigned integers in the file into Compressed Sparse Row(CSR) format
 * for a sparse matrix, writing this form to a text file
 */
int main(int argc, char** argv){
	//If no file is given, print error and return
	if(argc < 2 || strlen(argv[1]) == 0){
		printf("No input file given.");
		return 1;
	}
	
	//Open the file passed in
	FILE* fl = fopen(argv[1], "rb");
	
	//Check to see if file was actually opened
	if(fl == NULL){
		printf("File could not be opened");
		return 1;
	}

	//Matrix file is full of unsigned ints, 4 bytes each
	unsigned int r, c, i;

	//Read the number of rows in the matrix(first int)
	fread(&r, 1, sizeof(r), fl);
	//Read the number of columns in the matrix(second int)
	fread(&c, 1, sizeof(c), fl);
	
	//using compressed sparse row format(CSR)
	//We can safely assume that the matrix is 50% 0's
	int numInts = r * c * 0.5;
	unsigned int values[numInts], column_indices[numInts], row_start[r+1];

	//Count the number of nonzero elements
	int numNonZero = 0;
	//Keep an unsigned int for comparison
	unsigned int uZero = 0;

	//We will use these pointers to go through the arrays
	unsigned int* valPtr = values;
	unsigned int* colPtr = column_indices;

	//Go through the matrix symbolically
	for(int row = 0; row < r; row++){
		//Record the rowstart index
		row_start[row] = row;

		for(int col = 0; col < c; col++){
			//read an unsigned int into i
			fread(&i, 1, sizeof(i), fl);
			
			//If we encounter a nonzero element
			if(i != uZero){
				numNonZero++;

				//save the value
				*valPtr = i;
				valPtr++;

				//save the column index
				*colPtr = col;
				colPtr++;
			}
		}
	}

	//The last item in rowstart is the number of nonzero elements
	row_start[r] = numNonZero; 
	//close the file once we are done
	fclose(fl);

	//Sparse matrix is now deciphered, write to a new file
	FILE* f = fopen("matrix.txt", "w+");
	
	//Let the user know if there was an error creating file
	if(f == NULL){
		printf("Output file could not be created");
		return 1;
	}

	//Print the matrix dimensions
	fprintf(f, "dimensions %u %u\n", r, c);

	//Print all values to file
	fprintf(f, "%s", "values");

	for(int i = 0; i < numNonZero; i++){
		fprintf(f, " %u", values[i]);
	}
	
	//Print all column indices to file
	fprintf(f, "\ncolumn_indices");
	for(int i = 0; i < numNonZero; i++){
		fprintf(f, " %u", column_indices[i]);
	}

	//Print all row indices to file
	fprintf(f, "\nrow_start");
	
	for(int i = 0; i < r + 1; i++){
		fprintf(f, " %u", row_start[i]);
	}
	fprintf(f, "\n");
	//Close the file once printing is done
	fclose(f);
}
