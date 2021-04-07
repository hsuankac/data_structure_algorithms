#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 
* structure definition for a node
*/

typedef struct Node{
    int data;
    struct Node *next; // for storing the address of immediate next node
    struct Node *prev; // for storing the address of immediate previous node
}Node;

typedef struct{
    struct Node *head; // address of first node. NULL initially
    struct Node *tail; // address of last node. NULL initially
    int nodeCount; // count of total number of nodes. 0 initially
}DblList;

// function prototype
/**
* initializes the doubly linked list object that is passed
**/
void initList(DblList *lstptr);
/**
 * add a new node with the data content data (passed as argument)
 * as the first node
 */
void addFirst(DblList *lstptr, int data);
/**
 * add a new node with the data content data (passed as parameter)
 * as the last node
 */
void addLast(DblList *lstptr, int data);
/**
 * creates the doubly linkedlist reading data from file supplied as parameter 
 * The linked list is created by adding the nodes at the end of the list
 */
int loadFromFile(DblList *lstptr, char *fileName);
/**
 * creates a doubly linkedlist by generating n random numbers, nodes are added at the end
 */
void createListFromRandomNumbers(DblList *lstptr, int n);
/**
 * prints the detail of the doubly linkedlist included data and the pointers in 
 * each of the node from the first to the last node
 */
void printListDetail(DblList *list);
/**
 * prints content of each node from the first to the last node
 */
void printForward(DblList *lstptr);
/**
 * prints content of each node starting from last upto first
 */
void printReverse(DblList *lstptr);
/**
 * searches into the linked list for the content target, if found returns the pointer to the node
 * that contains the target, NULL otherwise
 */
Node *find(DblList *lstptr, int target);
/**
 * inserts a newnode after the target node with data supplied as parameter
 * returns 1 if the insertion is successfully done, 0 otherwise
 */
int insertAfter(DblList *lstptr, int target, int data);
/**
 * inserts a newnode before the target node with data supplied as parameter
 * returns 1 if the insertion is successfully done, 0 otherwise
*/
int insertBefore(DblList *lstptr, int target, int data);
/** 
 * deletes the first node of the doubly linked list, returns 1 if deletion is successful,
 * 0 otherwise
 */
int deleteFirst(DblList *lstptr);
/**
 * deletes the last node of the doubly linked list, returns 1 if deletion is successful,
 * 0 otherwise
 */
int deleteLast(DblList *lstptr);
/** 
 * deletes the node with the target, returns 1 if deletion is successful,
 * 0 otherwise
 */
int deleteTarget(DblList *lstptr, int target);
/**
 * menu for user interface
 */
void menu();

void initList(DblList *lstptr){
    lstptr->head = NULL;
    lstptr->tail = NULL;
    lstptr->nodeCount = 0;
}

int loadFromFile(DblList *lstptr, char *filename){
    FILE *inputFile = fopen(filename, "r");
    if (inputFile == NULL){
        return 0;
    }
    int data;
    fscanf(inputFile, "%d", &data);
    while(!feof(inputFile)){
        addLast(lstptr, data);
        fscanf(inputFile, "%d", &data);
    }
    fclose(inputFile);
    return 1;
}

void createListFromRandomNumbers(DblList *lstptr, int n){
    int i;
    srand(time(NULL));
    for(i = 1; i<=n; i++){
        int k = rand() % 1000;
        addLast(lstptr, k);
    }
}

void addFirst(DblList *lstptr, int data){
    /*
        1. Create the new node dynamically using malloc
        2. Assign the node content with data
        3. Initialize the prev and next pointer with NULL
        4. If the nodeCount is 0 then
            head = tail = assign the address of the new node
           else
            p->next = head;
            head->prev = p;
            head = p;
           End if
    */
   Node *p = (Node *)malloc(sizeof(Node));
   if(p == NULL){
       printf("Unable to create the double linked list\n");
       return;
   }
   p->data = data;
   p->next = p->prev = NULL;
   if(lstptr->nodeCount == 0){
       lstptr->head = lstptr->tail = p;
   }
   else{
       p->next = lstptr->head;
       lstptr->head->prev = p;
       lstptr->head = p;
   }
   lstptr->nodeCount++;
}

