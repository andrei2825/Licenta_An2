#include <stdio.h>

void sume(int v[], int n) {
    int i, j, k, l;
    int x = n;
    int D[n+1][3];
     
    for(i = 0; i < n+1; i++) {
        for (j = 0; j < 3; j++)
        {
            D[i][j] = 0;
        }
        printf("%d ", n);
    }
    
    for(i = 1; i <= x; i++) {
        if(v[i]%3 == 0){
            D[i][0] += 1 + 2 * D[i-1][0];
            D[i][1] += 2 * D[i-1][1];
            D[i][2] += 2 * D[i-1][2];
        } else if(v[i]%3 == 1) {
            D[i][0] += D[i-1][0] + D[i-1][2];
            D[i][1] += 1 + D[i-1][1] + D[i-1][0];
            D[i][2] += D[i-1][2] + D[i-1][1];
        } else {
            D[i][0] += D[i-1][0] + D[i-1][1];
            D[i][1] += D[i-1][1] + D[i-1][2];
            D[i][2] += 1 + D[i-1][2] + D[i-1][0];
        }
    }
   printf("\n");
    for(i = 0; i <= x; i++){
        for (j = 0; j < 3; j++)
        {
            printf("%d ", D[i][j]);
        }
        printf("\n");
        
    }
}



int main() {
    int v[5];
    v[1] = 3;
    v[2] = 1;
    v[3] = 2;
    v[4] = 4;
    sume(v, 4);
}