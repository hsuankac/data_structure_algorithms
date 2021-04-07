#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/**
* struct definition for a node
*/
typedef struct Node{
  int data;
  struct Node *next;  // for storing the address of immediate next node.
  struct Node *prev;  // for storing the address of immediate previous node.
}Node;

typedef struct {
  struct Node *head;  // address of first node. NULL initially.
  struct Node *tail;  // addres of last node. NULL initially.
  int nodeCount;      // count of total number of nodes. 0 initially.
}DblList;

// function prototypes
/**
* initializes the doubly linked list object that is passed.
*/
void initList(DblList *lstPtr);
/**
* add a new node with the data content data (passed as parameter)
* as the first node
*/
void addFirst(DblList *lstPtr, int data);
/**
* add a new node with the data content data (passed as parameter)
* as the last node
*/
void addLast(DblList *lstPtr, int data);

/**
* deletes the first node of the doubly linked list, returns data of the first node
* -999 is the DEQ is underflow.
*/
int deleteFirst(DblList *lstPtr);
/**
* deletes the last node of the list, returns data of the node if deletion is successfull,
* -999 if DEQ is underflow.
*/
int deleteLast(DblList *lstPtr);
/**
* Menu for user interface.
*/
void menu();



// to initialize the linkedlist object
// Input parameter: listp is the pointer to linkedlist object
// Precondition: LinkedList object pointed by listptr must be existing.
// Return Value: Nothing
void initList(DblList *lstPtr){
  lstPtr->head = NULL;
  lstPtr->tail = NULL;
  lstPtr->nodeCount = 0;
}



void menu(){
  printf("    Double Ended Queue Operations\n");
  printf("----------------------------------------\n");
  printf("1. Insert at front\n");          // load integer data from file and will create the list
                                          // by using insert_at_tail operation (menu option 3)
  printf("2. Insert at rear\n");
  printf("3. Delete front\n");          // inserting a new node as the first node
  printf("4. Delete Rear\n");          // inserting a new node as the last node

  printf("5. Quit\n");                   // to terminate each node
}

int main(){
  DblList deq;
  initList(&deq);
  int choice;
  menu();
  int quit = 0;
  int data, n, target;
  int success;
  Node *current = NULL, *prev = NULL;
  while(!quit){
    printf("Please input your choice: ");
    scanf("%d", &choice);

    switch(choice){
      case 1:
            // ask to input
            printf("Input data to insert at head (as first node): ");
            scanf("%d", &data);
            addFirst(&deq, data);
            break;
      case 2:
            printf("Input data to insert at tail (as last node): ");
            scanf("%d", &data);
            addLast(&deq, data);
            break;

      case 3:
            if (deq.nodeCount > 0){
              data = deleteFirst(&deq);
              printf("Deleted data from front: %d\n", data);
            }
            else{
              printf("Underflow, DEQ is empty\n");
            }

            break;
      case 4:
            if (deq.nodeCount > 0){
              data = deleteLast(&deq);
              printf("Deleted data from rear: %d\n", data);
            }
            else{
              printf("Underflow, DEQ is empty\n");
            }
            break;

      case 5:
            quit = 1;
            break;

      default:
            printf("Invalid option chosen, valid option is from 1 - 5\n");
    }
  }

  return 0;
}


void addFirst(DblList *lstPtr, int data){
  /*
    1. CREATE the new node dynamically using malloc,
    2. Assign the node content with data
    3. Initialize the prev and next pointer with NULL.
    4. IF THE nodeCount = 0 then
        head = tail = assign the address of the new node
       else
          P->NEXT = HEAD;
          HEAD->PREV = P
          HEAD = P;
       END IF

  */
  Node *p = (Node *)malloc(sizeof(Node));
  if(p == NULL){
    printf("Unable to create node for the double ended queue\n");
    return;
  }
  p->data = data;
  p->next = p->prev = NULL;
  if (lstPtr->nodeCount == 0){
    lstPtr->head = lstPtr->tail = p;
  }
  else{
    p->next = lstPtr->head;
    lstPtr->head->prev = p;
    lstPtr->head = p;
  }
  lstPtr->nodeCount++;
}

void addLast(DblList *lstPtr, int data){
  Node *p = (Node *)malloc(sizeof(Node));
  if(p == NULL){
    printf("Unable to create node for the double linked list\n");
    return;
  }
  p->data = data;
  p->next = p->prev = NULL;
  if (lstPtr->nodeCount == 0){
    lstPtr->head = lstPtr->tail = p;
  }
  else{
    lstPtr->tail->next = p;
    p->prev = lstPtr->tail;
    lstPtr->tail = p;
  }
  lstPtr->nodeCount++;
}



int deleteFirst(DblList *lstPtr){
  if (lstPtr->nodeCount == 0)
    return -999;
  Node *p = lstPtr->head;

  if (lstPtr->nodeCount == 1){
    lstPtr->head = lstPtr->tail = NULL;
  }
  else{
    lstPtr->head = lstPtr->head->next;
    lstPtr->head->prev = NULL;
  }
  int data = p->data;
  free(p);
  lstPtr->nodeCount--;
  return data;
}

int deleteLast(DblList *lstPtr){
  if (lstPtr->nodeCount == 0)
    return -999;

  Node *p = lstPtr->tail;
  if (lstPtr->nodeCount == 1){
    lstPtr->head = lstPtr->tail = NULL;
  }
  else{
    lstPtr->tail = lstPtr->tail->prev;
    lstPtr->tail->next = NULL;
  }
  int data = p->data;
  free(p);
  lstPtr->nodeCount--;
  return data;
}
