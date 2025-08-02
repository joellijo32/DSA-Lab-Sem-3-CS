#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX 100

char opStack[MAX];
int opTop = -1;

void pushOp(char ch) {
    opStack[++opTop] = ch;
}

char popOp() {
    return opStack[opTop--];
}

char peekOp() {
    return (opTop >= 0) ? opStack[opTop] : '\0';
}

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

void infixToPostfix(char* infix, char* postfix) {
    int i = 0, j = 0;
    char ch;

    while ((ch = infix[i++]) != '\0') {
        if (isdigit(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            pushOp(ch);
        } else if (ch == ')') {
            while (peekOp() != '(')
                postfix[j++] = popOp();
            popOp(); // pop '('
        } else if (isOperator(ch)) {
            while (opTop != -1 && precedence(peekOp()) >= precedence(ch))
                postfix[j++] = popOp();
            pushOp(ch);
        }
    }

    while (opTop != -1)
        postfix[j++] = popOp();
    postfix[j] = '\0';
}

int valStack[MAX];
int valTop = -1;

void pushVal(int val) {
    valStack[++valTop] = val;
}

int popVal() {
    return valStack[valTop--];
}

int evaluatePostfix(char* postfix) {
    int i = 0;
    char ch;

    while ((ch = postfix[i++]) != '\0') {
        if (isdigit(ch)) {
            pushVal(ch - '0'); 
        } else if (isOperator(ch)) {
            int b = popVal();
            int a = popVal();
            int result = 0;
            switch (ch) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
                case '^': result = (int)pow(a, b); break;
            }
            pushVal(result);
        }
    }

    return popVal();
}

int main() {
    int choice;
    char infix[MAX], postfix[MAX];

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Convert Infix to Postfix\n");
        printf("2. Evaluate Postfix\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter infix expression: ");
                fgets(infix, MAX, stdin);
                infix[strcspn(infix, "\n")] = '\0'; 
                opTop = -1;
                infixToPostfix(infix, postfix);
                printf("Postfix expression: %s\n", postfix);
                break;

            case 2:
                printf("Enter postfix expression: ");
                fgets(postfix, MAX, stdin);
                postfix[strcspn(postfix, "\n")] = '\0';
                valTop = -1;
                printf("Result: %d\n", evaluatePostfix(postfix));
                break;

            case 3:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
