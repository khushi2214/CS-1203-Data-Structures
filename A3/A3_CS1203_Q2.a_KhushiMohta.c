//Implementing the insertion sort iteratively 
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

//Defining a function to perform the insertion sort 
void insertionsort (int arr[], int n) {
    int i, j, k; //i is for the elements of the array, j is for comparison, and k is the element to be inserted to its correct position  
    
    for (i=1; i<n; i++) { //Loop through the entire array, starting with i=1, as long as i remains less than n
    k = arr[i]; //Storing the current element which is to be inserted into its correct position in the array 
    j = i-1; // j will be used to compare k with the elements before it, and its initially set to one place behind i

    while (j >=0 && arr[j] > k) { //To make sure it doesnt try to access the elements before the start of the array, and that the element at j is greater than k
        arr[j+1] = arr[j]; //If the above conditions are satisfied then the element at position j moves one place ahead to make place for k
        j = j-1; //Decrementing value to continue checking the positions of elements and moving them until k is in its right position or reach the beginning of the array
    }
    arr[j+1] = k; //Assigns the element k its correct position in the sorted array
    }
}

void generatearray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;  //to generate random numbers between 0 and 999
    }
}

int main () {
    int n = 20;
    int arr[n];

    generatearray(arr, n);

    printf("Original array: "); //Printing the original, unsorted array
    for (int i = 0; i < n; i++){
        printf("%d", arr[i]);
        if (i<n-1){
            printf(", "); //To properly format the printed array
        }
    }
    
    clock_t start, end;
    start = clock (); //to record the starting time 

    insertionsort(arr, n); //Calling the function to sort the array

    end = clock (); //to record the end time

    double execTime = (double)(end-start)/CLOCKS_PER_SEC; //division converts elapsed clock ticks to seconds 

    printf("\nSorted array: "); //Printing the sorted array
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i<n-1){
            printf(", "); //To properly format the printed array
        }
    }
printf("\nTime taken for sorting: %f seconds\n", execTime);
return 0;
}