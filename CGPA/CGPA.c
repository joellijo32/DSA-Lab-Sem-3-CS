#include <stdio.h>
#include <string.h>

#define MAX 100

struct Student {
    char name[26];
    char reg[11];
    float cgpa;
};

void bubbleSort(struct Student s[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(s[j].name, s[j + 1].name) > 0) {
                struct Student temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
}

int binarySearch(struct Student s[], int n, char key[]) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        int cmp = strcmp(s[mid].name, key);

        if (cmp == 0) return mid;
        else if (cmp > 0) high = mid - 1;
        else low = mid + 1;
    }
    return -1;
}

int main() {
    struct Student students[MAX];
    int count = 0;

    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("File could not be opened.\n");
        return 1;
    }

    while (fscanf(fp, "%25s %10s %f", students[count].name, students[count].reg, &students[count].cgpa) == 3) {
        count++;
    }
    fclose(fp);

    bubbleSort(students, count);

    printf("Enter student name to search: ");
    char key[26];
    scanf("%s", key);

    int index = binarySearch(students, count, key);
    if (index != -1) {
        printf("\nRecord Found:\n");
        printf("Name: %s\n", students[index].name);
        printf("Register No: %s\n", students[index].reg);
        printf("CGPA: %.2f\n", students[index].cgpa);
    } else {
        printf("\nStudent not found.\n");
    }

    return 0;
}
