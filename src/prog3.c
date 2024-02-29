/**
 * Author: Jack Robbins
 * Homework 03, Problem 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

//We assume all filenames are less than 1000 chars, and each line in a file is less than 1000 chars
#define MAXFNAME 1000
#define MAXLENGTH 1000


int main(int argc, char** argv){
	//Predeclare traverseCountLines function
	void traverseCountLines(int* numLines, char* pathName);
	
	//If no pathname is given, return an error
	if(argc < 2 || strlen(argv[1]) == 0){
		printf("No pathname provided");
		return 1;
	}
	
	//An integer used to hold the total number of lines for the file
	int totalLines;

	//All we need to do from here is call traverse 
	traverseCountLines(&totalLines, argv[1]);

	//Print out the total number of lines under the directory
	printf("Lines in all .txt files under %s: %d", argv[1], totalLines);

	return 0;
}


void traverseCountLines(int* numLines, char* pathName){
	//Predeclare countlines function
	void countLines(int* numLines, char* fname);

	//predeclare to hold status
	struct stat status;
	//Will tell us if we have a regular file or a directory
	mode_t mode;
	int result;
	//References for the current directory and the directory entries
	DIR* dirP;
	struct dirent* entryP;
	//Assume each filename is less than 1000 characters long
	char fName[MAXFNAME];

	//Get the status of the current pathName
	result = stat(pathName, &status);

	//If the result is bad, something went wrong, so return
	if(result == -1){
		fprintf(stderr, "Status of file %s was not available\n", pathName);
		return;
	}

	//Grab the mode for comparison
	mode = status.st_mode;

	//If the file is a regular file 
	if(S_ISREG(mode)){
		char* fExtension;
		//Search for file extension	
		fExtension = strchr(pathName, '.');
		//compare the extension to txt
		if(strcmp(fExtension, ".txt") == 0){
			//Call countlines if strcmp works
			countLines(numLines, pathName);
		}
	//If we have a directory, recursively search that directory
	} else if(S_ISDIR(mode)){
		//Open the directory for traversal
		dirP = opendir(pathName);
		
		//Go through each entry in the directory
		while((entryP = readdir(dirP)) != NULL){
			//We do not want to get stuck in an infinite loop
			//Skip over the "."(current directory) and ".."(parent directory)
			if(strcmp(entryP -> d_name, ".") == 0 || strcmp(entryP -> d_name, "..") == 0){
				continue;
			}

			//Save the whole path to fname
			sprintf(fName, "%s/%s", pathName, entryP -> d_name);

			//Traverse that directory recursively
			traverseCountLines(numLines, fName);
		}

		//close once done
		closedir(dirP);
	}
}


void countLines(int* numLines, char* pathName){
	//Assume each line in the file is at most 1000 chars
	char line[MAXLENGTH];
	
	//Open the file for reading
	FILE* fl = fopen(pathName, "r");
	
	char* lineP;

	while((lineP = fgets(line, 1000, fl)) != NULL){
		//Increment numlines by 1
		(*numLines)++;
	}	

	//Close the file once we're done
	fclose(fl);


}

