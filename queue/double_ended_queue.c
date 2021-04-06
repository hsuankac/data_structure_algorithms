#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

typedef struct {
  int item[SIZE];
  int rear, front;
}Queue;

// function prototypes
void initQueue(Queue *);
void ins_at_rear(Queue *, int );
int del_from_rear(Queue *);
void ins_at_front(Queue *, int );
int del_from_rear(Queue *);

void initQueue(Queue *qp){
  qp -> front = 0;
  qp-> rear = -1;
}

void ins_at_rear(Queue *qp, int v){
  if (qp->rear == SIZE - 1){
    printf("Unable to insert at the rear end\n");
    return;
  }
  qp->rear++;
  qp->item[qp->rear] = v;
}
int del_from_rear(Queue *qp){
  if (qp->front > qp->rear){
    return -9999;
  }
  int v = qp->item[qp->rear];
  qp->rear --;
  return v;
}
void ins_at_front(Queue *qp, int v){
  if (qp->front == 0){
    printf("Unable to insert at the front end\n");
    return;
  }
  qp->front --;
  qp->item[qp->front] = v;
}
int del_from_front(Queue *qp){
  printf("You need to implement this by yourself\n");
  return -9999;
}


void menu(){
  printf("----------FIFO Queue Operations----------\n");
  printf("-----------------------------------------\n");
  printf("1. Insert at rear\n");
  printf("2. Insert at front\n");
  printf("3. Delete from rear\n");
  printf("4. Delete from front\n");
  printf("5. Quit\n");
  printf("-----------------------------------------\n\n");
}

int main() {
  Queue q;
  initQueue(&q);
  int quit = 0;
  int value;
  menu();
  while(!quit){
    int choice;
    printf("Input your option: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
              printf("Input value to insert at rear: ");
              scanf("%d", &value);
              ins_at_rear(&q, value);
              break;
      case 2:
              printf("Input value to insert at front: ");
              scanf("%d", &value);
              ins_at_front(&q, value);
              break;
      case 3:
              value = del_from_rear(&q);
              if (value == -9999)
                printf("Queue underflow\n");
              else
                printf("Deleted from front, value: %d\n", value);
              break;
      case 4:
              value = del_from_front(&q);
              if (value == -9999)
                printf("Queue underflow\n");
              else
                printf("Deleted from front, value: %d\n", value);
              break;
      case 5:
              quit = 1;
              break;
      default: printf("Invalid choice, valid options are 1 - 5\n");
    }

  }



  return 0;
}
