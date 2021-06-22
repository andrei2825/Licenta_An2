//ex1:
#include <stdio.h>


int validare(int v[], int x) {
    int i;
    for ( i = 0; i < x; i++)
    {
        if (v[i] == v[x])
        {
            return 0;
        }   
    }
    return 1;
}

void bck(int v[], int n) {
    int init_val = 0;
    int max = 3;
    int val = 1;
    int valid;
    for (int k = 0; k < n; k++) {
        v[k] = init_val;
    }
    int i = 0;
    while (i >= 0) {
        valid = 0;
        while (!valid && v[i] <= max) {
            v[i] = v[i] + val;
            valid = validare(v, i);
        }
        if (v[i] <= max) {
            if (i == n - 1) {
                printf("(%d %d %d) \n", v[0], v[1], v[2]);
            } else {
                i++;
            }
        } else {
            v[i] = init_val;
            i--;
        }   
    }
}


int main () {
    int n = 3;
    int v[n];
    bck(v, n);
}



//ex2:

#include <stdio.h>


void bck(int v[], int n) {
    int init_val = -1;
    int max = 1;
    int val = 1;
    int valid;
    for (int k = 0; k < n; k++) {
        v[k] = init_val;
    }
    int i = 0;
    while (i >= 0) {
        v[i]++;
        if (v[i] <= max) {
            if (i == n - 1) {
                printf("(");
                for (int j = 0; j < n; j++) {
                    printf("%d ", v[j]);
                }
                printf(") -> {");
                for (int j = 0; j < n; j++) {
                    if (v[j] == 1)
                    {
                        printf("%d ", j+1);
                    }
                }
                printf("}\n");
                
                
            } else {
                i++;
            }
        } else {
            v[i] = init_val;
            i--;
        }   
    }
}

int main () {
    int n = 3;
    int v[n];
    bck(v, n);
}


//ex3:

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