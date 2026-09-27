#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 20

typedef struct {
    int items[MAX_NODES];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, int value) {
    if (q->rear == MAX_NODES - 1) {
        printf("Queue is full!\n");
        return;
    }

    if (q->front == -1) {
        q->front = 0;
    }

    q->items[++(q->rear)] = value;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }

    int item = q->items[(q->front)++];

    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }

    return item;
}

void bfs(int graph[MAX_NODES][MAX_NODES], int numVertices, int startVertex) {
    Queue q;
    initQueue(&q);

    int visited[MAX_NODES] = {0};

    visited[startVertex] = 1;
    enqueue(&q, startVertex);

    while (!isEmpty(&q)) {
        int currentVertex = dequeue(&q);
        printf("%d ", currentVertex);

        for (int i = 0; i < numVertices; i++) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                enqueue(&q, i);
            }
        }
    } printf("\n");
}

int main(void) {
    char choice;
    int numVertices = 0, startVertex = 0;

    int graph[MAX_NODES][MAX_NODES] = {0};
    printf("---------------------------------------\n");
    printf("Breadth-First Search Implementation:\n");
    printf("---------------------------------------\n");
    printf("Enter number of vertices in the graph: ");
    scanf("%d", &numVertices);
    printf("---------------------------------------\n");
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            printf("Does an edge between vertex %d & %d exist? (1: YES, 0: NO): ", i, j);
            scanf("%d", &graph[i][j]);
        } printf("\n");
    }
    while (1) {
        printf("---------------------------------------\n");
        printf("Enter start vertex (0-%d): ", numVertices - 1);
        scanf("%d", &startVertex);
        printf("---------------------------------------\n");
        bfs(graph, numVertices, startVertex);
        printf("---------------------------------------\n");
        printf("Do you want to continue (y/N)?: ");
        scanf(" %c", &choice);
        
        if (choice == 'n' || choice == 'N') {
            printf("Exiting program...\n");
            printf("---------------------------------------\n");
            exit(0);
        }
    }
    return 0;
}