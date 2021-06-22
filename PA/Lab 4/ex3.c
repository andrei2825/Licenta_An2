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
