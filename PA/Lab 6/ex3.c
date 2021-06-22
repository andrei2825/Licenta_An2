#include <stdio.h>
#define N 4

int verificare(int board[N][N], int l, int c) {
    int i, j;
    for (i = 0; i < c; i++)
    {
        if (board[l][i])
        {
            return 0; 
        } 
    }
    for ( i = l, j = c; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j])
        {
            return 0;
        }
    }

    for (i = l, j = c; j >= 0 && i < N; i++, j--)
    {
        if (board[i][j])
        {
            return 0;
        }   
    }
    return 1;
     
    
}

int dame(int board[N][N], int c) {
     if (c >= N)
     {
         return 1;
     }

     for (int i = 0; i < N; i++)
     {
         if (verificare(board, i, c))
         {
             board[i][c] = 1;
             if (dame(board, c + 1))
             {
                 return 1;
             }
            board[i][c] = 0;
             
         }
         
     }
     return 0;
}


int main () {
    int n = 4;
    int board[n][n];
    for (int  i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = 0;
        }
    }
    if(dame(board, 0)) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                printf(" %d ", board[i][j]);
            printf("\n");
        }
        printf("\n");
        for (int i = N-1; i >= 0; i--) {
            for (int j = 0; j < N; j++)
                printf(" %d ", board[i][j]);
            printf("\n");
        }
    }
}