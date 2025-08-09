#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char opStack[100];
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

int isVariable(char ch) {
    return isalpha(ch);
}

void infixToPostfix(char* infix, char* postfix) {
    int i = 0, j = 0;
    char ch;
    while ((ch = infix[i++]) != '\0') {
        if (isVariable(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            pushOp(ch);
        } else if (ch == ')') {
            while (peekOp() != '(')
                postfix[j++] = popOp();
            popOp(); // remove '('
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

int valStack[100];
int valTop = -1;

void pushVal(int val) {
    valStack[++valTop] = val;
}

int popVal() {
    return valStack[valTop--];
}

int evaluatePostfix(char* postfix) {
    int varValues[26] = {0};
    int usedVars[26] = {0};
    int i = 0;
    char ch;
    while ((ch = postfix[i++]) != '\0') {
        if (isVariable(ch))
            usedVars[ch - 'a'] = 1;
    }
    for (int j = 0; j < 26; j++) {
        if (usedVars[j]) {
            printf("Enter value for %c: ", 'a' + j);
            scanf("%d", &varValues[j]);
        }
    }
    i = 0;
    while ((ch = postfix[i++]) != '\0') {
        if (isVariable(ch)) {
            pushVal(varValues[ch - 'a']);
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
    char infix[100] = "", postfix[100] = "";
    int expressionAvailable = 0;

    while (1) {
        printf("\n1. Convert Infix to Postfix\n");
        printf("2. Evaluate Postfix\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter infix expression: ");
                fgets(infix, sizeof(infix), stdin);
                infix[strcspn(infix, "\n")] = '\0';
                opTop = -1;
                infixToPostfix(infix, postfix);
                printf("Postfix: %s\n", postfix);
                expressionAvailable = 1;
                break;

            case 2:
                if (!expressionAvailable) {
                    printf("No postfix expression available. Convert infix first.\n");
                } else {
                    printf("Postfix: %s\n", postfix);
                    valTop = -1;
                    printf("Result: %d\n", evaluatePostfix(postfix));
                }
                break;

            case 3:
                exit(0);

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
