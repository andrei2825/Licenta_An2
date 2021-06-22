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