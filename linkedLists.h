// A single list element, specific to word frequency counting application
// Contains a word, word length, occurence count and pointer to the next node 
typedef struct node{

	char* word;
	int wordSize;
	int count;
	struct node* next;

}node;

// A list of nodes with a pointer to the head, tail and a count of the nodes
// contained in the list
typedef struct linkedList{

	int size;
	struct node* head;
	struct node* tail;

}linkedList;


// Unused struct thus far
// Could be used to make the code more flexible
typedef struct dataType{

	char* word;

}dataType;


// Node instantiation and linking
struct node buildNode(char*);

// Linked list instantiation
struct linkedList buildLinkedList();

// List search
struct node* findByIndex(struct linkedList* , int );
struct node* findByValue(struct linkedList* , char* value, int*);

// List modification (node additions and removals)
void linkTwoNodes(struct node* , struct node* );
void addToList(struct linkedList* , struct node* );
int insertByIndex(struct linkedList* , struct node* , int );
int removeByIndex(struct linkedList* , int );
int removeByValue(struct linkedList* , char* value );

// List output for debugging purposes
int printLinkedList(struct linkedList*);