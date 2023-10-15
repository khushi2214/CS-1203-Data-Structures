//Implementing the eight queens recursively 
#include<stdio.h>
#define N 8 //defining a constant N as 8, which represents the size of the chessboard

int place (char b[N][N], int r, int c){ //b defins the board, r stands for row and c stands for column 
    int i, j; //look counters, used to represent row and col indexes to determine place of queen in the board

    for (i=0; i<c; i++){ //this checks if there is no queen in the same row to the left of the current cell
        if(b[r][i]=='Q')
        return 0;
    }

    for (i=r, j=c; i>=0 && j>=0; i--, j--){ //checks if there is no queen on the upper diagonal on the left
        if (b[i][j]== 'Q')
        return 0;
    }

    for (i=r, j=c; i<N && j>=0; i++, j--){ //checks if there is no queen on the lower diagonal on the left
        if (b[i][j] == 'Q')
        return 0;
    }

    return 1;
}

void printBoard (char b[N][N]){ //loops thorugh each cell of the 2 dimentional array and prints out values
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            printf("%c", b[i][j]);
        }
        printf("\n"); //after printing each board, a new line is added for better formatting 
    }
    printf("\n");
}

void solution (char b[N][N], int c){
    if (c>=N){ //if all queens have been placed
        printBoard(b);
        return;
    }

    for (int i=0; i<N; i++){ //for each column it iterates through all i rows
        if (place(b, i, c)){
            b[i][c] = 'Q'; //when a place is found, it marks the position with 'Q'
            solution(b, c+1); //recursively finds the positions by moving to the next column 
            b[i][c] = '.'; //backtrack and mark as '.', meaning that no queen has been placed  
        }
    }
}

int main(){
    char b[N][N];
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            b[i][j] = '.';
        }
    }
    solution(b,0);
    return 0;
}