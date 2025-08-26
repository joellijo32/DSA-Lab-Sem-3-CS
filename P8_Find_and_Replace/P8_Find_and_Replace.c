#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char word[50];
    struct Node *next;
};

struct Node* createNode(char w[]) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->word, w);
    newNode->next = NULL;
    return newNode;
}

void append(struct Node** head, char w[]) {
    struct Node* newNode = createNode(w);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
}

int findReplace(struct Node* head, char find[], char replace[]) {
    int count = 0;
    struct Node* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->word, find) == 0) {
            strcpy(temp->word, replace);
            count++;
        }
        temp = temp->next;
    }
    return count;
}

void display(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%s ", temp->word);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    char text[1024];
    char *token;
    char find[50], replace[50];

    printf("Enter text: ");
    scanf(" %[^\n]", text);

    token = strtok(text, " ");
    while (token != NULL) {
        append(&head, token);
        token = strtok(NULL, " ");
    }

    printf("--- Entered Text ---\n");
    display(head);

    printf("Enter word to find: ");
    scanf("%s", find);
    printf("Enter replacement word: ");
    scanf("%s", replace);

    int occ = findReplace(head, find, replace);

    printf("%d replacements made\n", occ);
    printf("---- Replaced Text ----\n");
    display(head);

    return 0;
}
