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


//F2 implementation
//purpose is to add a node at a given spot inside of the existing list.
void addNodePosition(CircularDoublyLinkedListP list, int value, int position){
    NodeTP newNode = (NodeTP)malloc(sizeof(NodeT));

    //There is some similarity in the code between F1 and F2, as they are both
    //doing a very similar job, but their job as a function as a whole has a 
    //different objective.
    if (newNode == NULL){
        printf("Memory allocation failure\n");
        //exit failure to terminate program, since return will end the function
        exit(EXIT_FAILURE);
        //return;
    }
    //setting the currentValue of newNode to value.
    newNode->currentValue = value;
    //Adding a node using the addNode if it is the first element in the list.
    if (list->firstValue == NULL){
        addNode(list, value);
    }
    //This is dealing for the case where the user input is 0
    else if(position == 0){
        NodeTP currentNode = list->firstValue;

        //inserts a new node at the start of the list.
        list->firstValue = newNode;

        //setting the pointer for nextValue of newNode to currentNode
        newNode->nextValue = currentNode;

        //since newNode is the first element now, the previous is a Null
        newNode->prevValue = NULL;

        //This goes in unison with the second pointer operation in this
        //if statement, where currentNode's previous is set to newNode.
        currentNode->prevValue = newNode;

    }
    //dealing for all other valid input included in the list.
    else{
        NodeTP currentNode = list->firstValue;
        //This is formatting the for loop to walk and check for every value
        //until the end of the list is reached (NULL)
        for (int i = 0; i < (position -1); i++){
            currentNode = currentNode->nextValue;
            //this is the check to see if it is trying to replace the position
            //of one of the null terminators
            if (currentNode == NULL){
                //If this check is passed, the malloc will be freed and the
                //pointer will be nullified, and since the \0 can only be found
                //on the start or end of the list, then we know that we have 
                //arrived at the end of the list and can return this function.
                printf("Invalid position, unable to add your node.\n");
                free(newNode);
                newNode = NULL;
                return;
            }
        }
        //Attributing newNodes pointer to the next value equal to the current
        //Node's next value
        newNode->nextValue = currentNode->nextValue;
        //After the new node has been put in the correct place to attribute its
        //value for currentNode pointing to next value, the previous value is set
        //to the currentNode itself.
        newNode->prevValue = currentNode;
        //specifying what the surrounding for currentNode is and checking
        //to see if it is not the last element in the list.
        //updating the currentNode's previous value to be set to the newNode
        if (currentNode->nextValue != NULL){
            currentNode->nextValue->prevValue = newNode;
        }
        //updating the currentNode's next value to be set to the newNode
        currentNode->nextValue = newNode;

        //Check to see if the new node is the first item to be swapped in
        if (newNode->prevValue == NULL){
            list->firstValue = newNode;
        }
        //Check to see if the new node is the last item to be swapped in
        if (newNode->nextValue == NULL){
            list->lastValue = newNode;
        }
        printf("Node with the value %d added at the position %d in your list.\n", value, position);
    }
    //inrementing the counter for the amount of elements that are currently in the list.
    (list->elementCount)++;
}

void deleteNode(CircularDoublyLinkedListP list, int value){
    //Checking to see if the list is empty
    if (list->firstValue == NULL){
        printf("The list is empty, No elements can be deleted.\n");
        return;
    } 
    else{
        NodeTP currentNode = list->firstValue;

        while(currentNode != NULL){
            //checking to see if the currenValue located in the node is the same
            //when compared to that of value, meaning the element is found.
            if (currentNode->currentValue == value){
                //Multiple if blocks in order to make sure all conditions are read
                //instead of using else if's

                //checking for the first item in the list
                if (currentNode->prevValue == NULL){
                    //handling deleting the first item in the list.
                    list->firstValue = currentNode->nextValue;
                }
                //Checking for the last item in the list
                if (currentNode->nextValue == NULL){
                    //handling deleting the last item in the list.
                    list->lastValue = currentNode->prevValue;
                }
                //checking to make sure it is within the scope of the list
                if (currentNode->prevValue != NULL){
                    //attributing the pointer for current node to the correct
                    //values
                   currentNode->prevValue->nextValue = currentNode->nextValue;  
                }
                //checking to make sure it is within the scope of the list
                if (currentNode->nextValue != NULL){
                    //attributing the pointer for current node to the correct
                    //values
                    currentNode->nextValue->prevValue = currentNode->prevValue;
                }
                //Freeing up the currentNode and nulling out its positions.
                currentNode->nextValue = NULL;
                currentNode->prevValue = NULL;
                //freeing up the currentNode
                free(currentNode);
                currentNode = NULL;
                printf("Node with value of %d appearing first in the list has been deleted\n", value);
                //decrementing the element count found in list used for checks inside of main.
                (list->elementCount)--;
                return;
            }
            else{
                //This is cycling the value of currentNode for the while loop
                currentNode = currentNode->nextValue;
            }
        } 
        //outside of the while loop, meaning the value was not found
        printf("Node with value %d was not found as an element in the list\n", value);
    }
}

