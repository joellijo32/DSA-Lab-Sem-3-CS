#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int freq;
} App;

typedef struct {
    App apps[100];
    int size;
} AppManager;

void addApp(AppManager *m, char *name) {
    strcpy(m->apps[m->size].name, name);
    m->apps[m->size].freq = 0;
    m->size++;
    printf("App '%s' added successfully.\n", name);
}

void openApp(AppManager *m, char *name) {
    for (int i = 0; i < m->size; i++) {
        if (strcmp(m->apps[i].name, name) == 0) {
            m->apps[i].freq++;
            printf("Opened %s (frequency = %d)\n", name, m->apps[i].freq);
            return;
        }
    }
    printf("App not found: %s\n", name);
}

void showApps(AppManager *m) {
    if (m->size == 0) {
        printf("No apps available.\n");
        return;
    }
    printf("Apps and their usage:\n");
    for (int i = 0; i < m->size; i++) {
        printf("%s (freq = %d)\n", m->apps[i].name, m->apps[i].freq);
    }
}

void cleanApps(AppManager *m) {
    if (m->size == 0) {
        printf("No apps to clean.\n");
        return;
    }

    int minIndex = 0;
    for (int i = 1; i < m->size; i++) {
        if (m->apps[i].freq < m->apps[minIndex].freq) {
            minIndex = i;
        }
    }

    printf("Cleaning (removing): %s (freq = %d)\n", 
           m->apps[minIndex].name, m->apps[minIndex].freq);

    for (int i = minIndex; i < m->size - 1; i++) {
        m->apps[i] = m->apps[i + 1];
    }
    m->size--;
}

int main() {
    AppManager manager;
    manager.size = 0;
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
            addApp(&manager, appName);
        }
        else if (choice == 2) {
            printf("Enter app name to open: ");
            scanf("%s", appName);
            openApp(&manager, appName);
        }
        else if (choice == 3) {
            showApps(&manager);
        }
        else if (choice == 4) {
            cleanApps(&manager);
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
