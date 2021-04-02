#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *item;
    int top;
    int size;
}Stack;

// prototype declarations
void init(Stack *, int);
void push(Stack *, int);
int pop(Stack *);
void deallocate(Stack *);
int isUnderflow(Stack *);
int isOverflow(Stack *);
void printBinary(unsigned int);
int getSize(Stack *);


int getSize(Stack *sp){
    return sp -> size;
}


void push(Stack *sp, int value){
    if (isOverflow(sp)){
        int *temp;
        temp = (int *)malloc(sizeof(int) * sp->size * 2);
        if (temp == NULL){
            printf("Stack overflow\n");
            return;
        }
        int i;
        for(i=0; i<=sp->top;i++){
            temp[i] = sp->item[i];
        }
        free(sp->item);
        sp->item = temp;
        sp->size *= 2;
    }
    
    sp->top++;
    sp->item[sp->top] = value;
    
}

int pop(Stack *sp){
    if (isUnderflow(sp)){
        printf("Stack Underflow\n");
        return -9999;
    }
    int value;
    value = sp->item[sp->top];
    sp->top--;
    return value;

}

/*
 The init method this time dynamically allocates the array
 sp - pointer to the stack object.
 size - size of the stack
*/
void init(Stack *sp, int size){
    sp->top = -1;
    // using malloc allocating the stack dynamically

    sp->item = (int *)malloc(sizeof(int) * size);
    if (sp->item == NULL){
        printf("Unable to allocate memory\n");
        exit(1);
    }
    sp->size = size;
}

/**
 deallocate function will deallocate the 
 dynamically allocated array for the stack.
*/
void deallocate(Stack *sp){
    if (sp->item!=NULL)
        free(sp->item);
    sp->top = -1;
    sp->size = 0;
}

int isOverflow(Stack *sp){
    return sp->top == sp->size -1;
}

int isUnderflow(Stack *sp){
    return sp->top == -1;
}


void printBinary(unsigned int n){
    Stack s;
    int temp = n;
    const int BASE = 2;
    init(&s, 10);

    while(n>0){
        int rem = n % BASE;
        push(&s, rem);
        n /= BASE;
    }
    printf("Bonary equivalent of %d is: \n", temp);
    while(!isUnderflow(&s)){
        printf("%d", pop(&s));
    }
    deallocate(&s);
}

int main() {
    printBinary(18);
    return 0;
}

