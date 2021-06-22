#include <stdio.h>
#include <limits.h>

int search(int v[], int s, int d, int x) {
    if(s <= d){
        int m = (s+d)/2;
        if(v[m] == x) {
            return m;
        }
        if(v[m] > x) {
            return search(v, s, m, x);
        } else {
            return search(v, m+1, d, x);
        }
    }
    return -1;
}

int main()
{
    int v[7] = {1, 3, 4, 5, 7, 3, 9};
    printf("%d", search(v, 0, 6, 3));
    return 0;
}

