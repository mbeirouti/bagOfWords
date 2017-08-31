#include "linkedLists.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node buildNode(char* word){ //INEFFICIENCY: RETURNS COPY INSTEAD OF POINTER TO MANIPULATED OBJECT

	struct node built;
	
	built.word = malloc(sizeof(char) * (strlen(word)+1));
	
	strcpy(built.word, word);
	built.wordSize = strlen(word);
	built.count = 0;
	built.next = NULL;

	return built;
}


struct linkedList buildLinkedList(){ //INEFFICIENCY: RETURNS COPY INSTEAD OF POINTER TO MANIPULATED OBJECT

	struct linkedList built;

	built.size = 0; // Number of nodes in the list
	built.head = NULL; // Address of head node
	built.tail = NULL; // Address of tail node

	return built;

}

// Should probably return one of the two addresses instead of void
void linkTwoNodes(struct node* firstNode, struct node* secondNode){ 

	(*firstNode).next = &(*secondNode);

}

// Should probably return one of the two addresses instead of void
void addToList(struct linkedList* list, struct node* addNode){ 

	if((*list).size == 0){

		(*list).size = 1;
		(*list).head = addNode;
		(*list).tail = addNode;

	} else {
		(*list).size++;
		linkTwoNodes( (*list).tail , addNode );
		(*list).tail = addNode;
	}
	
}

struct node* findByIndex(struct linkedList* list, int index){

	int gtrdn;
	struct node currentNode;
	struct node* addressOfIndex;

	if(index > (*list).size-1){

		printf("Warning, index specified is greater than size of list provided. Using max index.");
		index = (*list).size-1;
		addressOfIndex = (*list).tail;

	} else if (index < 0) {

		printf("Warning, index specified is greater than size of list provided. Using min index.");
		index = 0;
		addressOfIndex = (*list).head;

	} else {

		addressOfIndex = (*list).head;

		for(gtrdn = 0; gtrdn < index; gtrdn++){

			addressOfIndex = (*addressOfIndex).next;
		
		}

	}

	return addressOfIndex;

}

struct node* findByValue(struct linkedList* list, char* value, int* index){

	int gtrdn;
	struct node* currentNode = NULL;
	struct node* addressOfNode = NULL;

	currentNode = (*list).head;
	
	(*index) = -1;

	for(gtrdn = 0; gtrdn < (*list).size; gtrdn++){

		if(strcmp((*currentNode).word, value) == 0){

			addressOfNode = currentNode;
			(*index) = gtrdn;
			break;

		} else {

			currentNode = (*currentNode).next;

		}

	}

	return addressOfNode;

}

int insertByIndex(struct linkedList* list, struct node* addNode, int index) {


	if( index <= 0 ) { // If appending to head of list
		
		if( index < 0){
			printf("Warning, you are attempting to append to an index less than 0. Appending to head instead.\n");
		}

		linkTwoNodes( addNode , (*list).head );
		(*list).head = addNode;
		(*list).size++;

	} else if( index >= (*list).size ){ // If appending to tail of list

		if( index > (*list).size){
			printf("Warning, you are attempting to append to an index greater than the list size. Appending to tail instead.\n");
		}

		addToList( list, addNode );

	} else {
		
		// CHANGE: Use only the previous node pointer, then use the previous nodes next pointer to get the nodeAtIndexPointer
		struct node* nodeAtPreviousIndexPointer = findByIndex(list, index-1);
		struct node* nodeAtIndexPointer = findByIndex(list, index);

		// For the node added at the index, make the previous node point to it
		// then make it point to the next node (the one that was previously at the index)
		linkTwoNodes(nodeAtPreviousIndexPointer, addNode);
		linkTwoNodes(addNode, nodeAtIndexPointer);

		(*list).size++;

	}
	
	return 0;

}


int removeByIndex(struct linkedList* list, int index){

	struct node* foundNode = NULL;
	struct node* previousNode = NULL;

	if (index >= ((*list).size-1)) { // If node is at the end of the list or index is too large
		
		index = (*list).size - 1; // Fixes it if it is too large
		
		previousNode = findByIndex(list, index-1); // CAN BE OPTIMIZED SO THAT FINDBYINDEX RETURNSPREVIOUS AND FOUND 
		linkTwoNodes(previousNode, NULL);
		(*list).tail = previousNode;
		(*list).size--;

		return 1;


	} else if (index <= 0){
		index = 0;
		
		foundNode = (*list).head;
		(*list).head = (*foundNode).next;
		(*foundNode).next = NULL;
		(*list).size--;

		return 1;

	} else {

		// CHANGE: Use only the previous node pointer, then use the previous nodes next pointer to get the nodeAtIndexPointer
		previousNode = findByIndex(list, index-1); 
		foundNode = findByIndex(list, index); 

		linkTwoNodes(previousNode, (*foundNode).next);

		(*foundNode).next = NULL;

		(*list).size--;

		// CHANGE: Should the memory be freed here?

		return 1;

	}


	return -1;


}

int removeByValue(struct linkedList* list, char* value){

	struct node* foundNode = NULL;
	int indexOfNode = -1;

	foundNode = findByValue(list, value, &indexOfNode);

	if (indexOfNode < 0){
		return -1;
	} else {
		removeByIndex(list, indexOfNode);
		return 1;
	}

	// CHANGE: Should the memory be freed here? Depends on removeByIndex


	return -1;

}

int printLinkedList(struct linkedList* printedList){

	int gtrdn;
	struct node* currentNode = (*printedList).head;

	printf("%s:%d", (*currentNode).word, (*currentNode).count);

	for(gtrdn = 1; gtrdn < (*printedList).size; gtrdn++){

		currentNode = (*currentNode).next;
		printf(" -> %s:%d", (*currentNode).word, (*currentNode).count);

	}

	printf("\n");

	return 0;

}


