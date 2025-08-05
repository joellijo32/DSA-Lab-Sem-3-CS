#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_DEGREE 7

typedef struct {
    int coeffs[MAX_DEGREE];
} Polynomial;

void initPolynomial(Polynomial* p) {
    int i;
    for (i = 0; i < MAX_DEGREE; i++)
        (*p).coeffs[i] = 0;
}

int parseNumber(const char* str, int* idx) {
    int val = 0;
    while (isdigit(str[*idx])) {
        val = val * 10 + (str[*idx] - '0');
        (*idx)++;
    }
    return val;
}

void parseTerm(char* term, Polynomial* p) {
    int coeff = 0, degree = 0, i = 0;

    // skip leading spaces
    while (term[i] == ' ') i++;

    if (isdigit(term[i]))
        coeff = parseNumber(term, &i);
    else if (term[i] == 'x' || term[i] == 'X') {
        coeff = 1;
    }

    if (term[i] == 'x' || term[i] == 'X') {
        i++;
        if (isdigit(term[i]))
            degree = parseNumber(term, &i);
        else
            degree = 1;
    } else {
        degree = 0;
    }

    if (degree >= 0 && degree < MAX_DEGREE)
        (*p).coeffs[degree] += coeff;
}

void readPolynomial(Polynomial* p) {
    char input[256];
    fgets(input, sizeof(input), stdin);
    char* token = strtok(input, "+\n");
    while (token != NULL) {
        parseTerm(token, p);
        token = strtok(NULL, "+\n");
    }
}

void addPolynomials(Polynomial* raw, Polynomial* mod3, Polynomial a, Polynomial b) {
    int i;
    for (i = 0; i < MAX_DEGREE; i++) {
        int sum = a.coeffs[i] + b.coeffs[i];
        (*raw).coeffs[i] = sum;
        if (sum != 0 && sum % 3 == 0)
            (*mod3).coeffs[i] = 0;
        else
            (*mod3).coeffs[i] = sum;
    }
}

void printPolynomial(Polynomial p) {
    int i, first = 1;
    for (i = MAX_DEGREE - 1; i >= 0; i--) {
        int c = p.coeffs[i];
        if (c == 0) continue;
        if (!first) printf(" + ");
        if (i == 0)
            printf("%d", c);
        else {
            if (c != 1)
                printf("%d", c);
            printf("x");
            if (i > 1)
                printf("%d", i);
        }
        first = 0;
    }
    if (first) printf("0");
    printf("\n");
}

int main() {
    Polynomial m, k, raw_sum, mod_result;
    initPolynomial(&m);
    initPolynomial(&k);
    initPolynomial(&raw_sum);
    initPolynomial(&mod_result);

    printf("k(x) = ");
    readPolynomial(&k);

    printf("m(x) = ");
    readPolynomial(&m);

    addPolynomials(&raw_sum, &mod_result, m, k);

    printf("Raw sum: ");
    printPolynomial(raw_sum);

    printf("Modulo-3 result: ");
    printPolynomial(mod_result);

    return 0;
}

