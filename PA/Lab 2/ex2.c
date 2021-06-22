#include <stdio.h>
#include <limits.h>

void maxim(int v[], int s, int d, int *max) {
    if (s == d) {
        if(v[s] > *max) {
            *max = v[s];
            return;
        } else {
            return;
        }
    }
    if(d - s == 1) {
        if(v[s] > v[d]) {
            if(v[s] > *max) {
                *max = v[s];
                return;
            } else {
                return;
            }
        } else {
            if(v[d] > *max) {
                *max = v[d];
                return;
            } else {
                return;
            }
        }
    }
    int m = (s+d)/2;
    maxim(v, s, m, max);
    maxim(v, m+1, d, max);
}

int main()
{
    int v[5] = {3, 2, 5, 2, 4};
    int max = INT_MIN;
    maxim(v, 0, 4, &max);
    printf("%d", max);
}
