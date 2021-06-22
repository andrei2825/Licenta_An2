#include <limits.h>
#include <stdio.h>
#define V 7
int minDistance(int dist[], int done[])
{
    int min = INT_MAX, min_index;
  
    for (int v = 0; v < V; v++)
        if (done[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;
  
    return min_index;
}
  
int printSolution(int dist[], int parent[], int n)
{
    printf("Node    Parent   Dist\n");
    for (int i = 0; i < V; i++)
        if(parent[i] != -1) {
            printf("%d       %d        %d\n", i+1, parent[i] + 1,  dist[i]);
        } else  {
            printf("%d       %d        %d\n", i+1, parent[i],  dist[i]);
        }
}
void dijkstra(int graph[V][V], int src)
{
    int dist[V];
    int done[V];
    int parent[V];
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, done[i] = 0, parent[i] = -1;
  
    dist[src] = 0;
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, done);
        done[u] = 1;
        for (int v = 0; v < V; v++)

            if (!done[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]){
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
    }
  
    printSolution(dist, parent, V);
}
  
void BF(int graph[V][V], int src)
{
    int dist[V];
    int done[V];
    int parent[V];
    int E;
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, done[i] = 0, parent[i] = -1;
    dist[src] = 0;
    for (int i = 0; i < V; i++){
        for (int j = 0; j < V; j++) {
            if (graph[i][j] != 0)
            {
                if (dist[j] > (dist[i] + graph[i][j]))
                {
                    dist[j] = (dist[i] + graph[i][j]);
                    parent[j] = i;
                }
            }
        }
    }
    printSolution(dist, parent, V);
} 

int main()
{
    int graph[V][V] =  {{0, 3, 4, 0, 1, 10, 3},
                        {0, 0, 2, 0, 0, 0, 0},
                        {0, 0, 0, 2, 0, 2, 0},
                        {0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 3, 0, 0, 1},
                        {0, 0, 0, 2, 0, 0, 0},
                        {0, 0, 1, 10, 2, 0, 0}};
    printf("Dijkstra: \n");
    dijkstra(graph, 0);
    printf("Bellman ford: \n");
    BF(graph, 0);
    return 0;
}