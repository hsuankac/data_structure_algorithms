#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node{
  int data;
  struct Node *next;
}Node;

typedef struct {
  struct Node *tail;
  int nodeCount;
}CircularLinkedList;

// function prototypes
void initList(CircularLinkedList *);
void createListFromRandomNumbers(CircularLinkedList *, int);
void insertNode(CircularLinkedList *, int);
void printList(CircularLinkedList *);
Node * find(CircularLinkedList *, int);
int deleteNode(CircularLinkedList *);

// to initialize the linkedlist object
// Input parameter: listp is the pointer to linkedlist object
// Precondition: CircularLinkedList object pointed by lstptr must be existing.
// Return Value: Nothing
void initList(CircularLinkedList *lstPtr){
  lstPtr->tail = NULL;
  lstPtr->nodeCount = 0;
}



// To add a new node at the end of the CircularLinkedList
// Input parameters: pointer to struct CircularLinkedList, an integer data that will
//                   be the content  of the new node.
// Precondition: The linkedList object must be existing.
// Return Value: Nothing
void insertNode(CircularLinkedList *lstPtr, int data){

  Node *newNodePtr = (Node*)malloc(sizeof(Node));
  if (newNodePtr == NULL){
    printf("Unable to allocate new node\n");
    return;
  }
  newNodePtr->data = data;

  if (lstPtr->nodeCount == 0){
    newNodePtr->next = newNodePtr;
  }
  else{
    newNodePtr->next = lstPtr->tail->next;
    lstPtr->tail->next = newNodePtr;
  }

  lstPtr->tail = newNodePtr;
  lstPtr->nodeCount++;

}

void printList(CircularLinkedList *lstPtr){
  if (lstPtr->nodeCount == 0){
    printf("Linked list is empty\n");
    return;
  }
  int done = 0;
  Node *current = lstPtr->tail->next;
  while(!done){
    printf("%4d", current->data);
    // check if we have printed the content of the last node
    if (current == lstPtr->tail){
      done = 1;
    }
    else{
      current = current->next;
    }
  }
  printf("\n");
}

Node * find(CircularLinkedList *lstPtr, int target){
  if (lstPtr->nodeCount == 0)
    return NULL;
    int done = 0;
    Node *current = lstPtr->tail->next;
    while(!done){
      if (current->data == target){
        return current;
      }
      if (current == lstPtr->tail){
        done = 1;
      }
      else{
        current = current->next;
      }
    }
  return NULL;
}

void createListFromRandomNumbers(CircularLinkedList *lstPtr, int n){
  int i;
  srand(time(NULL));
  for(i = 1; i<=n; ++i){
      int k = rand() % 1000;
      insertNode(lstPtr, k);
  }
}

int deleteNode(CircularLinkedList *lstPtr){
  if (lstPtr->nodeCount == 0){
    return -9999;
  }
  Node *p = lstPtr->tail->next;
  int data = p->data;
  if (lstPtr->tail == lstPtr->tail->next){
    lstPtr->tail = NULL;
  }
  else{
    lstPtr->tail->next = p->next;
  }
  free(p);
  lstPtr->nodeCount--;
  return data;
}

void menu(){
  printf("    Circular Linked List Operations\n");
  printf("----------------------------------------\n");

  printf("1. Create list with random numbers\n");
  printf("2. Insert\n");          // inserting a new node as the first node
  printf("3. Delete\n");          // inserting a new node as the last node
  printf("4. Print List (data only)\n");  // prints the integer data in each node
  printf("5. Find\n");                    // finds if an integer exisits in a node from
                                          // the start in the list
  printf("6. Quit\n");                   // to terminate each node
}

int main(){
  CircularLinkedList list;
  initList(&list);
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
            printf("Enter number of integers to be generated and added into the list: ");
            scanf("%d", &n);
            createListFromRandomNumbers(&list, n);
            break;
      case 2:
            // ask to input
            printf("Input data to insert: ");
            scanf("%d", &data);
            insertNode(&list, data);
            break;
      case 3:
            data = deleteNode(&list);
            if (data == -9999){
              printf("Linkedlist is empty\n");
            }
            else{
              printf("First node has been deleted, data: %d\n", data);
            }
            break;

      case 4:
              printList(&list);
              break;

      case 5:
            printf("Enter target to find: ");
            scanf("%d", &data);
            current = find(&list, data);
            if (current == NULL){
              printf("Target not found in the Linkedlist\n");
            }
            else{
              printf("Target node exists, address of the target node: %p\n", current);
            }
            break;
      case 6:
            quit = 1;
            break;
      default:
            printf("Invalid option chosen, valid option is from 1 - 11\n");
    }
  }

  return 0;
}
