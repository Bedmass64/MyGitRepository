# MyGitRepository

# Circular Doubly Linked List (CDLL) Implementation in C

## Overview
This project implements a **Circular Doubly Linked List (CDLL)** in C, allowing users to dynamically manage a list of nodes. The program provides functionalities such as adding, deleting, and printing nodes in both forward and reverse order.

## Features
- **Create a Circular Doubly Linked List**
- **Add a Node** at the end of the list
- **Insert a Node** at a specific position
- **Delete a Node** by value
- **Delete a Node** at a specific position
- **Print the List** (forward and reversed)

## Files
- `main.c`: Contains the full implementation of the CDLL with a menu-driven interface.

## Group Members and Roles
| Name | Role |
|------|------|
| Member 1 | Implemented `addNode()` and `constructList()` |
| Member 2 | Implemented `deleteNode()` and `deleteNodePosition()` |
| Member 3 | Implemented `printList()` and `printListReverse()` |

## Usage
1. Compile the program using **GCC**:
   ```sh
   gcc -o cdll main.c
   ```
2. Run the program:
   ```sh
   ./cdll
   ```
3. Choose from the menu options to manipulate the circular doubly linked list.

## Menu Options
Upon execution, the user is presented with the following options:

```
Please select a number to do the following operation:

1 - Add a value to the end of the list
2 - Add a value at a specific position
3 - Delete the first node with a given value
4 - Delete a node at a specific position
5 - Print the list
6 - Print the list in reverse
-1 - Exit
```

## Example Run
```
Please select a number to do the following operation:
1
Please enter a value: 10
Node with value 10 has been added to your list.
5
\0->10->\0
2
Please enter a value: 20
Please enter a position: 1
Node with the value 20 added at position 1 in your list.
5
\0->10->20->\0
```

