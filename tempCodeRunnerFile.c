#include <stdio.h>
#include <stdlib.h>
#include "mt64.h"


//Tree node structure
struct treeNode {
    //Insert code here to define the tree node
    int val;
    struct treeNode* left;
    struct treeNode* right;

};

//K-th smallest centre node structure
struct centreNode {
    int val;
    int* maxHeap;
    int* minHeap;
    int minHeapSize;
    int maxHeapSize;
};

//Make it easier to call the structs
typedef struct treeNode tNode;
typedef struct centreNode cNode;

//Generate an array of n random numbers
int* generateRandomNumbers(int n) {
    int* randomNumbers = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++) {
        randomNumbers[i] = (int)(genrand64_int64()%100);
    }
    return randomNumbers;
}

//Print an array of n numbers starting at *arr
void printArray(int* arr, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
}

//Function to create a node with a value
tNode* createTreeNode(int val) {
    //Insert code here to create a node with a given value
    tNode* newNode = (tNode*)malloc(sizeof(tNode));
    newNode ->val = val;
    newNode ->left = NULL;
    newNode ->right = NULL;
    return newNode;
}

//Search tree for a value
tNode* searchTree(tNode* root, int val) {
    //Insert code here to search for a value
    if (root==NULL || root ->val == val){
        return root;
    }
    if (val < root -> val){
        return searchTree(root -> left, val);
    }
    return searchTree(root->right,val);
}

//Insert a new node with a given value and check difference k
tNode* insertTree(tNode* root, int val, int k) {
    //Insert code here to insert a new node with a given value and check difference k
    tNode* insertTree(tNode* root, int val, int k);{
        if (root==NULL){
            return createTreeNode(val);
        }
        if(val<root->val){
            root->left = insertTree(root->left, val, k);
        }
        else if(val > root->val){
            root->right = insertTree(root->right, val, k);
        }
        if (abs(val - root -> val) >= k){
            return root;
        }
        return root;
    }
}

//Finding the minimum value node
tNode* minValueNode(tNode* node){
    tNode* current=node;
    while (current && current->left != NULL){
        current = current->left;
    }
    return current;
}

//Delete a node with a given value
tNode* deleteTree(tNode* root, int val) {
    //Insert code here to delete a node with a given value
    if (root == NULL){
        return root;
    }
    if (val<root->val){
        root->left = deleteTree(root->left, val);
    }
    else if(val>root->val){
        root->right=deleteTree(root->right, val);
    }
    else{
        if(root->left == NULL){
            tNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right==NULL){
        tNode*temp = root->left;
        free(root);
        return temp;
        }
        tNode*temp = minValueNode(root->right);
        root->val = temp->val;
        root->right = deleteTree(root->right, temp->val);
    }
    return root;
}


//Print out the tree in inorder with a space between each nubmer, an example would be "1 2 4 5 3"
void inorderTree(tNode* root) {
    if (root != NULL){
        inorderTree(root->left);
        printf("%d ", root-> val);
        inorderTree(root->right);
    }

}

