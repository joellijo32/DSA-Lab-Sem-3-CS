#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char word[50];
    char meaning[100];
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(char word[], char meaning[]) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->word, word);
    strcpy(newNode->meaning, meaning);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, char word[], char meaning[]) {
    if (root == NULL) {
        return createNode(word, meaning);
    }
    
    int cmp = strcmp(word, root->word);
    if (cmp < 0) {
        root->left = insert(root->left, word, meaning);
    } else if (cmp > 0) {
        root->right = insert(root->right, word, meaning);
    } else {
        strcpy(root->meaning, meaning);
    }
    
    return root;
}

struct Node* search(struct Node* root, char word[]) {
    if (root == NULL) {
        return NULL;
    }
    
    int cmp = strcmp(word, root->word);
    if (cmp == 0) {
        return root;
    } else if (cmp < 0) {
        return search(root->left, word);
    } else {
        return search(root->right, word);
    }
}

struct Node* findMin(struct Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

struct Node* deleteNode(struct Node* root, char word[]) {
    if (root == NULL) {
        return root;
    }
    
    int cmp = strcmp(word, root->word);
    if (cmp < 0) {
        root->left = deleteNode(root->left, word);
    } else if (cmp > 0) {
        root->right = deleteNode(root->right, word);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        
        struct Node* temp = findMin(root->right);
        strcpy(root->word, temp->word);
        strcpy(root->meaning, temp->meaning);
        root->right = deleteNode(root->right, temp->word);
    }
    return root;
}

void displayAll(struct Node* root) {
    if (root != NULL) {
        displayAll(root->left);
        printf("%-20s : %s\n", root->word, root->meaning);
        displayAll(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    int choice;
    char word[50], meaning[100];
    
    while (1) {
        printf("\n1. Insert word and meaning\n");
        printf("2. Find meaning of a word\n");
        printf("3. Remove a word\n");
        printf("4. Display all words\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                printf("Enter word: ");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = 0;
                printf("Enter meaning: ");
                fgets(meaning, sizeof(meaning), stdin);
                meaning[strcspn(meaning, "\n")] = 0;
                root = insert(root, word, meaning);
                printf("Word added successfully\n");
                break;
                
            case 2:
                printf("Enter word to search: ");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = 0;
                struct Node* found = search(root, word);
                if (found != NULL) {
                    printf("Meaning: %s\n", found->meaning);
                } else {
                    printf("Word not found in dictionary\n");
                }
                break;
                
            case 3:
                printf("Enter word to remove: ");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = 0;
                struct Node* check = search(root, word);
                if (check != NULL) {
                    root = deleteNode(root, word);
                    printf("Word removed successfully\n");
                } else {
                    printf("Word not found in dictionary\n");
                }
                break;
                
            case 4:
                if (root == NULL) {
                    printf("Dictionary is empty\n");
                } else {
                    printf("\nDictionary contents:\n");
                    printf("%-20s : %s\n", "WORD", "MEANING");
                    printf("----------------------------------------\n");
                    displayAll(root);
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
