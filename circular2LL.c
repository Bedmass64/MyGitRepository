#include <stdio.h>
#include <stdlib.h>


//typedef struct for a node
typedef struct node{
    //Stores the value of the current 
    int currentValue;
    //pointer to the next node in the list
    struct node *nextValue;
    //pointer to the previous node in the list
    struct node *prevValue;
    //Able to call this struct through its value or through its pointer using
    //its specified name instead of having a bunch of *, instead use the pointer
    //version for the specific struct.
} NodeT, *NodeTP;


//typedef struct for the list
typedef struct{
    //Stores the count of the number of elements in the list
    int elementCount;
    //Pointer for the starting value of the list
    NodeTP firstValue;
    //Pointer for the ending value of the list
    NodeTP lastValue;
    //Able to call this struct through its value or through its pointer using
    //its specified name 
} CircularDoublyLinkedList,  *CircularDoublyLinkedListP;

//constructor for list
//Purpose is to construct a new list and attribute the appropriate values
//to the list struct given it has not already been made.
CircularDoublyLinkedListP constructList(void){
    CircularDoublyLinkedListP myList;
    if ((myList = malloc(sizeof(CircularDoublyLinkedList))) == NULL){
        return NULL;
    }
    else{
        //As seen on the constructor inside of the slide deck. Added last value
        //which has the same purpose as first value ( \0 )
        myList->firstValue = NULL;
        myList->lastValue = NULL;
        myList->elementCount = 0;
        return myList;
    }
}

//potentially have to change this to only take in value

//F1 of the assignment
void addNode(CircularDoublyLinkedListP list, int value){

    //Malloc is being done here to dynamically allocate memory for the space in
    //the list on an as needed basis instead of being static as per assignments 
    //requirements.
    //this structure for setting up the pointer is as seen in multiple of my
    //ressources with NodeTp at the front of malloc.
    NodeTP newNode = (NodeTP)malloc(sizeof(NodeT));
    //This if statement is the checking of the condition to see if this malloc 
    //is allocating a null value is done inside of the first function.
    if (newNode == NULL){
        printf("Memory allocation failure\n");
        exit(EXIT_FAILURE);
        //return;
    }

    newNode->currentValue = value;
    newNode->nextValue = NULL;
    newNode->prevValue = NULL;

    //This is a condition to check and see if the list is an empty list
    //meaning that the first value in the list is equal to NULL.
    if (list->firstValue == NULL){
        list->firstValue = newNode;
        list->lastValue = newNode;
        printf("Your new circular doubly linked list has been created.\n");
        printf("Node with value %d has been added to your list.\n", value);
    }
    //This is checking to see if the list is containing elements already
    //before doing the necassary operations in order to add the value to
    //the end of the linked list.
    else{
        
        //nextValue whcih is taken from the list's pointer is set to the newNode
        list->lastValue->nextValue = newNode;
        //This is setting the previous value in the node struct to the farthest
        //value in the list
        newNode->prevValue = list->lastValue;
        //Since we have just made this value equal to the new previous value in
        //the node struct, we add this to take its place in the list struct.
        list->lastValue = newNode;
        printf("Node with value %d has been added to the end of your list.\n", value);
    }
    //increment the amount of elements in the list for every time this function 
    //is being passed
    (list->elementCount)++;
}


