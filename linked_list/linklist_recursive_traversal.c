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
void createListFromRandomNumbers(LinkedList *, int);
void insertAtTail(LinkedList *, int);

// printing of linkedlist in forward direction
void printListForward(LinkedList *);
// to print the linkedlist in the reverse direction.
void printListReverse(LinkedList *);

// helper recursive functions for implementing the traversal
void printRecForward(Node *);
void printRecReverse(Node *);


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
void insertAtTail(LinkedList *listPtr, int data){
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
void createListFromRandomNumbers(LinkedList *lstPtr, int n){
  int i;
  srand(time(NULL));

  for(i = 1; i<=n; ++i){
      int k = rand() % 1000;
      insertAtTail(lstPtr, k);
  }
}

void printListForward(LinkedList *lstPtr){
  printRecForward(lstPtr->head);
}
void printListReverse(LinkedList *lstPtr){
  printRecReverse(lstPtr->head);
}

// helper recursive functions for implementing the traversal
void printRecForward(Node *p){
  if (p == NULL){
    return;
  }
  printf("%4d", p->data);
  printRecForward(p->next);
}
void printRecReverse(Node *p){
    if (p == NULL){
      return;
    }
    printRecReverse(p->next);
    printf("%4d", p->data);
}

int main(){
  LinkedList list;
  initList(&list);
  createListFromRandomNumbers(&list, 10);
  printListForward(&list);
  printf("\n");
  printListReverse(&list);
  printf("\n");
  return 0;
}
