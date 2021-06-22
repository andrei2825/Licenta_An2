#include <stdio.h>
int M, n;
int sol[1000], value[1000], mass[1000];

/*
50 3
60 10
120 30
100 20
*/
void read(){
    int x, y;
    scanf("%d %d", &M, &n);
    for(int i = 0; i < n; i++) {
        sol[i] = i;
        scanf("%d %d", &x, &y);
        value[i] = x;
        mass[i] = y;
    }
}

void sort() {
    int temp, change;
    do{
        change = 0;
        for(int i = 0; i < n-1; i++) {
            if(value[sol[i]]/mass[sol[i]] < value[sol[i+1]]/mass[sol[i+1]]) {
                temp = sol[i];
                sol[i] = sol[i+1];
                sol[i+1] = temp;
                change = 1;
            }
        }
    }
    while(change);
}

void bag() {
    int bagMass = 0;
    int bag = 0;
    for(int i = 0, bagMass = M; i < n; i++){
        bag += mass[sol[i]];
        if(bagMass-bag >= 0) {
            printf("%d - %d\%%\n", sol[i]+1, 100);
        } else {
            int x = bag - bagMass;
            float prc = (x*100)/bag;
            printf("%d - %f%%\n", sol[i]+1, prc);
        }
    }
}

int main() {
    read();
    sort();
    bag();

}
