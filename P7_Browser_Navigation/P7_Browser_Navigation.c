#include <stdio.h>
#include <string.h>

typedef struct {
    char urls[100][100]; 
    int top;
} Stack;

void init(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == 99; 
}

void push(Stack *s, char url[]) {
    if (!isFull(s)) {
        strcpy(s->urls[++s->top], url);
    }
}

void pop(Stack *s, char url[]) {
    if (!isEmpty(s)) {
        strcpy(url, s->urls[s->top--]);
    }
}

int main() {
    Stack backStack, forwardStack;
    init(&backStack);
    init(&forwardStack);

    char currentPage[100] = "https://ktu.edu.in/";
    char url[100];
    int choice;

    printf("Starting at: %s\n", currentPage);

    do {
        printf("\n1. Visit New Page");
        printf("\n2. Back");
        printf("\n3. Forward");
        printf("\n4. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter new URL: ");
                scanf("%s", url);
                push(&backStack, currentPage);  
                strcpy(currentPage, url);       
                init(&forwardStack);            
                break;

            case 2:
                if (!isEmpty(&backStack)) {
                    push(&forwardStack, currentPage);
                    pop(&backStack, currentPage);
                } else {
                    printf("No page to go back to.\n");
                }
                break;

            case 3:
                if (!isEmpty(&forwardStack)) {
                    push(&backStack, currentPage);
                    pop(&forwardStack, currentPage);
                } else {
                    printf("No page to go forward to.\n");
                }
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

        printf("Current Page: %s\n", currentPage);

    } while(choice != 4);

    return 0;
}
