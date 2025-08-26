#include <stdio.h>
#include <stdlib.h>

struct Block {
    int size;
    int free;
    int pid;
    struct Block* next;
};

struct Block* createBlock(int size) {
    struct Block* newBlock = (struct Block*)malloc(sizeof(struct Block));
    newBlock->size = size;
    newBlock->free = size;
    newBlock->pid = -1;
    newBlock->next = NULL;
    return newBlock;
}

void reset(struct Block* head) {
    struct Block* temp = head;
    while (temp != NULL) {
        temp->free = temp->size;
        temp->pid = -1;
        temp = temp->next;
    }
}

void allocate(struct Block* head, int process[], int p, int choice) {
    for (int i = 0; i < p; i++) {
        struct Block* target = NULL;
        struct Block* temp = head;

        if (choice == 1) {
            while (temp != NULL) {
                if (temp->free >= process[i]) {
                    target = temp;
                    break;
                }
                temp = temp->next;
            }
        } else if (choice == 2) {
            int min = 1000000;
            while (temp != NULL) {
                if (temp->free >= process[i] && temp->free < min) {
                    min = temp->free;
                    target = temp;
                }
                temp = temp->next;
            }
        } else if (choice == 3) {
            int max = -1;
            while (temp != NULL) {
                if (temp->free >= process[i] && temp->free > max) {
                    max = temp->free;
                    target = temp;
                }
                temp = temp->next;
            }
        }

        if (target != NULL) {
            target->free -= process[i];
            target->pid = i + 1;
            printf("Process %d allocated to block of size %d\n", i + 1, target->size);
        } else {
            printf("Process %d not allocated\n", i + 1);
        }
    }
}

int main() {
    int n, p, size;
    printf("Enter number of memory blocks: ");
    scanf("%d", &n);

    struct Block* head = NULL;
    struct Block* tail = NULL;

    for (int i = 0; i < n; i++) {
        printf("Size of block %d: ", i + 1);
        scanf("%d", &size);
        struct Block* newBlock = createBlock(size);
        if (head == NULL) {
            head = newBlock;
            tail = newBlock;
        } else {
            tail->next = newBlock;
            tail = newBlock;
        }
    }

    printf("Enter number of processes: ");
    scanf("%d", &p);
    int process[p];
    for (int i = 0; i < p; i++) {
        printf("Size of process %d: ", i + 1);
        scanf("%d", &process[i]);
    }

    int ch;
    while (1) {
        printf("\n1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Exit\n");
        scanf("%d", &ch);
        if (ch == 4) break;
        reset(head);
        allocate(head, process, p, ch);
    }
    return 0;
}
