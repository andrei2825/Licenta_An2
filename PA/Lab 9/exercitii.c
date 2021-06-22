#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int timp = 0;
char c1[10][6];
int p1[10];
int d1[10];
int low1[10];
int subarb[10];
int art[10];

int timp2 = 0;
char c2[10][6];
int p2[10];
int d2[10];
int low2[10];
int punte[10];


int min(int a, int b) {
    if(a  > b) {
        return b;
    }
    return a;
}


struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};
 
struct AdjList
{
    struct AdjListNode *head;
};

struct Graph
{
    int N;
    struct AdjList* arr;
};
 
struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode =
     (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}
 
struct Graph* createGraph(int N)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->N = N;

    graph->arr = (struct AdjList*) malloc(N * sizeof(struct AdjList));

    int i;
    for (i = 0; i < N; ++i)
        graph->arr[i].head = NULL;
 
    return graph;
}
 
void addEdge(struct Graph* graph, int src, int dest)
{
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->arr[src].head;
    graph->arr[src].head = newNode;
    newNode = newAdjListNode(src);
    newNode->next = graph->arr[dest].head;
    graph->arr[dest].head = newNode;
}
 
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->N; ++v)
    {
        struct AdjListNode* pCrawl = graph->arr[v].head;
        while (pCrawl)
        {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

void Exploreaza(int u, struct Graph *graph) {
    d1[u] = low1[u] = timp++;
    printf("Low[%d] = %d, D[%d] = %d, Timp:%d\n",u, d1[u], u, low1[u], timp);
    strcpy(c1[u], "gri");
    printf("C[%d] = %s\n",u, c1[u]);
    struct AdjListNode *tmpNode = graph->arr[u].head;
    while (tmpNode){
        int v = tmpNode->dest;
        if(strcmp(c1[v], "alb") == 0) {
            p1[v] = u;
            subarb[u]++;
            printf("P[%d] = %d\n", v, p1[v]);
            printf("Subarb[%d] = %d\n", u, subarb[u]);
            printf("Exploreaza(%d)\n", v);
            Exploreaza(v, graph);
            printf("revenire\n");
            int tmp = low1[u];
            low1[u] = min(low1[u], low1[v]);
            printf("Low[%d] = min{low[%d], low[%d]} = min{%d, %d} = %d\n\n", u, u, v, tmp, low1[v], low1[u]);
            if(p1[u] != -1 && low1[v] >= d1[u]) {
                art[u] = 1;
            }
        } else {
            if(p1[u] != v) {
                low1[u] = min(low1[u], d1[v]);
            }
        }
        tmpNode = tmpNode->next;
    }
}

void Articulatii(struct Graph *graph) {
    struct AdjList *V = graph->arr;
    for (int u = 0; u < graph->N; ++u) {
        strcpy(c1[u], "alb");
        d1[u] = 0;
        p1[u] = -1;
        low1[u] = 0;
        subarb[u] = 0;
        art[u] = 0;
    }
    for (int u = 0; u < graph->N; ++u) {
        if(strcmp(c1[u], "alb") == 0) {
            Exploreaza(u, graph);
            if(subarb[u] > 1) {
                art[u] = 1;
            }
        }
    }
}

void ExploreazaPunti(int u, struct Graph *graph) {
    d2[u] = low2[u] = timp2++;
    printf("u = %d\n", u);
    printf("d(%d) = low(%d) = timp++ = %d\n", u, u, timp2-1);
    printf("timp = %d\n", timp2);
    strcpy(c2[u], "gri");
    printf("c(%d) = %s\n", u, c2[u]);
    struct AdjListNode *tmpNode = graph->arr[u].head;
    while (tmpNode){
        int v = tmpNode->dest;
        if(strcmp(c2[v], "alb") == 0) {
            p2[v] = u;
            printf("p(%d) = %d\n", v, u);
            ExploreazaPunti(v, graph);
            int tmp = low2[u];
            low2[u] = min(low2[u], low2[v]);
            printf("low(%d) = min{low(%d), low(%d)} = min{%d, %d} = %d\n", u, u ,v, tmp, low2[v], low2[u]);
            if(low2[v] > d2[u]) {
                printf("low(%d) > d(%d) <=> %d > %d => punte(%d) = 1\n\n", v, u, low2[v], d2[u], v);
                punte[v] = 1;
            }
        } else {
            if(p2[u] != v) {
                printf("p(%d) != %d => low(%d) = min{low(%d), low(%d)} = min{%d, %d} = %d\n", u, v, u, u, v, low2[u], low2[v],  min(low2[u], d2[v]));
                low2[u] = min(low2[u], d2[v]);
            }
        }   
        tmpNode = tmpNode->next;
    }
}

void Punti(struct Graph *graph) {
    struct AdjList *V = graph->arr;
    timp2 = 0;
     for (int u = 0; u < graph->N; ++u) {
        strcpy(c2[u], "alb");
        d2[u] = 0;
        p2[u] = -1;
        low2[u] = 0;
        punte[u] = 0;
    }
    for (int u = 0; u < graph->N; ++u) {
        if(strcmp(c2[u], "alb") == 0) {
            ExploreazaPunti(u, graph);
        }
    }
}




int main() {
    int N = 10;
    struct Graph *graph = createGraph(N);
    addEdge(graph, 0, 9);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 8);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 7);
    addEdge(graph, 2, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 5);
    addEdge(graph, 3, 4);
    addEdge(graph, 5, 6);
    addEdge(graph, 7, 8);
    Articulatii(graph);
    for (int i = 0; i < N; i++) {
        printf("Art[%d] = %d\n",i,art[i]);
    }
    printf("\n");
    Punti(graph);
    for (int i = 0; i < N; i++) {
        printf("Punte[%d] = %d\n",i,punte[i]);
    }
    return 0;
}