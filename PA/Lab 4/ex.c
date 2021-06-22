//---------------------EX1-------------------------//
#include <stdio.h>
#include <limits.h>

void suma(int v[], int n) {
    int mat[n][n];
    for(int i = 1; i < n; i++) {
        mat[i][i] = 0;
    }
    for(int m = 2; m < n; m++) {
        for (int i = 1; i < n-m+1; i++) {
            int j = i+m-1;
            mat[i][j] = INT_MAX;
            for (int k = i; k <= j-1; k++) {
                int q = mat[i][k] + mat[k+1][j] + v[i-1]*v[k]*v[j];
                if(q < mat[i][j]) {
                    mat[i][j] = q;
                    mat[j][i] = k;
                }
            }
        }
    }
    char name = 'A';
    printf("Cost optim: %d\n", mat[1][n-1]);
    printf("Parantezare:");
    parantezare(1, n-1, n, mat, name);
}

void parantezare(int i, int j, int n, int paranteze[n][n], char name) {
    if(i == j) {
        printf("%c", name++);
        return;
    }
    printf("(");
    parantezare(i, paranteze[j][i], n, paranteze, name);
    parantezare(paranteze[j][i]+1, j, n, paranteze, name);
    printf(")");
}


int main(){
    int v[] = {2, 4, 3, 5, 2};
    int n = sizeof(v)/sizeof(v[0]);
    suma(v, n);
}

//---------------------EX2-------------------------//
#include <stdio.h>
#include <limits.h>

int max(int a, int b) {
    if(a > b) {
        return a;
    }
    return b;
}

int rucsac(int M, int m[], int v[], int n) {
    int i, j;
    int D[n+1][M+1];
    for (i = 0; i <=n; i++) {
        for(j = 0; j <= M; j++) {
            if(i == 0 || j == 0) {
                D[i][j] = 0;
            } else if(m[i-1] <= j) {
                D[i][j] = max(v[i-1] + D[i-1][j-m[i-1]], D[i-1][j]);
            } else {
                D[i][j] = D[i-1][j];
            }
        }
    }
    return D[n][M];
}

int main() {
    int M = 50;
    int m[] = {10, 30, 20};
    int v[] = {60, 120, 100};
    int n = sizeof(m)/sizeof(m[0]);
    printf("%d", rucsac(M, m, v, n));
}


//---------------------EX3-------------------------//
#include <stdio.h>
#include <limits.h>

int max(int a, int b) {
    if(a > b) {
        return a;
    }
    return b;
}

void subsir(int v[], int n) {
    int sizeInc[n];
    int sizeDec[n];
    for(int i = 0; i < n; i++) {
        sizeDec[i] = 0;
        sizeInc[i] = 0;
    }
    sizeInc[0] = 1;
    sizeDec[n-1] = 1;
    int l = 0;
    for(int i = 1; i < n; i++) {
        if (v[i] > v[i-1]) {
            sizeInc[i] = sizeInc[i-1] + 1;
        } else {
            sizeInc[i] = 1;
        }
    }
     l = 1;
    for (int i = n - 2; i >= 0; i--) {
        if (v[i] < v[i + 1])
            sizeDec[i] = sizeDec[i + 1] + 1;
        else
            sizeDec[i] = 1;
    }
    int size = 0;
    for (int i = 1; i <= n-2; i++) {
        if(v[i-1] < v[i+1]) {
            size = max(sizeInc[i-1] + sizeDec[i+1], size);
        }
    }
    int count = 0;
     for (int i = 1; i <= n-2; i++) {
        if(v[i-1] < v[i+1]) {
            count++;
            printf("%d ", v[i-1]);
            if(count == (size - 1)) {
                printf("%d ", v[i+1]);
            }
        }
    }
    printf("\n%d", size);
}

int main() {
    int v[] = {1, 2, 9, 3, 4, 8, 7};
    int n = sizeof(v)/sizeof(v[0]);
    subsir(v, n);
}
