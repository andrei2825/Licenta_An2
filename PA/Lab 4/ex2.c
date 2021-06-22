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
