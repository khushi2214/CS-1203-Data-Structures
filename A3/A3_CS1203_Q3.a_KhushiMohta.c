#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//To apply divide and conquer, we divide an array into sub-arrays, such that the first array is from left to mid, and the second is from mid+1 to right
void merge(int arr[], int left, int right, int mid) {
    int leftarr = mid-left+1; //To calculate the size of the left sub-array
    int rightarr = right-mid; //To calculate the size of the right sub-array

    int lsub[leftarr], rsub[rightarr]; //Creating temporary arrays for the left and right sub-arrays

    for (int i=0; i<leftarr; i++) { //Copying the elements to the temporary arrays
        lsub[i] = arr[left+i]; //Copies the element at left+ith place and copies to lsub-array
    }
    for (int j=0; j<rightarr; j++) {
        rsub[j] = arr[mid+1+j]; //Copies elements to the temporary right sub-array
    }

    int i=0; //i is used to keep track of the elements in the left sub-array, and this sets the initial index of this array to 0
    int j=0; //We start merging from the beginning of this array too, and therefore the initial index is set to 0
    int k=left; //k refers to where we will place the elements in the original (merged) array, and it's set to the starting index of the left sub-array because we start merging from the left sub-array's position

    while (i<leftarr && j<rightarr) {
        if (lsub[i]<=rsub[j]) {
            arr[k] = lsub[i]; //If the element in the left sub-array is smaller, then copy it to the original array
            i++;
        } else {
            arr[k] = rsub[j]; //If the element in the right sub-array is smaller, then copy it to the original array
            j++;
        }
        k++; //Incrementing k to prepare it for the placement of the next element into the array
    }

    //Add two loops to copy the remaining elements in lsub and rsub back into the arr, which is required especially if there is an odd number of elements and either the left sub-array or the right sub-array has more elements
    while (i<leftarr) {
        arr[k] = lsub[i];
        i++;
        k++;
    }

    while (j < rightarr) {
        arr[k] = rsub[j];
        j++;
        k++;
    }
}

//Recursive function to perform the merge sort
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; //Calculate the middle index

        mergeSort(arr, left, mid); //Sorting the left half of the array recursively
        mergeSort(arr, mid + 1, right); //Sorting the right half of the array recursively
        merge(arr, left, right, mid); //Merging the sorted halves
    }
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

    mergeSort(arr, 0, n-1); 

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

