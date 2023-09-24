#include <stdio.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main() {
    int a;
    printf("Enter the value of n (up to 8): ");
    scanf("%d", &a);

    if (a > 8 || a < 1) {
        printf("Invalid input. Please enter a value between 1 and 8.\n");
        return 1;
    }

    int arr[8]; //maximum value of a 
    for (int i = 0; i < a; i++) {
        arr[i] = i + 1; //mapping the index to the elements and initialising the array
    }

    int i; 
    //i and j are initialised. i will be used to find where the index whose element needs to be swapped, and j finds the index of the element which should be swapped with the element at index i 

    do {
        for (int j = 0; j < a; j++) {
            printf("%d ", arr[j]); // to print the current permutation, which will be the first one
        }
        printf("\n");
        //to find the rightmost element which is smaller than the element immediately to its right (ascending order)
        i = -1;
        for (int j = a - 2; j >= 0; j--) {
            if (arr[j] < arr[j + 1]) {
                i = j;
                break;
            }
        }

        if (i == -1) {
            //all permutations have been printed (i remains -1), so we can break the loop
            break;
        }
        //finding the rightmost element which is greater than arr[i] in order to swap with it 
        int j = -1;
        for (int k = a - 1; k > i; k--) {
            if (arr[k] > arr[i]) {
                j = k;
                break;
            }
        }

        swap(&arr[i], &arr[j]);
        //reverses the order of the elements to the right of arr[i] in order to keep the lexicographical order 
        int start = i + 1;
        int end = a - 1;
        while (start < end) {
            swap(&arr[start], &arr[end]);
            start++;
            end--;
        }
    } while (1);

    return 0;
}
