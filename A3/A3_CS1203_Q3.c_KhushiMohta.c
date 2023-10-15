//Implementing heap sort 

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void swap (int* a, int*b){
    int temp = *a; //storing the value of a in a temporary variable 
    *a = *b; //assigning the value of b to a
    *b = temp; //assigning the value in the temporary variable to b to swap a and b
}

void heapify(int arr[], int n, int i) {
    int largest = i; //initialising the largest as the root
    int l = 2 * i + 1; //left child index calculation
    int r = 2 * i + 2; //right child index calculation

    if (l < n && arr[l] > arr[largest]) //checking if left child exists and is largerthan the current largest
        largest = l;

    if (r < n && arr[r] > arr[largest]) //checking if right child exists and is larger than the current largest
        largest = r;

    if (largest != i) { //if the largest is not the root, then swap elememts and recursively heapify the sub-tree
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heapsort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) //building a max heap, starts from the last non-leaf node (at index n/2 - 1) and works its way up to the root
        heapify(arr, n, i); //to make sure the current sub-tree is a valid heap 

    for (int i = n - 1; i > 0; i--) { //iterates over elements one by one to extract them (starts at the end and moves towards the start)
        int temp = arr[0]; //stores largest element temporarily in temp
        arr[0] = arr[i]; //swaps the root element with the last unsorted element such that its at the end of the array
        arr[i] = temp; //places the largest element at the i position in the sorted array

        heapify(arr, i, 0);
    }
}

void print(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void generatearray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;  //to generate random numbers between 0 and 999
    }
}

int main() {
    int n = 20;
    int arr[n];

    generatearray(arr, n);

    printf ("Original array: "); //Printing the original array 
    for (int i=0; i<n; i++){ //Loop though elements to print the original array
        printf("%d", arr[i]); //To print each element of the array
        if (i<n-1){
            printf(", "); //To properly format the printed array
        }
    }
    
    clock_t start, end;
    start = clock (); //to record the starting time 

    heapsort(arr, n); 

    end = clock (); //to record the end time

    double execTime = (double)(end-start)/CLOCKS_PER_SEC; //division converts elapsed clock ticks to seconds 

    printf ("\nSorted array: "); //Printing the sorted array
    for (int i=0; i<n; i++){ 
        printf("%d", arr[i]); //To print each element of the array
        if (i<n-1){
            printf(", "); //To properly format the printed array
        }
    }
    printf("\nTime taken for sorting: %f seconds\n", execTime);
    return 0;
}