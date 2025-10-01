#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Block {
    int start, size;
    int free;
    char pname[5];
    struct Block *next;
} Block;

Block *head = NULL;   // circular linked list head

// Create new block
Block* new_block(int start, int size, char *pname, int free) {
    Block *b = (Block*)malloc(sizeof(Block));
    b->start = start;
    b->size = size;
    b->free = free;
    strcpy(b->pname, pname);
    b->next = NULL;
    return b;
}

// Insert block into circular list
void insert_block(Block *b) {
    if (!head) {
        head = b;
        b->next = b;
        return;
    }
    Block *temp = head;
    while (temp->next != head) temp = temp->next;
    temp->next = b;
    b->next = head;
}

// Merge adjacent free blocks
void merge_blocks() {
    if (!head) return;
    Block *curr = head;
    do {
        Block *next = curr->next;
        if (curr->free && next->free && curr->start + curr->size == next->start) {
            curr->size += next->size;
            curr->next = next->next;
            if (next == head) head = curr;
            free(next);
            continue;
        }
        curr = curr->next;
    } while (curr != head);
}

// Allocation functions
int allocate_first_fit(char *pname, int size) {
    Block *curr = head;
    if (!curr) return 0;
    do {
        if (curr->free && curr->size >= size) {
            if (curr->size == size) {
                curr->free = 0;
                strcpy(curr->pname, pname);
            } else {
                Block *newb = new_block(curr->start + size, curr->size - size, "HOLE", 1);
                newb->next = curr->next;
                curr->next = newb;
                curr->size = size;
                curr->free = 0;
                strcpy(curr->pname, pname);
            }
            return 1;
        }
        curr = curr->next;
    } while (curr != head);
    return 0;
}

int allocate_best_fit(char *pname, int size) {
    Block *curr = head, *best = NULL;
    if (!curr) return 0;
    do {
        if (curr->free && curr->size >= size) {
            if (!best || curr->size < best->size)
                best = curr;
        }
        curr = curr->next;
    } while (curr != head);

    if (!best) return 0;
    if (best->size == size) {
        best->free = 0;
        strcpy(best->pname, pname);
    } else {
        Block *newb = new_block(best->start + size, best->size - size, "HOLE", 1);
        newb->next = best->next;
        best->next = newb;
        best->size = size;
        best->free = 0;
        strcpy(best->pname, pname);
    }
    return 1;
}

int allocate_worst_fit(char *pname, int size) {
    Block *curr = head, *worst = NULL;
    if (!curr) return 0;
    do {
        if (curr->free && curr->size >= size) {
            if (!worst || curr->size > worst->size)
                worst = curr;
        }
        curr = curr->next;
    } while (curr != head);

    if (!worst) return 0;
    if (worst->size == size) {
        worst->free = 0;
        strcpy(worst->pname, pname);
    } else {
        Block *newb = new_block(worst->start + size, worst->size - size, "HOLE", 1);
        newb->next = worst->next;
        worst->next = newb;
        worst->size = size;
        worst->free = 0;
        strcpy(worst->pname, pname);
    }
    return 1;
}

// Deallocate
void deallocate(char *pname) {
    Block *curr = head;
    if (!curr) return;
    do {
        if (!curr->free && strcmp(curr->pname, pname) == 0) {
            curr->free = 1;
            strcpy(curr->pname, "HOLE");
            merge_blocks();
            return;
        }
        curr = curr->next;
    } while (curr != head);
}

// Print memory map
void print_memory() {
    Block *curr = head;
    if (!curr) return;
    printf("Memory Map:\n");
    do {
        printf("[%d - %d] %s %s (%dKB)\n",
               curr->start,
               curr->start + curr->size,
               curr->pname,
               curr->free ? "FREE" : "USED",
               curr->size);
        curr = curr->next;
    } while (curr != head);
    printf("\n");
}

// Clone memory map (for testing each strategy independently)
Block* clone_memory(Block *orig) {
    if (!orig) return NULL;
    Block *clone_head = NULL, *last = NULL;
    Block *curr = orig;
    do {
        Block *copy = new_block(curr->start, curr->size, curr->pname, curr->free);
        if (!clone_head) {
            clone_head = copy;
            copy->next = clone_head;
            last = copy;
        } else {
            last->next = copy;
            copy->next = clone_head;
            last = copy;
        }
        curr = curr->next;
    } while (curr != orig);
    return clone_head;
}

// Run simulation with a strategy
int run_simulation(int strategy) {
    head = NULL;

    // Initialize memory map as per figure
    insert_block(new_block(0, 10, "P5", 0));
    insert_block(new_block(10, 300, "HOLE", 1));
    insert_block(new_block(310, 90, "P6", 0));
    insert_block(new_block(400, 600, "HOLE", 1));
    insert_block(new_block(1000, 500, "P1", 0));
    insert_block(new_block(1500, 350, "HOLE", 1));
    insert_block(new_block(1850, 150, "P2", 0));
    insert_block(new_block(2000, 200, "HOLE", 1));
    insert_block(new_block(2200, 100, "P4", 0));
    insert_block(new_block(2300, 850, "HOLE", 1));
    insert_block(new_block(3150, 350, "P3", 0));
    insert_block(new_block(3500, 500, "HOLE", 1));

    int success = 0;

    // Allocation/Deallocation sequence
    if ((strategy == 1 ? allocate_first_fit("P7",115) : (strategy==2 ? allocate_best_fit("P7",115) : allocate_worst_fit("P7",115)))) success++;
    if ((strategy == 1 ? allocate_first_fit("P10",650) : (strategy==2 ? allocate_best_fit("P10",650) : allocate_worst_fit("P10",650)))) success++;
    deallocate("P3");
    deallocate("P1");
    deallocate("P6");
    if ((strategy == 1 ? allocate_first_fit("P8",200) : (strategy==2 ? allocate_best_fit("P8",200) : allocate_worst_fit("P8",200)))) success++;
    deallocate("P5");
    deallocate("P2");
    if ((strategy == 1 ? allocate_first_fit("P9",37) : (strategy==2 ? allocate_best_fit("P9",37) : allocate_worst_fit("P9",37)))) success++;
    deallocate("P10");
    deallocate("P9");
    deallocate("P4");

    return success;
}

int main() {
    int ff = run_simulation(1);
    int bf = run_simulation(2);
    int wf = run_simulation(3);

    printf("Successful allocations:\n");
    printf("First Fit: %d\n", ff);
    printf("Best Fit : %d\n", bf);
    printf("Worst Fit: %d\n", wf);

    if (bf >= ff && bf >= wf) printf("\nBest Fit performs the best.\n");
    else if (ff >= bf && ff >= wf) printf("\nFirst Fit performs the best.\n");
    else printf("\nWorst Fit performs the best.\n");

    return 0;
}
