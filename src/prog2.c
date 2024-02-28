/**
 * @Author Jack Robbins
 * Homework 03, problem 2
 */

#include <ctype.h>
#include <stdio.h>

//Define an unsigned char type byte
typedef unsigned char BYTE;

int main(int argc, char **argv){
	//If no file is passed, exit with an error
	if(argc < 1){
		printf("No filename given");
		return 1;
	}

	//Open the file for reading in binary mode
	FILE* fl = fopen(argv[1], "rb");

	//If file isn't opened, error out
	if(fl == NULL){
		printf("Cannot open file");
		return 1;
	}

	//We expect each 4 bytes to be an unsigned int
	unsigned int i;	

	//figure out how many bytes we read each time(fread returns size_t)
	size_t bytesRead;

	//While we've read more than 0 bytes
	while((bytesRead = fread(&i, 1, sizeof(i), fl)) > 0){
		//Print out int and hex values
		printf("Integer: Hex: 0x%08x Dec: %u \n", i, i);
		
		//Make a one byte mask
		BYTE mask = 0xFF;
		//Get each individiual byte in our int using bitshifting
		BYTE byte1 = i & mask;
		BYTE byte2 = (i >> 8) & mask;
		BYTE byte3 = (i >> 16) & mask;
		BYTE byte4 = (i >> 24) & mask;
	
		BYTE bytes[] = {byte1, byte2, byte3, byte4}; 

		//For each byte, print out the hex value and either the int or char value
		for(int i = 0; i < 4; i++){
			BYTE byte = bytes[i];
			printf("Byte %d: Hex: 0x%02x Char: ", i, byte);
			
			if(isprint(byte)){
				printf("%c\n", byte);
			} else {
				printf("\\%u\n", byte);
			}
		}
	}


	//Close once we are all done
	fclose(fl);

	return 0;
}
