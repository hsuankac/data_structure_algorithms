#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node{
    int data;
    struct Node *next;
}Node;

typedef struct{
    struct Node *head;
    struct Node *tail;
    int nodeCount;
}LinkedList;

// function prototype 
void initList(LinkedList *);
int loadFromFile(LinkedList *, char *);
void createListFromRandomNumbers(LinkedList *, int);
void insertAtHead(LinkedList *, int);
void insertAtTail(LinkedList*, int);
void printListDetail(LinkedList *);
void printList(LinkedList *);
Node * find(LinkedList *, int, Node **);
int deleteFirst(LinkedList *);
int deleteLast(LinkedList *);
int deleteTarget(LinkedList *, int);
void reverse(LinkedList *);

void initList(LinkedList *listptr){
    listptr -> head = NULL; // NULL pointer to initialize
    listptr -> tail = NULL;
    listptr -> nodeCount = 0;
}

void insertAtTail(LinkedList *listptr, int data){
    // create the node
    Node *newNodePtr = (Node*)malloc(sizeof(Node));
    if(newNodePtr == NULL){
        printf("Unable to allocate new node \n");
        return;
    }
    newNodePtr->data = data;
    newNodePtr->next = NULL;

    if (listptr->nodeCount ==0){
        // this is the case when the list is empty
        listptr->head = newNodePtr;
        listptr->tail = newNodePtr;
    }
    else{
        // this is the case when the list is not empty
        listptr->tail->next = newNodePtr;
        listptr->tail = newNodePtr;
    }
    listptr->nodeCount++;
} 

void insertAtHead(LinkedList *listptr, int data){
    // create the node
    Node *newNodePtr = (Node*)malloc(sizeof(Node));
    if(newNodePtr == NULL){
        printf("Unable to allocate new node \n");
        return;
    }
    newNodePtr->data = data;
    newNodePtr->next = NULL;

    if (listptr->nodeCount ==0){
        // this is the case when the list is empty
        listptr->head = newNodePtr;
        listptr->tail = newNodePtr;
    }
    else{
        // this is the case when the list is not empty
        newNodePtr->next = listptr->head;
        listptr->head = newNodePtr;
    }
    listptr->nodeCount++;
}

void printListDetail(LinkedList *listptr){
    if(listptr->nodeCount == 0){
        printf("Linked list is empty\n");
        return;
    }
    printf("Printing linked list in details\n");
    printf("HEAD: %p\n", listptr->head);
    Node *current = listptr->head;
    int counter = 1;
    while(current != NULL){
        printf("%d. (%p)[%d|%p]\n", counter, current, current->data, current->next);
        current = current->next;
        counter++;
    }
    printf("TAIL: %p\n", listptr->tail);
}

void printList(LinkedList *listptr){
    if(listptr->nodeCount == 0){
        printf("Linked list is empty\n");
        return;
    }
    Node *current = listptr->head;
    while(current != NULL){
        printf("%d\n", current->data);
        current = current->next;
    }
}

Node * find(LinkedList *listptr, int target, Node **pvrPtr){
    Node* current = listptr->head;
    *pvrPtr = NULL;
    while(current != NULL){
        if(current->data == target){
            break;
        }
        *pvrPtr = current;
        current = current->next;
    }
    return current;
}

int loadFromFile(LinkedList *listptr, char *filename){
    FILE *inputFile = fopen(filename, "r");
    if (inputFile == NULL){
        return 0;
    }
    int data;
    fscanf(inputFile, "%d", &data);
    while(!feof(inputFile)){
        insertAtTail(listptr, data);
        fscanf(inputFile, "%d", &data);
    }
    fclose(inputFile);
    return 1;
}

void createListFromRandomNumbers(LinkedList *listptr, int n){
    int i;
    srand(time(NULL));
    for(i = 1; i<=n; i++){
        int k = rand() % 1000;
        insertAtTail(listptr, k);
    }
}

int deleteFirst(LinkedList *listptr){
    if(listptr->nodeCount == 0){
        return -9999;
    }
    Node *first = listptr->head;
    int data = first->data;
    if(listptr->nodeCount == 1){
        // there is only one node
        listptr->head = NULL;
        listptr->tail = NULL;
    }
    else{
        // there are many nodes, and we need to delete the first
        listptr->head = first->next;
    }
    free(first);
    listptr->nodeCount--;
    return data;
}

