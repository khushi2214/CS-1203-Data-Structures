#include <stdio.h>
#include <stdlib.h>
#define BADVAL -9999

typedef struct node{
    int info;
    struct node *next;
}
NODE, *NODEPTR;
NODEPTR front, rear; 

typedef struct queue{
NODEPTR front, rear;
} QUEUE;

void init(QUEUE *q){
    &q->front = &q->rear = -1;
}

NODEPTR createNode(int val){
    NODEPTR p;
    p = (NODEPTR) malloc(sizeof(struct node));
    p->info = val;
    p->next = NULL;
    return p;
    }


int isEmpty(QUEUE *q){
    if (&q->front == -1) return 1;
    else return 0;
}

int delete(NODEPTR *afront, NODEPTR *arear){
    NODEPTR temp;
    int val;
    if (*afront == NULL) return BADVAL;
    else{
        temp = *afront;
        (*afront) = (*afront)->next;
        val = temp->info;
        free(temp);
        if (*afront == NULL)
            *arear = NULL;
        return val;
    }
}

void insert(NODEPTR *afront, NODEPTR *arear, int elm){
    NODEPTR temp;
    temp = createNode(elm);
    if (*afront == NULL){
        *afront = temp;
        *arear = temp;
    }
    else{
        (*arear)->next = temp;
        *arear = temp;
    }
}

void printQueue(NODEPTR front){
    NODEPTR temp;
    if (front == NULL){
        printf("Queue empty\n");
        return;
    }
    printf("<- F ");
    for (temp = front; temp!= NULL; temp = temp->next)
        printf("%d ", temp->info);
    printf("<- R\n");
}

int main(){

    QUEUE q;
    int elm, menu;
    while(1){
        printf("0. exit, 1. initialize, 2. delete, 3. insert, 4. print. Input Choice: ");
        scanf("%d", &menu);
        switch(menu){
        case 0: 
            exit(0);
        case 1: 
            init(q);
        break;
        case 2: 
            printf("Deleted Value %d\n",
            delete(q));
        break;
        case 3: 
            printf("Give element: ");
            scanf("%d", &elm);
            printf("Insert Flag %d\n", insert(q, elm));
        break;
        case 4: 
            printQueue(q);
        break;
            default: 
        printf("Wrong choice\n");
    }
    }
}
return 0;