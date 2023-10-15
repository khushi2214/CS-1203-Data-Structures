//Complete the AVL Tree code by adding a deletion routine

#include <stdio.h>
#include <stdlib.h>

struct Node { //representing an AVL tree
    int k; //unique key value associated with every node 
    struct Node* l;
    struct Node* r;
    int h; //height value
};

int max(int a, int b) { //function to calculate the maximum of 2 integers, which will be used for detetrmining the height and the balance factor
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int height(struct Node* node) {
    if (node == NULL)
        return 0; //indicates that an empty sub-tree has a height of 0
    return node->h; //each node has a height value, and this retrieves that 
}

void newheight(struct Node* node) { //this function emakes sure that the height of the node reflects the height of its sub-tree
    if (node == NULL)
        return;
    node->h = 1 + max(height(node->l), height(node->r)); //to calculate height based on the maximum of the left children and the right children's heights
}

struct Node* create(int k) { //creating a new node with a given key
    struct Node* new = (struct Node*)malloc(sizeof(struct Node)); //memory allocation
    //initalising the parts of a node
    new->k = k;
    new->l = NULL;
    new->r = NULL;
    new->h = 1;
    return new;
}

struct Node* rotateR(struct Node* y) { //function to perform a right rotation
    //getting the left child and the right child (right sub-tree of x)
    struct Node* x = y->l;
    struct Node* RsubtreeX = x->r;

    x->r = y; //make y the right child of x
    y->l = RsubtreeX; //make the right sub-tree of x the left child of y 

    newheight(y); //updating the height of node y
    newheight(x); //updating the height of node x

    return x; //x is now the root of the rotated sub-tree
}

struct Node* rotateL(struct Node* x) { //function to perform a left rotation
    struct Node* y = x->r;
    struct Node* RsubtreeX = y->l;

    y->l = x; //make x the left child of y
    x->r = RsubtreeX; //make the right sub-tree of x the right child of x 

    newheight(x);
    newheight(y);

    return y; //new root node
}

int getbalf(struct Node* node) {
    if (node == NULL)
        return 0;
    return height(node->l) - height(node->r); //difference between the left and right sub-tree 
}

struct Node* min(struct Node* node) { //to find the minimum node in a tree 
    struct Node* current = node; //temporary pointer current initalised to the same node passed as an argument
    while (current->l != NULL) //loop continues as long as the left node has a child
        current = current->l; //current pointer updated to point to its left child child in each iteration
    return current; //this is now the node with the minimum key
}

struct Node* deletion(struct Node* root, int k) {
    if (root == NULL)
        return root; //if tree is empty then return the unchanged tree 

    if (k < root->k)
        root->l = deletion(root->l, k); //recursively searching for the key k in the left sub-tree
    else if (k > root->k)
        root->r = deletion(root->r, k); //recursively searching for the key k in the right sub-tree
    else {
        if ((root->l == NULL) || (root->r == NULL)) {
            struct Node* temp;
            if (root->l == NULL) {
                temp = root->r; //node with no left child 
            }
            else {
                temp = root->l; //node with no right child
            }

            if (temp == NULL) { //if the non-empty child is also NULL, then its a node with no children 
                temp = root; //mark the current node for deletion
                root = NULL; //remove it from the tree 
            } else //this is when either the left or the right child is not NULL
                *root = *temp; //copy the element of the non-empty child (temp) to the current node (root)

            free(temp);
        } 
        else { //this is for a node with two children
            struct Node* temp = min(root->r); //to find the inorder successor (smallest node in the right sub-tree)
            root->k = temp->k; //copying the inorder successor's key to this node
            root->r = deletion(root->r, temp->k); //delete the inorder successor's node 
        }
    }

    if (root == NULL)
        return root; //if tree became empty then return unchanged tree 

    newheight(root); //updating the height of the current node 

    int bal = getbalf(root); //calculating the balance factor of the current node 

    if (bal > 1 && getbalf(root->l) >= 0)
        return rotateR(root); //left-left case, so we perform a right rotation

    if (bal > 1 && getbalf(root->l) < 0) {
        root->l = rotateL(root->l);
        return rotateR(root); //left-right case, so we perform left rotation on left child and then right rotation on the current node 
    }

    if (bal < -1 && getbalf(root->r) <= 0)
        return rotateL(root); //right-right case, so we perform a left rotation

    if (bal < -1 && getbalf(root->r) > 0) {
        root->r = rotateR(root->r);
        return rotateL(root); //right-left case, so we perform right rotation on right child and then left rotation on the current node
    }

    return root;
}

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->l);
        printf("%d ", root->k);
        inorder(root->r);
    }
}

int main() {
    struct Node* root = create(30);
    root->l = create(20);
    root->r = create(40);
    root->l->l = create(10);
    root->r->r = create(50);

    printf("In-order traversal before deletion: ");
    inorder(root);
    printf("\n");

    root = deletion(root, 20);

    printf("In-order traversal after deleting 20: ");
    inorder(root);
    printf("\n");

    return 0;
}