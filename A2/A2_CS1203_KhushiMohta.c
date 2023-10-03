//Inorder traversal without recursion, using a stack of node pointers
 
#include <stdio.h>
#include <stdlib.h>

//Defining a structure for a node 
typedef struct node{ 
    int data; // Each node contains an integer value referred to as data  
    struct node *left, *right; //Each node will contain pointers to other nodes, the left child and the right child  
} NODE; // This function makes calling functions easier

//Defining a structure for a stack
typedef struct stack {
    int stackpointer; //Indicates the index of the array where the next element will be pushed/popped 
    NODE** arr; //Using a pointer to a pointer for dynamic allocation of nodes 
} STACK;

//Initialising a stack 
void init (STACK *s) {
    s->stackpointer=-1; //Initialsing the stack pointer (empty stack)
    s->arr = (NODE**)malloc(sizeof(NODE*)); //Dynamic memory allocation for stack   
}

//Checking if the stack is empty 
int empty(STACK *s){
    s->stackpointer == -1; 
}

//Defining a function to push a node into the stack 
int push (STACK *s, NODE *elm) {
        s->arr[++(s->stackpointer)] = elm; //Increment of stack pointer and assinging node to the stack 
        return 1; //For a successful push 
    }

//Defining a function to pop a node from a stack 
NODE* pop(STACK *s){
        return s->arr[(s->stackpointer)--]; //To get the node at the current stack pointer and then decrement the pointer
    }

//Function to perform inorder traversal 
void inorder (NODE* root) {
    if (root == NULL) return; //To check of the tree is empty 
    STACK st; //Creating a stack to hold tree node pointers 
    init (&st); //Initialising the stack 

    NODE* current = root; //Starting with the root node 
    while (current != NULL || empty(&st)) { //Continue traversal until there are nodes or the stack is not empty
        while (current != NULL) {
            push (&st, current); //Pushing the current node onto the stack 
            current = current -> left; //Move to the left child 
        }
        current = pop(&st); //To pop a node from the stack
        printf("%d ", current->data); //Printing the current node's data
        current = current -> right; //Move to the right  
    }
    free (st.arr); //Free the dynamically allocated memory for the stack
}

int main() {
    struct node* root = malloc(sizeof(struct node));
    root->data=10;
    root->left = malloc(sizeof(struct node));
    root->right = malloc(sizeof(struct node));
    root->right->data = 15;
    root->left->data=5;
    root->left->left=NULL;
    root->left->right=NULL;
    root->right->left=NULL;
    root->right->right=NULL;

    inorder(root);
}
