//Implementing quick sort
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap (int* a, int*b){
    int temp = *a; //storing the value of a in a temporary variable 
    *a = *b; //assigning the value of b to a
    *b = temp; //assigning the value in the temporary variable to b to swap a and b
}

int divide (int arr[], int less, int more){ //low is the index of the starting (leftmost) element and more is the  index of the ending (rightmost) element 
    int pivotelm = arr[more]; //selecting the last element as the pivot element 
    int i = less - 1; //to keep track of where the element less than the pivot element should be placed, value initalised to the left of the leftmost element 
    
    for (int j = less; j < more; j++){
        if (arr[j] < pivotelm) {
            i++; //increase the index of the smaller element 
            swap(&arr[i], &arr[j]); //swap arr[i] and arr[j]
        }
    }
    swap(&arr[i+1], &arr[more]); //swapping arr[i+1] and the pivot element 
    return (i+1); //return the index of the pivot element 
}

void quicksort (int arr[], int less, int more){
    if (less < more){
        int pivotidx = divide(arr, less, more); //finding the pivot index 
        quicksort(arr, less, pivotidx-1); //recursively sorting the elements to the left of the pivot 
        quicksort(arr, pivotidx+1, more); //recursively sorting the elements to the right of the pivot 
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

    quicksort(arr, 0, n-1); 

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

