#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct Node {
    char data;
    struct Node* left;
    struct Node* right;
};

struct Node* nodeStack[100];
int nodeTop = -1;

char operatorStack[100];
int opTop = -1;

struct Node* createNode(char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void pushNode(struct Node* node) {
    nodeStack[++nodeTop] = node;
}

struct Node* popNode() {
    return nodeStack[nodeTop--];
}

void pushOperator(char op) {
    operatorStack[++opTop] = op;
}

char popOperator() {
    return operatorStack[opTop--];
}

char topOperator() {
    if (opTop >= 0)
        return operatorStack[opTop];
    return '\0';
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int isOperand(char c) {
    return isalnum(c);
}

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void buildSubtree() {
    char op = popOperator();
    struct Node* root = createNode(op);
    root->right = popNode();
    root->left = popNode();
    pushNode(root);
}

struct Node* constructExpressionTree(char* expression) {
    int i = 0;
    while (expression[i] != '\0') {
        char c = expression[i];
        
        if (isOperand(c)) {
            struct Node* newNode = createNode(c);
            pushNode(newNode);
        }
        else if (c == '(') {
            pushOperator(c);
        }
        else if (c == ')') {
            while (topOperator() != '(') {
                buildSubtree();
            }
            popOperator();
        }
        else if (isOperator(c)) {
            while (opTop >= 0 && topOperator() != '(' && 
                   precedence(topOperator()) >= precedence(c)) {
                buildSubtree();
            }
            pushOperator(c);
        }
        i++;
    }
    
    while (opTop >= 0) {
        buildSubtree();
    }
    
    return popNode();
}

void preorderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%c", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void postorderTraversal(struct Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%c", root->data);
    }
}

void displayTree(struct Node* root, int space) {
    if (root == NULL)
        return;
    
    space += 10;
    
    displayTree(root->right, space);
    
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%c\n", root->data);
    
    displayTree(root->left, space);
}

int main() {
    char expression[100];
    int choice;
    struct Node* root = NULL;
    
    while (1) {
        printf("\n1. Input Expression\n");
        printf("2. Display Expression Tree\n");
        printf("3. Display Prefix Notation\n");
        printf("4. Display Postfix Notation\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                nodeTop = -1;
                opTop = -1;
                printf("Enter arithmetic expression: ");
                scanf("%s", expression);
                root = constructExpressionTree(expression);
                printf("Expression tree constructed successfully\n");
                break;
                
            case 2:
                if (root != NULL) {
                    printf("Expression Tree Structure:\n");
                    displayTree(root, 0);
                    printf("\n");
                } else {
                    printf("No expression tree found. Please input expression first.\n");
                }
                break;
                
            case 3:
                if (root != NULL) {
                    printf("Prefix notation: ");
                    preorderTraversal(root);
                    printf("\n");
                } else {
                    printf("No expression tree found. Please input expression first.\n");
                }
                break;
                
            case 4:
                if (root != NULL) {
                    printf("Postfix notation: ");
                    postorderTraversal(root);
                    printf("\n");
                } else {
                    printf("No expression tree found. Please input expression first.\n");
                }
                break;
                
            case 5:
                printf("Exiting...\n");
                return 0;
                
            default:
                printf("Invalid choice\n");
        }
    }
    
    return 0;
}