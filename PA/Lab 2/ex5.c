#include <stdio.h>
#include <limits.h>

void search(int v[], int s, int d, int x, int *sum) {
    if (s == d) {
        if(v[s] == x) {
            (*sum)++;
            return;
        } else {
            return;
        }
    }
    int m = (s+d)/2;
    search(v, s, m, x, sum);
    search(v, m+1, d, x, sum);
}

int main()
{
    int v[10] = {2, 1, 3, 1, 1, 4, 2, 1, 8, 1};
    int sum = 0;
    search(v, 0, 9, 1, &sum);
    printf("%d", sum);
    return 0;
}
