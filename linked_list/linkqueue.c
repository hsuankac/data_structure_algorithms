/**
  Implementation of Queue using linkedlist
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
void insertQueue(LinkedList *, int);
void printList(LinkedList *);
int deleteQueue(LinkedList *);

// to initialize the linkedlist object
// Input parameter: listp is the pointer to linkedlist object
// Precondition: LinkedList object pointed by listptr must be existing.
// Return Value: Nothing
void initList(LinkedList *lstPtr){
  lstPtr->head = NULL;
  lstPtr->tail = NULL;
  lstPtr->nodeCount = 0;
}


// To add a new node at the end of the LinkedList
// Input parameters: pointer to struct LinkedList, an integer data that will
//                   be the content  of the new node.
// Precondition: The linkedList object must be existing.
// Return Value: Nothing
void insertQueue(LinkedList *listPtr, int data){
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
    listPtr->tail->next = newNodePtr;
    listPtr->tail = newNodePtr;
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

int deleteQueue(LinkedList *lstPtr){
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
  printf("    Queue using LinkedList\n");
  printf("----------------------------------------\n");
  printf("1. Insert\n");
  printf("2. Delete\n");
  printf("3. Display\n");
  printf("4. Quit\n");                   // to terminate each node
}

int main(){
  LinkedList queue;
  initList(&queue);
  int choice;
  menu();
  int quit = 0;
  int data;

  while(!quit){
    printf("Please input your choice: ");
    scanf("%d", &choice);

    switch(choice){
      case 1:
              printf("Input data to insert: ");
              scanf("%d", &data);
              insertQueue(&queue, data);
              break;
      case 2:
            data = deleteQueue(&queue);
            if (data != -9999){
              printf("Deleted data is: %d\n", data);
            }
            else{
              printf("Queue underflow\n");
            }
            break;
      case 3:
            printList(&queue);
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
