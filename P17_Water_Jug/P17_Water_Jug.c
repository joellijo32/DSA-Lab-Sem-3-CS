#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 10000

typedef struct {
    int jug10, jug7, jug4;
} State;

typedef struct Node {
    State state;
    struct Node* parent;
    int action;
} Node;

typedef struct {
    Node* nodes[MAX_STATES];
    int front, rear;
} Queue;

int visited[11][8][5]; 

void initQueue(Queue* q) {
    q->front = q->rear = 0;
}

int isEmpty(Queue* q) {
    return q->front == q->rear;
}

void enqueue(Queue* q, Node* node) {
    q->nodes[q->rear++] = node;
}

Node* dequeue(Queue* q) {
    return q->nodes[q->front++];
}

int isVisited(State s) {
    return visited[s.jug10][s.jug7][s.jug4];
}

void markVisited(State s) {
    visited[s.jug10][s.jug7][s.jug4] = 1;
}

int isGoal(State s) {
    return s.jug7 == 2 || s.jug4 == 2;
}

State pour(State s, int from, int to) {
    State newState = s;
    int* jugs[3] = {&newState.jug10, &newState.jug7, &newState.jug4};
    int capacities[3] = {10, 7, 4};
    
    int transfer = *jugs[from];
    int available = capacities[to] - *jugs[to];
    
    if (transfer <= available) {
        *jugs[to] += transfer;
        *jugs[from] = 0;
    } else {
        *jugs[to] = capacities[to];
        *jugs[from] -= available;
    }
    
    return newState;
}

void printAction(int action) {
    char* actions[] = {
        "Pour 10L -> 7L",
        "Pour 10L -> 4L",
        "Pour 7L -> 10L",
        "Pour 7L -> 4L",
        "Pour 4L -> 10L",
        "Pour 4L -> 7L"
    };
    printf("%s\n", actions[action]);
}

void printState(State s) {
    printf("  [10L: %d, 7L: %d, 4L: %d]\n", s.jug10, s.jug7, s.jug4);
}

void printSolution(Node* node) {
    if (node->parent == NULL) {
        printf("\nInitial state:\n");
        printState(node->state);
        return;
    }
    
    printSolution(node->parent);
    printf("\nAction: ");
    printAction(node->action);
    printState(node->state);
}

int solve() {
    Queue q;
    initQueue(&q);
    memset(visited, 0, sizeof(visited));
    
    Node* start = (Node*)malloc(sizeof(Node));
    start->state.jug10 = 0;
    start->state.jug7 = 7;
    start->state.jug4 = 4;
    start->parent = NULL;
    start->action = -1;
    
    enqueue(&q, start);
    markVisited(start->state);
    
    while (!isEmpty(&q)) {
        Node* curr = dequeue(&q);
        
        if (isGoal(curr->state)) {
            printf("Solution found!\n");
            printf("===================\n");
            printSolution(curr);
            printf("\n===================\n");
            printf("Goal achieved: 2 litres in %s container\n", 
                   curr->state.jug7 == 2 ? "7L" : "4L");
            return 1;
        }
        
        for (int from = 0; from < 3; from++) {
            for (int to = 0; to < 3; to++) {
                if (from == to) continue;
                
                State newState = pour(curr->state, from, to);
                
                if (!isVisited(newState)) {
                    Node* newNode = (Node*)malloc(sizeof(Node));
                    newNode->state = newState;
                    newNode->parent = curr;
                    newNode->action = from * 2 + (to > from ? to - 1 : to);
                    
                    enqueue(&q, newNode);
                    markVisited(newState);
                }
            }
        }
    }
    
    printf("No solution found.\n");
    return 0;
}

int main() {
    printf("Water Jug Problem Solver\n");
    printf("========================\n");
    printf("Jugs: 10L (empty), 7L (full), 4L (full)\n");
    printf("Goal: Get exactly 2 litres in 7L or 4L container\n\n");
    
    solve();
    
    return 0;
}