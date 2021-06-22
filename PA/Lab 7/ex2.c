#include <stdio.h>
#include <stdlib.h>
int source,V,E,time,visited[20],G[20][20], start[21], end[21], s;
void DFS(int i)
{
    int j;
    visited[i]=1;
    s++;
    start[i] = s;
    printf(" c(%c) = gri\n",i + 'A');
    for(j=0;j<V;j++)
    {
        if(G[i][j]==1&&visited[j]==0){
            DFS(j);
            s++;
            end[j] = s;
            printf(" c(%c) = negru\n",j + 'A');
        }
    }
}
int main()
{
    int i,j,v1,v2;
    E = 15;
    V = 10;
    for(i=0;i<V;i++)
    {
        for(j=0;j<V;j++)
            G[i][j]=0;
    }
    G[0][7] = 1;
    G[0][2] = 1;
    G[0][1] = 1;
    G[1][8] = 1;
    G[1][7] = 1;
    G[1][4] = 1;
    G[1][3] = 1;
    G[2][3] = 1;
    G[3][9] = 1;
    G[3][4] = 1;
    G[4][6] = 1;
    G[4][5] = 1;
    G[5][6] = 1;
    G[7][8] = 1;
    G[8][0] = 1;
    DFS(0);
    printf(" c(%c) = negru\n",'A');
    i = 0;
    printf("%c : (%d, %d)\n",i+'A', start[i], s+1);
    for (i = 1; i < V; i++)
    {
        printf("%c : (%d, %d)\n",i+'A', start[i], end[i]);
    }
    
    return 0;
}