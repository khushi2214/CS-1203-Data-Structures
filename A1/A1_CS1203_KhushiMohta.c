#include <stdio.h>
#include <stdlib.h>
#define BADVAL -9999

//Defining a structure for a node in the queue 
typedef struct node{
    int info; //Information stored in the node 
    struct node *nextNode; //Pointer which points to the next node in a queue 
} NODE, *NODEPTR; //This function makes calling functions easier, instead of writing struct node, we can write NODE

//Defining a structure for the queue 
typedef struct queue{
    NODEPTR front, rear; //Pointers to the front (first element) and rear (last element) of the queue respectively
} QUEUE; //Instead of writing struct queue, we can simply write QUEUE when we want to call this function
QUEUE q = {NULL, NULL}; //Initialising an empty queue called q, the front and rear places are declared NULL

//Defining a fucntion to create a new node in the queue 
NODEPTR createNode(int val){
    NODEPTR newNode;
    newNode = (NODEPTR) malloc(sizeof(struct node)); //Menory allocation for a new node wth the function malloc 
    newNode->info = val; //Set the data (info) in the new node 
    newNode->nextNode = NULL; //Initialising the next pointer to NULL
    return newNode;
    }

//Defining a function to check if the queue is empty 
int empty(QUEUE *q){
    if (q->front == NULL) // Checking if the front pointer of the queue is NULL, because that indicates an empty queue
        return 1; //If it is empty, then return 1
    else {
        return 0; //If it is not empty then return 0
    }
}

//Defining a function to delete an element (first one) from the queue 
int delete(QUEUE *q){
    NODEPTR temp;
    int val;
    
    if (empty(q)) 
        return BADVAL; //Return BADVAL if the queue is empty and there's an attemp to dequeue an empty queue 

    else{
        temp = q->front; //Using a temporary variable, store a pointer to the front node 
        val = temp->info; //Getting the data from the front node 
        q->front = q->front->nextNode; //Moving the front pointer to the next node 
        free(temp); //Free up memory allocated by mallocto old, now empty node 
    }
    if (q->front == NULL)
            q->rear = NULL; //If queue is empty, update rear pointer to NULL because in an empty queue, both front and rear pointers should be null
    return val; //Return the value that was dequeued 
}

//Defining a function to insert an element (last one) into the queue
int insert(QUEUE *q, int elm){
    NODEPTR temp;
    temp = createNode(elm); //The element to be inserted needs to be put into a new node, which has to be created 

    if (empty(q)){
        q->front = q->rear = temp; //If the queue is empty, then declare both the front and the rear as the value of the new node 
    }
    else{
        q->rear->nextNode = temp; //New node gets added to the end if there are pre existing elements 
        q->rear = temp; //Updating the rear pointer to the new node 
    }
    return 0; //For successful insertion 
}

//Defining a function to print the elements of a queue
void printQueue(QUEUE *q){
    NODEPTR temp = q->front; //Initialise temp, a temporary pointer to the front of the queue 
    if (empty(q)){
        printf("Queue empty\n"); //If the queue is empty, then let the user know by printing a message 
        return;
    }
    //printf("<- F ");
    while  (temp!= NULL){ //Continue loop as long as there are no more elements to print 
        printf("%d ", temp->info); //Print the value of the current node pointed to by the temporary pointer, temp 
    temp = temp->nextNode; //Move the temp pointer to the next node 
    }
    printf("\n");
    //printf("<- R\n");
}
       
int main(){
    int elm, menu;

    while(1){
        printf("0. exit,  1. delete, 2. insert, 3. print. Input Choice: ");
        scanf("%d", &menu); 
        switch(menu){ //Begin a switch statement based on the value of the 'menu' variable
        case 0: 
            exit(0);
        case 1: 
            printf("Deleted Value %d\n", delete(&q)); //& gete the memory address of a varible, here, the queue q 
            break;
        case 2: 
            printf("Give element: ");
            scanf("%d", &elm);
            insert(&q, elm);
            break;
        case 3: 
            printQueue(&q);
            break;
        default: 
            printf("Wrong choice\n");
        }
    }
    return 0;
}
