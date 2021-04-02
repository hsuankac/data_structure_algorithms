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
int getSize(Stack *);

int getSize(Stack *sp){
    return sp -> size;
}

void push(Stack *sp, int value){
    if (sp->top == sp->size - 1){
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
    if (sp->top == -1){
        printf("Stack Underflow\n");
        return -9999;
    }
    int value;
    value = sp->item[sp->top];
    sp->top--;
    return value;

}

/**
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

int main() {
    Stack s1;
    init(&s1, 3);      
    printf("1. Push\n");
    printf("2. Pop\n");
    printf("3. Exit\n");
    int choice, value;
    while(1){
        printf("Enter choice: ");
        scanf("%d", &choice);
        printf("Size of Stack: %d\n", getSize(&s1));
        switch(choice){
            case 1: printf("Enter value: ");
                    scanf("%d", &value);
                    push(&s1, value); 
                    break;
            case 2:
                    value = pop(&s1);
                    if (value!=-9999){
                        printf("Popped data: %d\n", value);
                    }    
                    break;
            case 3: deallocate(&s1);
                    exit(0);
            default: printf("Invalid choice\n");   
        }   
    }
    return 0;
}