int deleteLast(LinkedList *listptr){
    if(listptr->nodeCount == 0){
        return -9999;
    }
    Node *current = listptr->head;
    Node *last = listptr->tail;
    int data = last->data;
    if(listptr->nodeCount == 1){
        // there is only one node
        listptr->head = NULL;
        listptr->tail = NULL;
    }
    else{
        // there are many nodes and we need to delete the second last node and assign that to tail
        while(current->next != listptr->tail){
            current = current->next;
        }
        listptr->tail = current;
        current->next = NULL;
    }
    free(last);
    listptr->nodeCount--;
    return data;
}

int deleteTarget(LinkedList *listptr, int target){
    Node *current = NULL, *prev = NULL;
    current = find(listptr, target, &prev);
    if(current == NULL){
        return -9999;
    }
    int data = current->data;
    if(current == listptr->head){
        // if the target is the first node
        return deleteFirst(listptr);
    }
    else if(current == listptr->tail){
        return deleteLast(listptr);
    }
    else{
        
        prev->next = current->next;
        free(current);
        listptr->nodeCount--;
        return data;
    }
}

void reverse(LinkedList *listptr){
    if(listptr->nodeCount <=1){
        return;
    }
    // declaring 3 Node pointers for doing the reversal
    Node *p, *q, *r;
    // p is current node, q is just previous to p and r is just immediate next to p
    q = NULL;
    p = listptr->head;
    r = p->next;
    while(1){
        // reverse the link
        p->next = q;
        if(p == listptr->tail){
            break;
        }
        // shift the pointers towards right
        q = p;
        p = r;
        r = r->next;
    }
    listptr->tail = listptr->head;
    listptr->head = p;
}

void menu(){
    printf(" Singly linked list operations\n"); 
    printf("--------------------------------\n");
    printf("1. Load fron file\n"); // load integer data from file and will create the list
                                   // by using the insert_at_tail operation (menu option 3)
    printf("2. Insert at head\n"); // Inserting a new node as the first node 
    printf("3. Insert at tail\n"); // Inserting a new node as the last node
    printf("4. Print list (detail)\n"); // Printing the linked list in detail
                                        // including the data and pointer in each node
    printf("5. Print list (data only)\n"); // Printing the integer data in each node
    printf("6. Find\n"); // Find an integer exist in the node from the start in the list
    printf("7. Delete first\n"); // Delete the first node
    printf("8. Delete last\n"); // Delete the last node
    printf("9. Delete a target node\n"); // Delete a particular node, if the exists
    printf("10. Reverse\n"); // Will physically reverse the list
    printf("11. Create list with random numbers\n");
    printf("12. Quit\n"); // terminate each node
}

int main(){
    LinkedList list;
    initList(&list);
    menu();
    int quit = 0;
    int choice;
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
            case 2: printf("Input data to insert at head (as first node): ");
                    scanf("%d", &data);
                    insertAtHead(&list, data);
                    break;
            case 3: printf("Input data to insert at tail (as last node): ");
                    scanf("%d", &data);
                    insertAtHead(&list, data);
                    break;
            case 4: printListDetail(&list);
                    break;
            case 5: printList(&list);
                    break;
            case 6: printf("Enter target number: \n");
                    scanf("%d", &data);
                    current = find(&list, data, &prev);
                    if (current == NULL){
                        printf("Target not found in the linked list\n");
                    }
                    else{
                        printf("Target node exists, address of the target node: %p, previous: %p", current, prev);
                    }
                    break;
            case 7: data = deleteFirst(&list);
                    if(data ==-9999){
                        printf("Linked list is empty\n");
                    }
                    else{
                        printf("First node has been deleted, data: %d\n", data);
                    }
                    break;
            case 8: data = deleteLast(&list);
                    if(data == -9999){
                        printf("Linked list is empty\n");
                    }
                    else{
                        printf("Last node has been deleted, data: %d\n", data);
                    }
                    break;
            case 9: printf("Enter target to find: ");
                    scanf("%d", &target);
                    data = deleteTarget(&list, target);
                    if(data == -9999){
                        printf("Target %d does not exist in the list\n", target);
                    }
                    else{
                        printf("Target node with data: %d, deleted successfully\n", data);
                    }
                    break;
            case 10: reverse(&list);
                     break;
            case 11: printf("Enter number of integers to be generated\n");
                     scanf("%d", &n);
                     createListFromRandomNumbers(&list, n);
                     break;
            case 12: quit = 1;
                     break;
            default: printf("Invalid choice\n");
        }
    }
    return 0;
}