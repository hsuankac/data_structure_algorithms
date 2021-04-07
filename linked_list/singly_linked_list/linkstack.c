/**
  Implementation of Stack using linkedlist
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node{
  int data;
  struct Node *next;
}Node;

typedef struct {
  struct Node *head;
  struct Node *tail;
  int nodeCount;
}LinkedList;

// function prototypes
void initList(LinkedList *);
void push(LinkedList *, int);
void printList(LinkedList *);
int pop(LinkedList *);

// to initialize the linkedlist object
// Input parameter: listp is the pointer to linkedlist object
// Precondition: LinkedList object pointed by listptr must be existing.
// Return Value: Nothing
void initList(LinkedList *lstPtr){
  lstPtr->head = NULL;
  lstPtr->tail = NULL;
  lstPtr->nodeCount = 0;
}


// To add a new node at the begining of the LinkedList
// Input parameters: pointer to struct LinkedList, an integer data that will
//                   be the content  of the new node.
// Precondition: The linkedList object must be existing.
// Return Value: Nothing

void push(LinkedList *listPtr, int data){
  Node *newNodePtr = (Node*)malloc(sizeof(Node));
  if (newNodePtr == NULL){
    printf("Unable to allocate new node\n");
    return;
  }
  newNodePtr->data = data;
  newNodePtr->next = NULL;


  if (listPtr->nodeCount == 0){
    // this is the case when the list is empty
    listPtr->head = newNodePtr;
    listPtr->tail = newNodePtr;
  }
  else{
    // this is the case when the list is not empty
    newNodePtr->next = listPtr->head;
    listPtr->head = newNodePtr;
  }
  listPtr->nodeCount++;
}


void printList(LinkedList *lstPtr){
  if (lstPtr->nodeCount == 0){
    printf("Linked list is empty\n");
    return;
  }
  Node *current = lstPtr->head;
  while(current != NULL){
    printf("%4d", current->data);
    current = current->next;
  }
  printf("\n");
}

int pop(LinkedList *lstPtr){
  if (lstPtr->nodeCount == 0){
    return -9999;
  }
  Node *first = lstPtr->head;
  int data = first->data;

  if (lstPtr->nodeCount == 1){
    // there is only one node
    lstPtr->head = NULL;
    lstPtr->tail = NULL;

  }
  else{
    // there are many nodes and we need to delete the first
    lstPtr->head = first->next;
  }
  free(first);
  lstPtr->nodeCount --;
  return data;
}


void menu(){
  printf("    Stack using LinkedList\n");
  printf("----------------------------------------\n");
  printf("1. Push\n");
  printf("2. Pop\n");
  printf("3. Display\n");
  printf("4. Quit\n");                   // to terminate each node
}

int main(){
  LinkedList stack;
  initList(&stack);
  int choice;
  menu();
  int quit = 0;
  int data;

  while(!quit){
    printf("Please input your choice: ");
    scanf("%d", &choice);

    switch(choice){
      case 1:
              printf("Input data to Push: ");
              scanf("%d", &data);
              push(&stack, data);
              break;
      case 2:
            data = pop(&stack);
            if (data != -9999){
              printf("Poped data is: %d\n", data);
            }
            else{
              printf("Stack underflow\n");
            }

            break;
      case 3:
            printList(&stack);
            break;
      case 4:
            quit = 1;
            break;
      default:
            printf("Invalid option chosen, valid option is from 1 - 4\n");
    }
  }

  return 0;
}
