#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 20

typedef struct {
    int items[MAX_NODES];
    int front;
    int rear;
} Queue;

typedef struct {
    int items[MAX_NODES];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isStackEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, int value) {
    if (s->top == MAX_NODES - 1) {
        printf("Stack is full!\n");
        return;
    }
    s->items[++(s->top)] = value;
}

int pop(Stack *s) {
    if (isStackEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return s->items[(s->top)--];
}

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

void dfs(int graph[MAX_NODES][MAX_NODES], int numVertices, int startVertex) {
    Stack s;
    initStack(&s);

    int visited[MAX_NODES] = {0};

    visited[startVertex] = 1;
    push(&s, startVertex);

    while (!isStackEmpty(&s)) {
        int currentVertex = pop(&s);
        printf("%d ", currentVertex);

        for (int i = 0; i < numVertices; i++) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                push(&s, i);
            }
        }
    } printf("\n");
}

int main(void) {
    int choice;
    int numVertices = 0, startVertex = 0;

    int graph[MAX_NODES][MAX_NODES] = {0};
    printf("---------------------------------------\n");
    printf("Breadth-First Search Implementation:\n");

    while (1) {
        printf("---------------------------------------\n");
        printf("1. Create a graph\n");
        printf("2. Perform BFS\n");
        printf("3. Perform DFS\n");
        printf("4. Exit\n");
        printf("---------------------------------------\n");
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);
        printf("---------------------------------------\n");

        switch (choice) {
            case 1:
                printf("Enter the number of vertices (max %d): ", MAX_NODES);
                scanf("%d", &numVertices);
                if (numVertices > MAX_NODES || numVertices <= 0) {
                    printf("Invalid number of vertices. Please enter a value between 1 and %d.\n", MAX_NODES);
                    numVertices = 0;
                    break;
                }

                printf("Enter the adjacency matrix in terms of existence of vertices (0 or 1):\n");
                for (int i = 0; i < numVertices; i++) {
                    for (int j = 0; j < numVertices; j++) {
                        printf("Does a vertex exist between %d and %d? (0 or 1): ", i, j);
                        scanf("%d", &graph[i][j]);
                    }
                }
                break;

            case 2:
                if (numVertices == 0) {
                    printf("Please create a graph first!\n");
                    break;
                }
                printf("Enter start vertex (0-%d): ", numVertices - 1);
                scanf("%d", &startVertex);
                if (startVertex < 0 || startVertex >= numVertices) {
                    printf("Invalid start vertex. Please enter a value between 0 and %d.\n", numVertices - 1);
                    break;
                }
                bfs(graph, numVertices, startVertex);
                break;

            case 3:
                if (numVertices == 0) {
                    printf("Please create a graph first!\n");
                    break;
                }
                printf("Enter start vertex (0-%d): ", numVertices - 1);
                scanf("%d", &startVertex);
                if (startVertex < 0 || startVertex >= numVertices) {
                    printf("Invalid start vertex. Please enter a value between 0 and %d.\n", numVertices - 1);
                    break;
                }
                dfs(graph, numVertices, startVertex);
                break;

            case 4:
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid choice, please enter a choice from 1-4 only!\n");
        }
    }
    return 0;
}