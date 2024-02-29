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

int main(int argc, char** argv){
	//Predeclare traverseCountLines function
	void traverseCountLines(int* lineNum, char* pathName);
	
	//If no pathname is given, return an error
	if(argc < 2 || strlen(argv[1]) == 0){
		printf("No pathname provided");
		return 1;
	}
	
	//An integer used to hold the total number of lines for the file
	int totalLines;

	//All we need to do from here is call traverse 
	traverseCountLines(&totalLines, argv[1]);


	return 0;
}

void traverseCountLines(int* lineNum, char* pathName){

}

