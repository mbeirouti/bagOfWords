#include "hashMaps.h"
#include <string.h>

int matrixSize = 5000;
struct linkedList* hashTable[5000];


int collisionCount = 0;

int testIndicator = 0;

// Initializes the hash table to null indicating no buckets (linked lists)
int initializeHashTable(){

	int gtrdn;

	for(gtrdn = 0; gtrdn < matrixSize; gtrdn++){
		hashTable[gtrdn] = NULL;
	}

	return -1;
}

// Returns the numeric value of a signle letter
int letterValue(char letter){

    return (((int)letter) - 65) % 32; //Accounting for difference in ASCII number for capital and lowercase

}

// Finds the hash key for an entire word
int hashWord(char* word){

    int gtrdn, test = 0;
    int hashValue = 0;

    for(gtrdn = 0; gtrdn < strlen(word); gtrdn++){

        hashValue += letterValue(word[gtrdn]);

    }

    return hashValue % matrixSize;;

}


// Places a word into the hash table (accounting for existence or lack of a linked list)
int putWord (char* inputWord){

	unsigned int hashValue;

	// I think I just had this to ensure the inputWord doesn't change
	char* word = malloc(strlen(inputWord)+1);
	word[strlen(inputWord)] = '\0';
	strcpy(word, inputWord);

	hashValue = hashWord(word);

	if (hashTable[hashValue] == NULL){ 
		
		// If there is no linked list at hashValue
		// There is no word entry, make one
		// Does this to avoid variable loss in scope
		struct linkedList tempLinkedList;
    	tempLinkedList = buildLinkedList();
    	struct linkedList *tmp = malloc(sizeof(struct linkedList));
    	memcpy(tmp, &tempLinkedList, sizeof(struct linkedList));

    	hashTable[hashValue] = tmp;

		struct node insertNode = buildNode( word );
		insertNode.count = 1;
		struct node *tempNode = malloc(sizeof(struct node));
		memcpy(tempNode, &insertNode, sizeof(struct node));

		addToList(hashTable[hashValue], tempNode);

		testIndicator = 1;

		return 1;

	} else { 

		// There is already a linked list
		// Try to find the word and increment count
		// If it doesnt exist push it onto list bottom
		collisionCount++;

		int wordIndex;

		struct node* valueAddress = findByValue(hashTable[hashValue], word, &wordIndex);

		if (valueAddress == NULL){

			// List exists but word isn't there, so add it
			struct node insertNodeTwo = buildNode( word );
			insertNodeTwo.count = 1;
			struct node *tempNodeTwo = malloc(sizeof(struct node));
			memcpy(tempNodeTwo, &insertNodeTwo, sizeof(struct node));

			addToList(hashTable[hashValue], tempNodeTwo);
			collisionCount = collisionCount + (*hashTable[hashValue]).size - 1;

			return 1;

		} else {
			
			// Word is already in the list, increment count
			return ((*valueAddress).count++);

		}

	}

	return -1;

}

void printHashTable(void){

	int gtrdn;

	for(gtrdn = 0; gtrdn < 5000; gtrdn++){
		if(hashTable[gtrdn] == NULL){
			// Do nothing
		} else {
			printLinkedList(hashTable[gtrdn]);
		}
		
	}
}