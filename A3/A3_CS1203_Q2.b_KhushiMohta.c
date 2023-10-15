//Implementing bubble sort

#include <stdio.h>
#include<stdlib.h>
#include<time.h>

void swap(int *xp, int *yp) {
    int temp;
    temp = *xp; //Storing the value at xp in temp
    *xp = *yp; //Moving the value stored in yp to xp 
    *yp = temp; //Copying the original value from temp to yp
}

void bubblesort (int arr[], int n) {
    int swapped, j; //Swapped will be used to determine if any swaps took place during one loop through an array, and j will be used as the loop counter 

    for (int i=0; i<n-1; i++){
        swapped = 0; //Indicates that no swaps have occured yet

        //We have to now traverse from the beginning to the end of the array
        for (int j=0; j<n-1-i; j++ ) { //i is subtracted to account for those elements which have already been sorted in the previous passes, and this ensures that the loop only runs over the unsorted elements 
        //We will now have to compare adjacent elements and swap them if they are not sorted 
            if (arr[j]>arr[j+1]){ //Checking if the current element is greater than the element after it 
                swap (&arr[j], &arr[j+1]);
                swapped = 1; //This signifies that a swap has occured 

        }
    }
        if (swapped == 0){ //If the swapped variable remains 0, that means no elements were sorted and the array is already sorted 
            break; //To exit the outer loop 
        }    
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

    bubblesort(arr, n); //Calling the function with the array and the size of the array as the parameters 

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

