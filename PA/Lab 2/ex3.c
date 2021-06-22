#include <stdio.h>
#include <limits.h>

void sortare(int v[], int s, int d) {
    int m;
    int temp[10];
    if(s < d) {
        m = (s + d) / 2;
        sortare(v, s, m);
        sortare(v, m+1, d);
        int i, j, k;
        for(i = s, j = m+1, k = s; i <= m && j <= d; k++) {
            if(v[i] <= v[j]){
                temp[k] = v[i++];
            } else {
            temp[k] = v[j++];
            }
        }
        while(i <= m) {
            temp[k++] = v[i++];
        }
        while(j <= d) {
            temp[k++] = v[j++];
        }
        for(i = s; i <= d; i++){
            v[i] = temp[i];
        }
    }

}

int main()
{
    int v[7] = {3, 2, 1, 4, 3, 5, 2};
    sortare(v, 0, 6);
    for(int i = 0; i < 7; i++) {
        printf("%d ", v[i]);
    }
    return 0;
}
