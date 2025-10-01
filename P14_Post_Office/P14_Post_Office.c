#include <stdio.h>
#include <stdlib.h>

struct Queue {
    int tokens[100];
    int front, rear;
};

void initQueue(struct Queue* q) {
    q->front = q->rear = -1;
}

int isEmpty(struct Queue* q) {
    return q->front == -1;
}

void enqueue(struct Queue* q, int token) {
    if (q->rear == 99) return;
    if (q->front == -1) q->front = 0;
    q->rear++;
    q->tokens[q->rear] = token;
}

int dequeue(struct Queue* q) {
    if (isEmpty(q)) return -1;
    int token = q->tokens[q->front];
    if (q->front == q->rear) q->front = q->rear = -1;
    else q->front++;
    return token;
}

void displayQueue(struct Queue* q, const char* name) {
    if (isEmpty(q)) return;
    printf("%s queue tokens: ", name);
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->tokens[i]);
    }
    printf("\n");
}

int main() {
    struct Queue differentlyAbled, seniorCitizen, defencePersonnel, normalPerson;
    initQueue(&differentlyAbled);
    initQueue(&seniorCitizen);
    initQueue(&defencePersonnel);
    initQueue(&normalPerson);

    int tokenCounter = 1;
    int choice;

    while (1) {
        printf("\n--- Post Office Menu ---\n");
        printf("1. Add Customer\n");
        printf("2. Serve Next Customer\n");
        printf("3. Display Waiting Customers\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int category;
                printf("Enter category (1-Defence, 2-Differently abled, 3-Senior citizen, 4-Normal): ");
                scanf("%d", &category);
                switch(category) {
                    case 1: enqueue(&defencePersonnel, tokenCounter); break;
                    case 2: enqueue(&differentlyAbled, tokenCounter); break;
                    case 3: enqueue(&seniorCitizen, tokenCounter); break;
                    case 4: enqueue(&normalPerson, tokenCounter); break;
                    default: printf("Invalid category!\n"); continue;
                }
                printf("Token %d issued.\n", tokenCounter);
                tokenCounter++;
                break;
            }
            case 2: {
                int served = -1;
                const char* categoryName = "";
                if (!isEmpty(&differentlyAbled)) {
                    served = dequeue(&differentlyAbled);
                    categoryName = "Differently Abled";
                }
                else if (!isEmpty(&seniorCitizen)) {
                    served = dequeue(&seniorCitizen);
                    categoryName = "Senior Citizen";
                }
                else if (!isEmpty(&defencePersonnel)) {
                    served = dequeue(&defencePersonnel);
                    categoryName = "Defence Personnel";
                }
                else if (!isEmpty(&normalPerson)) {
                    served = dequeue(&normalPerson);
                    categoryName = "Normal";
                }

                if (served != -1)
                    printf("Serving token %d (%s)\n", served, categoryName);
                else
                    printf("No customers waiting.\n");
                break;
            }
            case 3:
                printf("\n--- Waiting Customers (Token Numbers by Category) ---\n");
                displayQueue(&differentlyAbled, "Differently Abled");
                displayQueue(&seniorCitizen, "Senior Citizen");
                displayQueue(&defencePersonnel, "Defence Personnel");
                displayQueue(&normalPerson, "Normal");
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