void addLast(DblList *lstptr, int data){
   Node *p = (Node *)malloc(sizeof(Node));
   if(p == NULL){
       printf("Unable to create the double linked list\n");
       return;
   }
   p->data = data;
   p->next = p->prev = NULL;
   if(lstptr->nodeCount == 0){
       lstptr->head = lstptr->tail = p;
   }
   else{
       lstptr->tail->next = p;
       p->prev = lstptr->tail;
       lstptr->tail = p;
   }
   lstptr->nodeCount++;
}

void printForward(DblList *lstptr){
    Node *p = lstptr->head;
    if (p ==NULL){
        printf("Linked list is empty\n");
        return;
    }
    printf("Content of the double linked list: \n");
    while(p != NULL){
        printf("%4d", p->data);
        p = p->next;
    }
    printf("\n--End--\n");
}

void printReverse(DblList *lstptr){
    Node *p = lstptr->tail;
    if (p ==NULL){
        printf("Linked list ins empty\n");
        return;
    }
    printf("Content of the double linked list: \n");
    while(p != NULL){
        printf("%4d", p->data);
        p = p->prev;
    }
    printf("\n--End--\n");
}

Node *find(DblList *lstptr, int target){
    Node *p;
    for(p=lstptr->head; p!=NULL; p=p->next){
        if(p->data ==target){
            return p;
        }
    }
    return NULL;
}

int insertAfter(DblList *lstptr, int target, int data){
    Node *p = find(lstptr, target);
    if(p==NULL){
        return 0;
    }
    // if the address is the last node
    if(p == lstptr->tail){
        addLast(lstptr, data);
    }
    else{
        Node *q = (Node *)malloc(sizeof(Node));
        q->data = data;
        if(q==NULL){
            printf("Unable to create node\n");
            return 0;
        }
        q->next = p->next;
        q->prev = p;
        p->next = q;
        q->next->prev = q;
    }
    lstptr->nodeCount++;
    return 1;
}

int insertBefore(DblList *lstptr, int target, int data){
    Node *p = find(lstptr, target);
    if(p==NULL){
        return 0;
    }
    // if the address is the first node
    if(p == lstptr->head){
        addFirst(lstptr, data);
    }
    else{
        Node *q = (Node *)malloc(sizeof(Node));
        q->data = data;
        if(q==NULL){
            printf("Unable to create node\n");
            return 0;
        }
        q->prev = p->prev;
        q->next = p;
        p->prev = q;
        q->prev->next = q;
    }
    lstptr->nodeCount++;
    return 1;
}

int deleteFirst(DblList *lstptr){
    if(lstptr->nodeCount == 0){
        return 0;
    }
    if(lstptr->nodeCount == 1){
        lstptr->head = lstptr->tail = NULL;
    }
    else{
        lstptr->head = lstptr->head->next;
        lstptr->head->prev = NULL;
    }
    lstptr->nodeCount--;
    return 1;
}

int deleteLast(DblList *lstptr){
    if(lstptr->nodeCount == 0){
        return 0;
    }
    if(lstptr->nodeCount == 1){
        lstptr->head = lstptr->tail = NULL;
    }
    else{
        lstptr->tail = lstptr->tail->prev;
        lstptr->tail->next = NULL;
    }
    lstptr->nodeCount--;
    return 1;
}

int deleteTarget(DblList *lstptr, int target){
    Node *p = find(lstptr, target);
    if(p==NULL){
        return 0;
    }
    if(p==lstptr->head){
        return deleteFirst(lstptr);
    }
    else if(p==lstptr->tail){
        return deleteLast(lstptr);
    }
    else{
        p->next->prev = p->prev;
        p->prev->next = p->next;
        free(p);
        lstptr->nodeCount--;
        return 1;
    }
}

