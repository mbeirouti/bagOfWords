#include "hashMaps.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

const int maxWordLength = 20;

int main(void) {

	int gtrdn; // This is just what I like calling my iterators

	FILE* filePointer;
	char fileName[] = "article.txt"; 

	// OPEN FILE ___________________________________
	printf("Opening file\n");
	filePointer = fopen(fileName, "r");

	if(filePointer == NULL){

		printf("The file you tried to open probably doesn't exist!\n");
	
	} else {
		
		printf("The file has successfully been opened!\n");
	
	}

	int read;
	char* readChar = malloc(sizeof(char)*(1+1));
	char* readWord = malloc(sizeof(char)*(maxWordLength+1));

	// Read a single character
	read = fgetc(filePointer);
	readChar[0] = (char) read;
	readChar[1] = '\0';

	// Initialize readWord with a null terminator to ensure
	// functions like strcat and strcpy work correctly
	readWord[0] = '\0';

	int previousWasPunct = 0;
	int isFound = -1;
	

	// Reading the file and parsing words. Needs some refining especially for edge cases
	while(read != EOF){
		
		if(ispunct(read) || read == ' ' || read == '\n'){

			if(previousWasPunct){

				// Do nothing
				previousWasPunct = 1;

			} else {

				// First punctuation mark was found, delimits a word

				// WARNING: Should I be using memcpy?
				putWord(readWord);

				free(readWord);
				readWord = malloc(sizeof(char)*(maxWordLength+1));
				readWord[0] = '\0';
				previousWasPunct = 1;

			}


		} else {

				*readChar = tolower(*readChar);
				strcat(readWord, readChar);
				previousWasPunct = 0;

		}

		// Read a new character
		read = fgetc(filePointer);
		readChar[0] = (char) read;
		readChar[1] = '\0';

	}

	printf("Reached the files end\n");

	printHashTable();


	return 1;
}