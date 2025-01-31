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

