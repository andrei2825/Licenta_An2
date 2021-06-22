//+--------------------------------EX1--------------------------------+
#include <stdio.h>
#include <stdlib.h>
#define N 40

struct Queue {
    int items[N];
    char names[N];
    char size[N];
    int front;
    int rear;
};

struct Queue* createQueue();
void enqueue(struct Queue* q, int);
int dequeue(struct Queue* q);
void display(struct Queue* q);
int isEmpty(struct Queue* q);
void printQueue(struct Queue* q);

struct AdjListNode
{
	int dest;
    char name;
	struct AdjListNode* next;
};

struct AdjList
{
	struct AdjListNode *head;
};

struct AdjListNode* newAdjListNode(int dest, char name);

struct Graph
{
	int V;
	struct AdjList* array;
    int* visited;
};


void BFS(struct Graph* graph, int startEdge, int V) {
    struct Queue* q = createQueue(V);
    graph->visited[startEdge] = 1;
    enqueue(q, startEdge);
    int prev = -1;
    while(!isEmpty(q)) {
        printQueue(q);
        int currentEdge = dequeue(q);
        if (prev != -1) {
            printf("c(%c) = negru\n", prev + 'A');
        }
        prev = currentEdge;
        struct AdjListNode* tmp = graph->array[currentEdge].head;
        while (tmp)
        {
            int edge = tmp->dest;
            if (graph->visited[edge] == 0)
            {
                graph->visited[edge] = 1;
                enqueue(q, edge);
            }
            tmp = tmp->next;
        }
    }
    printf("\nQ = {} \nc(%c) = negru\n", prev + 'A');
}


struct AdjListNode* newAdjListNode(int dest, char name)
{
	struct AdjListNode* newNode =
	(struct AdjListNode*) malloc(sizeof(struct AdjListNode));
	newNode->dest = dest;
    newNode->name = name;
	newNode->next = NULL;
	return newNode;
}


struct Graph* createGraph(int V)
{
	struct Graph* graph =
		(struct Graph*) malloc(sizeof(struct Graph));
	graph->V = V;

	graph->array =
	(struct AdjList*) malloc(V * sizeof(struct AdjList));
    graph->visited = malloc(V * sizeof(int));

	int i;
	for (i = 0; i < V; i++) {
		graph->array[i].head = NULL;
        graph->visited[i] = 0;
    }
	return graph;
}

void addEdge(struct Graph* graph, int src, int dest, char *names)
{
	struct AdjListNode* newNode = newAdjListNode(dest, names[dest]);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;
}

struct Queue* createQueue(int V) {
    struct Queue* q = malloc(sizeof(struct Queue));
    q->front= -1;
    q->rear = -1;
    return q;
}

int isEmpty(struct Queue* q) {
    if (q->rear == -1) {
        return 1;
    } else {
        return 0;
    }
}

void enqueue(struct Queue* q, int value) {
    if (q->rear == N - 1) {
        printf("\n =The queue is full");
    } else {
        if (q->front == -1) {
            q->front = 0;
        }
        q->rear++;
        q->items[q->rear] = value;
        q->names[q->rear] = 'A' + value;
    }
}

int dequeue(struct Queue* q) {
    int item;
    if(isEmpty(q)) {
        printf("The queue is empty");
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            printf("Resetting queue\n ");
            q->front = q->rear = -1;
        }
    }
    return item;
}


void printQueue(struct Queue* q) {
    int i = q->front;
    if (isEmpty(q)) {
        printf("The queue is empty");
    } else {
        printf("\nQ = {");
        for (i = q->front; i < q->rear + 1; i++) {
            printf("%c ", q->names[i]);
        }
        printf("}\n");
        for (i = q->front; i < q->rear + 1; i++)
        {
            printf("c(%c) = gri\n", q->names[i]);
        }
        
    }
}


int main()
{
	int V = 10;
    char names[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'};
	struct Graph* graph = createGraph(V);
    struct Graph* graphCurs = createGraph(12);
    addEdge(graph, 0, 7, names);
    addEdge(graph, 0, 2, names);
	addEdge(graph, 0, 1, names);
    addEdge(graph, 1, 8, names);
    addEdge(graph, 1, 7, names);
    addEdge(graph, 1, 4, names);
    addEdge(graph, 1, 3, names);
    addEdge(graph, 3, 9, names);
    addEdge(graph, 3, 4, names);
    addEdge(graph, 2, 3, names);
    addEdge(graph, 4, 6, names);
    addEdge(graph, 4, 5, names);
    addEdge(graph, 5, 6, names);
    addEdge(graph, 7, 8, names);
    addEdge(graph, 8, 0, names);
	BFS(graph, 0, V);

    addEdge(graphCurs, 0, 6, names);
    addEdge(graphCurs, 0, 1, names);
    addEdge(graphCurs, 1, 6, names);
    addEdge(graphCurs, 1, 2, names);
    addEdge(graphCurs, 2, 4, names);
    addEdge(graphCurs, 2, 3, names);
    addEdge(graphCurs, 4, 5, names);
    addEdge(graphCurs, 6, 7, names);
    addEdge(graphCurs, 7, 0, names);
    addEdge(graphCurs, 8, 0, names);
    addEdge(graphCurs, 8, 9, names);
    addEdge(graphCurs, 8, 10, names);
    addEdge(graphCurs, 9, 10, names);
    addEdge(graphCurs, 10, 11, names);
	BFS(graphCurs, 0, 12);

	return 0;
}











//+--------------------------------EX2--------------------------------+
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