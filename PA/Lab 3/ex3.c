#include <stdio.h>
/*
6
10 11
11 13
12 13
14 18
16 17
17 19
*/
int s[100], t[100], n, nr[100];
void read() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        nr[i] = i;
        scanf("%d %d", &s[i], &t[i]);
    }
}

void sort() {
    int temp, change;
    do{
        change = 0;
        for(int i = 0; i < n-1; i++){
            if(t[nr[i]] > t[nr[i+1]]) {
                temp = nr[i];
                nr[i] = nr[i+1];
                nr[i+1] = temp;
                change = 1;
            }
        }
    }while (change);
}

void solve() {
    int x, i;
    if(s[nr[1]] >= t[nr[0]]) {
        printf("%d ", nr[x] + 1);
    }
    for(x = 0, i = 1; i < n; i++) {
        if(s[nr[i]] >= t[nr[x]]) {
            printf("%d ", nr[i] + 1);
            x = i;
        }
    }
}

int main() {
    read();
    sort();
    solve();
}
