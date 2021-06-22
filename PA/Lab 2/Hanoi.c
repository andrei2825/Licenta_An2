#include <stdio.h>

void hanoi(int n, char a, char b, char c) {
    if(n==1) {
        printf("Muta 1 de la %c la %c\n", a, b);
        return;
    }
    hanoi(n-1, a, c, b);
    printf("Muta %d de la %c la %c\n", n, a, b);
    hanoi(n-1, c, b, a);
    
}

int main()
{
    int n = 3;
    hanoi(n, 'A', 'B', 'C');
    return 0;
}