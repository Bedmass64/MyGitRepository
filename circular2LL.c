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

void deleteNodePosition(CircularDoublyLinkedListP list, int position){
    //Checking to see if the list is empty
    if (list->firstValue == NULL){
            printf("The list is empty, No elements can be deleted.\n");
            return;
    } 
    else{
        NodeTP currentNode = list->firstValue;
        //position for the current while counting from 0, will increment
        int counter = 0;

        //This is checking to make sure currentNode is not equal to the start 
        //or the end of the list. This is pretty much the same function, but it
        //is searching for a different condition, that of the position instead
        //of the value as done in the previous function. 
        while (currentNode != NULL) {
            //this is checking to see if the counter is the same as position, 
            //meaning the currentNode has been incremented the correct amount
            //of times in order to be at the right position to do the rest of 
            //the operations. 
            if (counter == position) {
                //checking for the case where it is the first node
                if (currentNode->prevValue == NULL) {
                    //all of the comments on these pointers are the same as the 
                    //previous function, so to avoid redundancy i will not include
                    //them for these pointers in this function.
                    list->firstValue = currentNode->nextValue;
                }
                //checking for the case where it is the last node
                if (currentNode->nextValue == NULL) {
                    list->lastValue = currentNode->prevValue;
                }
                //checking to make sure it is within the scope of the list
                if (currentNode->prevValue != NULL) {
                    currentNode->prevValue->nextValue = currentNode->nextValue;
                }
                //checking to make sure it is within the scope of the list
                if (currentNode->nextValue != NULL) {
                    currentNode->nextValue->prevValue = currentNode->prevValue;
                }
                //setting all of the pointers for currentNode to NULL before 
                //freeing it up
                currentNode->nextValue = NULL;
                currentNode->prevValue = NULL;
                free(currentNode);
                currentNode = NULL;
                printf("Node at position %d has been deleted from the list\n", position);
                //decrementing the elementCount used inside of main
                (list->elementCount)--;
                return;
            }
            else{
                //This is cycling the values in order for all of them to be read
                //inside of the while loop if the previous check was not met.
                currentNode = currentNode->nextValue;
                counter++;
            }
        }
        //condition for while terminated, meaning the position was not found in
        //the list. There is error handling inside of the main function to make sure
        //this does not show up.
        printf("Node at position %d was not found in the list\n", position);
        
    }
}

//F5 implementation
//Purpose is to print out the entire contents of the C2LL 
void printList(CircularDoublyLinkedListP list){
    //Checking to make sure the list has content, as the first value of an empty
    //list is NULL
    if(list->firstValue == NULL){
        printf("The list is empty\n");
        return;
    }
    else{
        //if the check to make sure the list is passed, then you allocate
        //the first position of the list to the pointer of the node to the
        //current element
        NodeTP currentNode = list->firstValue;

        //This here is done to show a visual of what a circular double linked
        //list is, and that it start and ends with a NULL.
        printf("\\0->");
        //This loop condition will be met so long as it is not reading the first
        //or last element of the list, as they are both NULL.
        while(currentNode != NULL){
            printf("%d->", currentNode->currentValue);
            //This is incrementing the while loop by making this become the next 
            //value that is being passed before checking the condition for the
            //while loop again
            currentNode = currentNode->nextValue;
        }
        //finish the formatting of the: \0->...->\0 
        printf("\\0\n");
    }
}

//F6 implementation
//Purpose is to print out the entire contents of the C2LL in reversed order.
void printListReverse(CircularDoublyLinkedListP list){
    //Checking to make sure the list has content, as the first value of an empty
    //list is NULL
    if(list->firstValue == NULL){
        printf("The list is empty\n");
        return;
    }
    else{
        //if the check to make sure the list is passed, then you allocate
        //the first position of the list to the pointer of the node to the
        //current element
        //Only 3 differences between this function and the printList is that this
        //pointer is starting at the last value
        NodeTP current = list->lastValue;

        //This here is done to show a visual of what a circular double linked
        //list is, and that it start and ends with a NULL.
        printf("\\0->");
        //This loop condition will be met so long as it is not reading the first
        //or last element of the list, as they are both NULL.
        while(current != NULL){
            printf("%d->", current->currentValue);
            //This is decrementing the while loop by making this become the next 
            //value that is being passed before checking the condition for the
            //while loop again
            current = current->prevValue;
        }
        //finish the formatting of the: \0->...->\0 
        printf("\\0\n");
    }
}

