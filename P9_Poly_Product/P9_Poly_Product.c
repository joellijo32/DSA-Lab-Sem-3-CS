#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int exp;
    struct Node* next;
};

struct Node* createNode(int c, int e) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = c;
    newNode->exp = e;
    newNode->next = NULL;
    return newNode;
}

void insertTerm(struct Node** head, int c, int e) {
    if (c == 0) return;
    struct Node* newNode = createNode(c, e);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    struct Node* prev = NULL;

    while (temp != NULL && temp->exp > e) {
        prev = temp;
        temp = temp->next;
    }
    if (temp != NULL && temp->exp == e) {
        temp->coeff += c;
        free(newNode);
        return;
    }
    if (prev == NULL) {
        newNode->next = *head;
        *head = newNode;
    } else {
        newNode->next = temp;
        prev->next = newNode;
    }
}

struct Node* readPoly() {
    int n, c, e;
    struct Node* head = NULL;
    printf("Enter number of terms: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter term %d (coeff exp): ", i + 1);
        scanf("%d %d", &c, &e);
        insertTerm(&head, c, e);
    }
    return head;
}

void printPoly(struct Node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->coeff > 0 && temp != head) printf(" + ");
        if (temp->exp == 0) printf("%d", temp->coeff);
        else if (temp->exp == 1) printf("%dx", temp->coeff);
        else printf("%dx^%d", temp->coeff, temp->exp);
        temp = temp->next;
    }
    printf("\n");
}

struct Node* multiply(struct Node* p1, struct Node* p2) {
    struct Node* result = NULL;
    for (struct Node* t1 = p1; t1 != NULL; t1 = t1->next) {
        for (struct Node* t2 = p2; t2 != NULL; t2 = t2->next) {
            insertTerm(&result, t1->coeff * t2->coeff, t1->exp + t2->exp);
        }
    }
    return result;
}

int main() {
    printf("-- Reading P1 --\n");
    struct Node* p1 = readPoly();
    printf("P1 = ");
    printPoly(p1);

    printf("-- Reading P2 --\n");
    struct Node* p2 = readPoly();
    printf("P2 = ");
    printPoly(p2);

    struct Node* result = multiply(p1, p2);
    printf("Polynomial Multiplication Output: ");
    printPoly(result);

    return 0;
}
