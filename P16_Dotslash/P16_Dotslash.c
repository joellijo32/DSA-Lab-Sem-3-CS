#include <stdio.h>
#include <stdlib.h>

#define MAX 50

int dx[4] = {-1, 1, 0, 0};
int dy[5] = {0, 0, -1, 1};

typedef struct {
        int x, y;
}Cell;

typedef struct {
        Cell arr[MAX * MAX];
        int rear, front;
}Queue;

void initQueue(Queue *q) {
        q->front = q->rear = 0;
}

int isEmpty(Queue *q) {
        return q->front == q->rear;
}

void enqueue(Queue *q, Cell c) {
        q->arr[q->rear++] = c;
}

Cell dequeue(Queue *q) {
        return q->arr[q->front++];
}

int isValid(int x, int y, int m, int n, int maze[MAX][MAX], int visited[MAX][MAX]) {
        return (x >= 0 && x < n && y >= 0 && y < m && maze[x][y] == 0 && !visited[x][y]);
}

int bfs(int maze[MAX][MAX], int m, int n, Cell start, Cell end) {
        int visited[MAX][MAX] = { 0 };
        int distance[MAX][MAX];

        
        for(int i=0; i<m; i++) {
                for(int j=0; j<n; j++) {
                        distance[i][j] = -1;
                }
        }

        Queue q;
        initQueue(&q);
        enqueue(&q, start);
        visited[start.x][start.y] = 1;
        distance[start.x][start.y] = 0;

        while(!isEmpty(&q)) {
                Cell curr = dequeue(&q);

                
                if(curr.x == end.x && curr.y == end.y) {
                        return distance[curr.x][curr.y];
                }

                
                for(int i=0; i<4; i++) {
                        int nx = curr.x + dx[i];
                        int ny = curr.y + dy[i];
                        if(isValid(nx, ny, n, m, maze, visited)) {
                                visited[nx][ny] = 1;
                                distance[nx][ny] = distance[curr.x][curr.y] + 1;
                                enqueue(&q, (Cell) {nx, ny});
                        }
                }

        }
        return -1;
}

void disp(int maze[MAX][MAX], int m, int n) {
	for (int i=0; i < m; i++) {
		for (int j=0; j < n; j++)
			printf("%d ", maze[i][j]);
		printf("\n");
	}
}

int main () {
        int m=6, n=8;
	int maze[MAX][MAX] = {
		{0, 0, 0, 0, 1, 0, 0, 0},
		{0, 1, 1, 0, 0, 0, 1, 0},
		{0, 0, 0, 1, 1, 0, 1, 0},
		{0, 1, 0, 1, 1, 0, 1, 0},
		{0, 1, 0, 0, 1, 0, 0, 0},
		{0, 0, 1, 0, 1, 1, 0, 1}
	};

	disp(maze, m, n);

        Cell start, end;
        start.x = 0; 
        start.y = 0; 
        end.x = 5; 
        end.y = 6; 

        int result = bfs(maze, m, n, start, end);

        if (result != -1)
                printf("The Shortest Distance is: %d\n", result);
        else 
                printf("The path can not be found.\n");
	return 0;
}
