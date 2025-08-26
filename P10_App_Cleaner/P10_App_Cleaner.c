#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char name[50];
    int freq;
    struct Node* next;
};

struct Node* head = NULL;

struct Node* createNode(char* name) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->name, name);
    newNode->freq = 0;
    newNode->next = NULL;
    return newNode;
}

void addApp(char* name) {
    struct Node* newNode = createNode(name);
    if (head == NULL) {
        head = newNode;
    } else {
        struct Node* temp = head;
        while (temp->next != NULL) {
            if (strcmp(temp->name, name) == 0) {
                printf("App already exists.\n");
                free(newNode);
                return;
            }
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf("App '%s' added successfully.\n", name);
}

void openApp(char* name) {
    struct Node* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            temp->freq++;
            printf("Opened %s (frequency = %d)\n", name, temp->freq);
            return;
        }
        temp = temp->next;
    }
    printf("App not found: %s\n", name);
}

void showApps() {
    if (head == NULL) {
        printf("No apps available.\n");
        return;
    }
    struct Node* temp = head;
    printf("Apps and their usage:\n");
    while (temp != NULL) {
        printf("%s (freq = %d)\n", temp->name, temp->freq);
        temp = temp->next;
    }
}

void cleanApps() {
    if (head == NULL) {
        printf("No apps to clean.\n");
        return;
    }

    struct Node* temp = head;
    struct Node* minNode = head;
    struct Node* prev = NULL;
    struct Node* minPrev = NULL;

    while (temp != NULL) {
        if (temp->freq < minNode->freq) {
            minNode = temp;
            minPrev = prev;
        }
        prev = temp;
        temp = temp->next;
    }

    if (minPrev == NULL) {
        head = head->next;
    } else {
        minPrev->next = minNode->next;
    }
    printf("Cleaning (removing): %s (freq = %d)\n", minNode->name, minNode->freq);
    free(minNode);
}

int main() {
    int choice;
    char appName[50];

    while (1) {
        printf("\n--- App Cleaner Menu ---\n");
        printf("1. Add App\n");
        printf("2. Open App\n");
        printf("3. Show All Apps\n");
        printf("4. Clean Least Used App\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter app name: ");
            scanf("%s", appName);
            addApp(appName);
        }
        else if (choice == 2) {
            printf("Enter app name to open: ");
            scanf("%s", appName);
            openApp(appName);
        }
        else if (choice == 3) {
            showApps();
        }
        else if (choice == 4) {
            cleanApps();
        }
        else if (choice == 5) {
            printf("Exiting...\n");
            break;
        }
        else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
