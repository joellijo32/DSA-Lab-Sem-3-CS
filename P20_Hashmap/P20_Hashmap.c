#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 100   // Increased size to reduce collisions
#define MAX_WORD_LEN 100

typedef struct Node {
    char word[MAX_WORD_LEN];
    struct Node *next;
} Node;

Node *hashTable[TABLE_SIZE];

// Hash function (case-insensitive)
unsigned int hash(char *word) {
    unsigned int sum = 0;
    for (int i = 0; word[i]; i++) {
        sum += tolower(word[i]);
    }
    return sum % TABLE_SIZE;
}

// Insert a word into the hash table
void insert(char *word) {
    unsigned int idx = hash(word);
    Node *newNode = malloc(sizeof(Node));
    strcpy(newNode->word, word);
    newNode->next = hashTable[idx];
    hashTable[idx] = newNode;
}

// Search for a word in the hash table (case-insensitive)
int search(char *word) {
    unsigned int idx = hash(word);
    Node *cur = hashTable[idx];
    while (cur) {
        if (strcasecmp(cur->word, word) == 0) return 1;
        cur = cur->next;
    }
    return 0;
}

// Clean a word: remove non-alphabetic characters and convert to lowercase
void cleanWord(char *word) {
    int j = 0;
    for (int i = 0; word[i]; i++) {
        if (isalpha(word[i])) word[j++] = tolower(word[i]);
    }
    word[j] = '\0';
}

// Check if two words have edit distance exactly one
int editDistanceOne(char *a, char *b) {
    int lenA = strlen(a), lenB = strlen(b);
    if (abs(lenA - lenB) > 1) return 0;

    if (lenA == lenB) {
        int diff = 0;
        for (int i = 0; i < lenA; i++) {
            if (a[i] != b[i]) diff++;
            if (diff > 1) return 0;
        }
        return diff == 1;
    } else if (lenA + 1 == lenB) {
        int i = 0, j = 0, diff = 0;
        while (i < lenA && j < lenB) {
            if (a[i] != b[j]) {
                diff++;
                j++;
                if (diff > 1) return 0;
            } else {
                i++; j++;
            }
        }
        return 1;
    } else if (lenA - 1 == lenB) {
        int i = 0, j = 0, diff = 0;
        while (i < lenA && j < lenB) {
            if (a[i] != b[j]) {
                diff++;
                i++;
                if (diff > 1) return 0;
            } else {
                i++; j++;
            }
        }
        return 1;
    }
    return 0;
}

// Suggest corrections for a misspelt word
void suggestCorrection(char *word) {
    int found = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *cur = hashTable[i];
        while (cur) {
            if (editDistanceOne(word, cur->word)) {
                printf("  Suggestion: %s\n", cur->word);
                found = 1;
            }
            cur = cur->next;
        }
    }
    if (!found) printf("  No suggestions found\n");
}

// Free the hash table memory
void freeHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *cur = hashTable[i];
        while (cur) {
            Node *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
        hashTable[i] = NULL;
    }
}

int main() {
    for (int i = 0; i < TABLE_SIZE; i++) hashTable[i] = NULL;

    FILE *vocab = fopen("vocabulary.txt", "r");
    if (!vocab) {
        printf("Failed to open vocabulary.txt\n");
        return 1;
    }

    char word[MAX_WORD_LEN];
    while (fscanf(vocab, "%s", word) == 1) {
        cleanWord(word);
        if (strlen(word) > 0) insert(word);
    }
    fclose(vocab);

    FILE *doc = fopen("myDocument.txt", "r");
    if (!doc) {
        printf("Failed to open myDocument.txt\n");
        freeHashTable();
        return 1;
    }

    int misspellCount = 0;
    while (fscanf(doc, "%s", word) == 1) {
        cleanWord(word);
        if (strlen(word) == 0) continue;
        if (!search(word)) {
            misspellCount++;
            printf("Misspelt word: %s\n", word);
            suggestCorrection(word);
            printf("\n"); 
        }
    }
    fclose(doc);

    printf("Total misspelt words: %d\n", misspellCount);

    freeHashTable();
    return 0;
}
