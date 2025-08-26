#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct Node {
    char data;
    struct Node* left;
    struct Node* right;
};

struct OpNode {
    char op;
    struct OpNode* next;
};

struct NodeNode {
    struct Node* treeNode;
    struct NodeNode* next;
};

struct OpNode* opTop = NULL;
struct NodeNode* nodeTop = NULL;

struct Node* createNode(char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void pushOp(char op) {
    struct OpNode* newOp = (struct OpNode*)malloc(sizeof(struct OpNode));
    newOp->op = op;
    newOp->next = opTop;
    opTop = newOp;
}

char popOp() {
    if (opTop == NULL) return '\0';
    char op = opTop->op;
    struct OpNode* temp = opTop;
    opTop = opTop->next;
    free(temp);
    return op;
}

char topOp() {
    if (opTop == NULL) return '\0';
    return opTop->op;
}

void pushNode(struct Node* n) {
    struct NodeNode* newNode = (struct NodeNode*)malloc(sizeof(struct NodeNode));
    newNode->treeNode = n;
    newNode->next = nodeTop;
    nodeTop = newNode;
}

struct Node* popNode() {
    if (nodeTop == NULL) return NULL;
    struct Node* n = nodeTop->treeNode;
    struct NodeNode* temp = nodeTop;
    nodeTop = nodeTop->next;
    free(temp);
    return n;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void buildSubtree() {
    char op = popOp();
    struct Node* root = createNode(op);
    root->right = popNode();
    root->left = popNode();
    pushNode(root);
}

struct Node* constructExpressionTree(char* expr) {
    int i = 0;
    while (expr[i] != '\0') {
        char c = expr[i];
        if (isalnum(c)) {
            pushNode(createNode(c));
        } else if (c == '(') {
            pushOp(c);
        } else if (c == ')') {
            while (topOp() != '(') buildSubtree();
            popOp();
        } else if (isOperator(c)) {
            while (opTop != NULL && topOp() != '(' && precedence(topOp()) >= precedence(c)) {
                buildSubtree();
            }
            pushOp(c);
        }
        i++;
    }
    while (opTop != NULL) {
        buildSubtree();
    }
    return popNode();
}

void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%c", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%c", root->data);
    }
}

void displayTree(struct Node* root, int space) {
    if (root == NULL) return;
    space += 10;
    displayTree(root->right, space);
    printf("\n");
    for (int i = 10; i < space; i++) printf(" ");
    printf("%c\n", root->data);
    displayTree(root->left, space);
}

int main() {
    char expr[100];
    struct Node* root = NULL;
    int choice;

    while (1) {
        printf("\n1. Input Expression\n");
        printf("2. Display Expression Tree\n");
        printf("3. Display Prefix Notation\n");
        printf("4. Display Postfix Notation\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            opTop = NULL;
            nodeTop = NULL;
            printf("Enter arithmetic expression: ");
            scanf("%s", expr);
            root = constructExpressionTree(expr);
        }
        else if (choice == 2) {
            if (root != NULL) displayTree(root, 0);
        }
        else if (choice == 3) {
            if (root != NULL) {
                preorder(root);
                printf("\n");
            }
        }
        else if (choice == 4) {
            if (root != NULL) {
                postorder(root);
                printf("\n");
            }
        }
        else if (choice == 5) break;
    }
    return 0;
}
