/*Ex2*/
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
#include <stdio.h>
#include <string.h>

void garduri(int n, int k) {
    char gard[n+1][100][100];
    if(n == 0) {
        return;
    }
    int sol[n+1];
    char temp[100];
    sol[0] = 1;
    strcpy(gard[1][0], "");
    sol[1] = 1;
    strcpy(gard[1][0], "|");
    printf("%d\n%d, %s\n", sol[0], sol[1], "|");
    for(int i = k; i <= n; i++){
        sol[i] = sol[i-1] + sol[i-k];
        printf("%d, ", sol[i]);
        for(int j = 0; j < sol[i-1]; j++) {
            strcpy(gard[i][j], gard[i-1][j]);
            strcat(gard[i][j], "|"); 
        }
        for(int j = sol[i-1]; j < sol[i]; j++) {
            strcpy(gard[i][j], gard[i-k][j - sol[i-1]]);
            strcat(gard[i][j], "="); 
        }
        for( int j = 0; j < sol[i]; j++) {
            printf("%s, ", gard[i][j]);
        }
        printf("\n");
    }

}


int main() {
    garduri(6,2);
}

/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
Ex 3
-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
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
    
    for(i = 1; i <= n; i++) {
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
    for(i = 0; i <= n; i++){
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