void menu(){
    printf(" Doubly linked list operations\n"); 
    printf("--------------------------------\n");
    printf("1. Load fron file\n"); // load integer data from file and will create the list
                                   // by using the insert_at_tail operation (menu option 3)
    printf("2. Create list with random numbers\n");
    printf("3. Add first\n"); // Inserting a new node as the first node 
    printf("4. Add last\n"); // Inserting a new node as the last node
    printf("5. Print list (detail)\n"); // Printing the linked list in detail
                                        // including the data and pointer in each node
    printf("6. Print list first to last (data only)\n"); // Prints the integer data in each node from first to last node 
    printf("7. Print list last to first (data only)\n"); // Prints the integer data in each node from last to first node 
    printf("8. Find\n"); // Find if an integer exists in a node from the start in the list
    printf("9. Insert after\n");
    printf("10. Insert before\n");
    printf("11. Delete last\n"); // Delete the first node
    printf("12. Delete first\n"); // Delete the last node
    printf("13. Delete a target node\n"); // Delete a particular node, if that exists
    printf("14. Quit\n"); // terminate each node
}

int main(){
    DblList list;
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
            case 1: success = loadFromFile(&list, "data.txt");
                    if (success == 1){
                        printf("File has been loaded successfully\n");
                    }
                    else{
                        printf("File loaded wrong\n");
                    }
                    break;
            case 2: printf("Enter number of integers to be gneerated and added into the list: ");
                    scanf("%d", &n);
                    createListFromRandomNumbers(&list, n);
                    break;
            case 3: // ask to input
                    printf("Input data to insert at head (as first node): ");
                    scanf("%d", &data);
                    addFirst(&list, data);
                    break;
            case 4: printf("Input data to insert at tail (as last node): ");
                    scanf("%d", &data);
                    addLast(&list, data);
                    break;
            // case 5: printListDetail(&list);
            //         break;
            case 6: printForward(&list);
                    break;
            case 7: printReverse(&list);
                    break;
            case 8: // call find
                    printf("Enter target: ");
                    scanf("%d", &target);
                    current = find(&list, target);
                    if(current==NULL){
                        printf("Linkedlist does not contain the target specified\n");
                    }
                    else{
                        printf("Target exists in the linked list\n");
                    }
                    break;
            case 9: printf("Enter target: ");
                    scanf("%d", &target);
                    printf("Input data: ");
                    scanf("%d", &data);
                    if(insertAfter(&list, target, data) == 1){
                        printf("Insert after was successful\n");
                    }
                    else{
                        printf("Insert after failed\n");
                    }
                    break;
            case 10: printf("Enter target: ");
                     scanf("%d", &target);
                     printf("Input data: ");
                     scanf("%d", &data);
                     if(insertBefore(&list, target, data) == 1){
                         printf("Insert before was successful\n");
                     }
                     else{
                        printf("Insert brefore failed\n");
                     }
                     break;
            case 11: if(deleteLast(&list)){
                        printf("Last node deleted successfully\n");
                     }
                     else{
                        printf("unable to delete last node\n");
                     }
                     break;
            case 12: if(deleteFirst(&list)){
                        printf("First node deleted successfully\n");
                     }
                     else{
                        printf("unable to delete first node\n");
                     }
                     break;
            case 13: printf("Enter target: ");
                     scanf("%d", &target);
                     if(deleteTarget(&list, target)){
                         printf("Target node deleted successfully\n");
                     }
                     else{
                         printf("Unable to delete the target node\n");
                     }
                     break;
            case 14: quit = 1;
                     break;
            default: printf("Invalid option chosen, valid option is from 1 - 11\n");
        }
    }
    return 0;
}