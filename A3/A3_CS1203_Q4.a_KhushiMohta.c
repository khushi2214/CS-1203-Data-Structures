//Implementing the tower of hanoi with recursion 
#include<stdio.h>
void hanoi(int n, char from, char extra, char to){
    if (n==1){
        printf("Move the disk 1 from %c to %c\n", from, to); //if there is only 1 disk that needs to be moved, we can move it from the beginning (from) peg to the final (to) peg
        return;
    }
    hanoi(n-1, from, to, extra); //moving (n-1) pegs from the beginning peg to the extra peg, using the final peg as the extra
    printf("Move the disk %d from %c to %c\n", n, from, to); //move the largest disk from the beginning peg to the final peg
    hanoi(n-1, extra, from, to); //moving (n-1) pegs from the extra peg to the final (to) peg, using the beginning (from) peg as the extra
}
int main(){
    int n;
    printf("Enter the number of disks: ");
    scanf("%d", &n);
    hanoi(n, 'A', 'B', 'C'); //here, A is the beginning (from) peg, B is the extra peg and C is the final (to) peg
    return 0;
}