//Swap 2 elements in an array
void swap(int* num1, int* num2) {
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

//Heapify min heap
void heapifyMin(int* arr, int len, int rootIndex) {
    int smallest = rootIndex;
    int leftChild = 2 * rootIndex + 1;
    int rightChild = 2 * rootIndex + 2;
    if (leftChild<len && arr[leftChild]<arr[smallest]){
        smallest=leftChild;
    }
    if (rightChild<len && arr[rightChild]<arr[smallest]){
        smallest=rightChild;
    }
    if (smallest != rootIndex){
        swap(&arr[rootIndex],&arr[smallest]);
        heapifyMin(arr, len, smallest);
    }

}

//Heapify max heap
void heapifyMax(int* arr, int len, int rootIndex) {
    int largest = rootIndex;
    int leftChild = 2 * rootIndex + 1;
    int rightChild = 2 * rootIndex + 2;
    if (leftChild < len && arr[leftChild] > arr[largest]){
        largest=leftChild;
    }
    if (rightChild<len && arr[rightChild]>arr[largest]){
        largest=rightChild;
    }
    if (largest!= rootIndex){
        swap(&arr[rootIndex],&arr[largest]);
        heapifyMax(arr, len, largest);
    }
}

//Build min heap
void buildMinHeap(int* arr, int len) {
    for(int i = len/2 - 1; i>=0; i--){
        heapifyMin(arr, len, i);
    }

}

//Build max heap
void buildMaxHeap(int* arr, int len) {
    for(int i = len/2 - 1; i>=0; i--){
        heapifyMax(arr, len, i);
    }

}

//Insert element in min heap, hint: use realloc
int* insertMinHeap(int* arr, int* len, int val) {
    (*len)++;
    arr=(int*)realloc(arr, sizeof(int) * (*len));
    int i = (*len)-1;
    while (i && val < arr[(i-1)/2]){
        arr[i] = arr[(i-1)/2];
        i=(i-1)/2;
    }
    arr[i] = val;
    return arr;
}

//Insert element in max heap, hint: use realloc
int* insertMaxHeap(int* arr, int* len, int val) {
    (*len)++;
    arr = (int*)realloc(arr, sizeof(int)*(*len));
    int i = (*len) - 1;
    while (i && val > arr[(i-1)/2]){
        arr[i] = arr[(i-1)/2];
        i=(i-1)/2;
    }
    arr[i]=val;
    return arr;
}

//Extract min element from min heap
int extractMin(int* arr, int* len) {
    if(*len<=0){
        return -1;
    }
    if (*len==1){
        (*len)--;
        return arr[0];
    }
    int root = arr[0];
    arr[0] = arr[(*len)-1];
    (*len)--;
    heapifyMin(arr, *len, 0);
    return root;
}

//Extract max element from max heap
int extractMax(int* arr, int* len) {
    if (*len<=0){
        return -1;
    }
    if(*len==1){
        (*len)--;
        return arr[0];
    }
    int root = arr[0];
    arr[0]=arr[(*len)-1];
    (*len)--;
    heapifyMax(arr,*len,0);
    return root;
}

//You will need to write other functions to complete the assignment as well, insert them here

int main(int argc, char *argv[]) {
    //Make sure we have a seed
    if(argc != 2) {
        printf("Usage: %s <seed>\n", argv[0]);
        exit(1);
    }

    init_genrand64(atoi(argv[1])); //Set the seed for the random number generator

    int n = 15;
    int* randomNumbers = generateRandomNumbers(n); //Generate an array of 15 random numbers
    printArray(randomNumbers, n); //Print the array of random numbers, leave this in
    printf("\n");

    //Code for problem 6 part a
    int k = 12;
    tNode* root = NULL;

    //Insert code here to solve problem 6 part a, loop over the numbers and print the tree on a new line after each insert
    for (int i = 0; i<n; i++){
        root = insertTree(root, randomNumbers[i], k);
        inorderTree(root);
        printf("\n");
    }

    //Insert code to solve problem 6 part b, print out the updated tree
    
    root = deleteTree(root, randomNumbers[1]);{
        printf("Updated: ");
        inorderTree(root);
        printf("\n");
    }


    //Code for problem 6 part c
    int c = 4;
    cNode* centreNode = (cNode*)malloc(sizeof(cNode));
    centreNode->maxHeap=(int*)malloc(sizeof(cNode));
    centreNode->minHeapSize=0;

    //Insert code here to complete the problem by initializing the centreNode and
    //looping over the numbers and updating the centre node, print the node value at each insert
    for (int i = 0; i<n; i++){
        if (centreNode->minHeapSize < c) {
            centreNode->minHeap[centreNode->minHeapSize] = randomNumbers[i];
            centreNode->minHeapSize++;
            buildMinHeap(centreNode->minHeap, centreNode->minHeapSize);
        } else if (randomNumbers[i] < centreNode->minHeap[0]) {
            centreNode->minHeap[0] = randomNumbers[i];
            heapifyMin(centreNode->minHeap, centreNode->minHeapSize, 0);
        }
        centreNode->val=centreNode->minHeap[0];
        printf("The 4th smallest element is %d: %d\n",randomNumbers[i],centreNode->val);
    }
    free(centreNode->minHeap);
    free(centreNode);

    return 0;
}