int main(void){
    //Construct a list using a similar list constructor as that found in the
    //class slides.
    CircularDoublyLinkedListP myList = constructList();
    //defining selector outside of the while loop for the while condition
    int selector = 0;

    while(selector != -1){
        //These are put here in order to reset the value of each variable in order
        //to avoid being sent in an infinite loop.
        int value = 0; 
        int position = 0;
        selector = 0;

        printf("\nPlease select a number to do the following operation:\n\n");
        printf("Add a value to the end of the list: 1\n");
        printf("Add a value to a specified position in the list: 2\n");
        printf("Delete the first node that shows up with the specified value: 3\n");
        printf("Delete the first node that shows up at the specified position: 4\n");
        printf("Prints out your circular doubly linked list: 5\n");
        printf("Prints out your circular doubly linked list in reverse: 6\n");
        printf("Exit: -1\n\n");
        scanf("%d", &selector);

        //Implementation for F1 inside of main
        if (selector == 1){
            printf("Option 1 selected\n");
            printf("Please enter any value: ");
            scanf("%d", &value);
            addNode(myList, value);
        }
        //Implementation for F2 inside of main
        //The user is able to add an element to position 0 of the empty list,
        //therefore there is no handling a case where there is an empty list
        else if (selector == 2){
            printf("Option 2 selected\n");
            printf("Please enter a value: ");
            scanf("%d", &value);
            printf("Please enter a position (counting from 0): ");
            scanf("%d", &position);
            addNodePosition(myList, value, position);
        }
        //Implementation for F3 inside of main
        else if (selector == 3){
            printf("Option 3 selected\n");
            //checking here to see if the list is empty, although it is also done
            //inside of the function itself. This is done here before prompting
            //the user for input.
            if (myList->elementCount == 0){
                printf("Your list is currently empty, unable to delete elements\n");
            }
            else{
                printf("Please enter the value of the node you would like to delete: \n");
                scanf("%d", &value);
                deleteNode(myList, value);
            }
        }
        //Implementation for F4 inside of main
        else if (selector == 4){
            printf("Option 4 selected\n");
            //checking to see if there are elements included in the list in order
            //to prompt the user for input
            if (myList->elementCount == 0){
                printf("Your list is currently empty, unable to delete elements\n");
            }
            else{
                printf("Please enter the position of the node you would like to delete (counting from 0): \n");
                scanf("%d", &position);
                //checking to see if the position they are giving is within the amount
                //of elements there inside of the list
                if (position < 0 || position > (myList->elementCount - 1)){
                    printf("The position you are giving is outside of the scope of your list (0, %d)\n", (myList->elementCount - 1));
                }
                else{
                    deleteNodePosition(myList, position);
                }
            }
        }
        //Implementation for F5 inside of main
        else if (selector == 5){
            if (myList->elementCount == 0){
                printf("Your list is currently empty, unable to print list\n");
            }
            else{
                printf("Option 5 selected\n");
                printf("printing list: \n");
                printList(myList);
            }
        }
        //Implementation for F6 inside of main
        else if (selector == 6){
            if (myList->elementCount == 0){
                printf("Your list is currently empty, unable to print list reversed\n");
            }
            else{
                printf("Option 6 selected\n");
                printf("printing list reversed: \n");
                printListReverse(myList);
            }
        }
        else if (selector == -1){
            printf("Termination value selected\n\n");
            printf("Have a nice day!\n");
            //exit successful is here
            return 0;
        }
        //error handling input that isnt a valid input, whether this is for
        //position, value or selector, it will bring you here.
        else{
            printf("Please enter a valid input \n");
            printf("(Press enter with a blank input to continue)\n");
            
            //user input handling for something that isnt valid. Will require
            //the user to press enter with no input to exit the loop and go back
            //to the options menu. this works for all user input, whether it is
            //selector, value or position. different behaviour inside of my main
            //terminal then that of falcon, where falcon does not require enter
            //after invalid input, but my terminal does.
            while (getchar() != '\n'){
                fflush(stdin);
            }
        }
    }
    //if somehow you manage to get to this point in the loop, then you found a
    //bug i did not
    return 1;
}