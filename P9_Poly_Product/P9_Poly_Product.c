#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int coeff;
    int exp;
} Term;

typedef struct {
    Term terms[100];
    int size;
} Poly;

Poly *readP() {
    Poly *p = malloc(sizeof(Poly));
    int terms;
    printf("Enter number of terms: ");
    scanf("%d", &terms);
    p->size = terms;

    for (int i = 0; i < terms; i++) {
        int coeff, exp;
        printf("Enter term %d (coeff exp): ", i + 1);
        scanf("%d %d", &coeff, &exp);
        p->terms[i].coeff = coeff;
        p->terms[i].exp = exp;
    }
    return p;
}

void printP(Poly *p) {
    int first = 1;
    for (int i = 0; i < p->size; i++) {
        int coeff = p->terms[i].coeff;
        int exp = p->terms[i].exp;
        if (coeff == 0) continue;

        if (!first && coeff > 0) printf(" + ");
        if (coeff < 0) printf(" - ");

        int absCoeff = coeff < 0 ? -coeff : coeff;

        if (exp == 0) printf("%d", absCoeff);
        else if (exp == 1) printf("%dx", absCoeff);
        else printf("%dx^%d", absCoeff, exp);

        first = 0;
    }
    if (first) printf("0");
    printf("\n");
}

void addTerm(Term t, Poly *p) {
    for (int i = 0; i < p->size; i++) {
        if (t.exp == p->terms[i].exp) {
            p->terms[i].coeff += t.coeff;
            return;
        }
    }
    p->terms[p->size] = t;
    p->size++;
}

Poly *multiply(Poly *p1, Poly *p2) {
    Poly *p = malloc(sizeof(Poly));
    p->size = 0;

    for (int i = 0; i < p1->size; i++) {
        for (int j = 0; j < p2->size; j++) {
            int newCoeff = p1->terms[i].coeff * p2->terms[j].coeff;
            int newExp = p1->terms[i].exp + p2->terms[j].exp;
            Term t;
            t.coeff = newCoeff;
            t.exp = newExp;
            addTerm(t, p);
        }
    }
    return p;
}

int main() {
    printf("-- Reading P1 --- \n");
    Poly *p1 = readP();
    printP(p1);

    printf("-- Reading P2 --- \n");
    Poly *p2 = readP();
    printP(p2);

    Poly *result = multiply(p1, p2);
    printf("Polynomial Multiplication Output: ");
    printP(result);

    free(p1);
    free(p2);
    free(result);
    return 0;
}
