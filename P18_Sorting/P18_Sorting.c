
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

long bubbleSteps = 0, insertionSteps = 0, radixSteps = 0, mergeSteps = 0, quickSteps = 0;

void bubbleSort(int arr[], int n);
void insertionSort(int arr[], int n);
void radixSort(int arr[], int n);
void mergeSort(int arr[], int l, int r);
void quickSort(int arr[], int low, int high);

int partition(int arr[], int low, int high);
void merge(int arr[], int l, int m, int r);

void printArray(int arr[], int n);
int *readFile(char *filename, int *size);
int getMax(int arr[], int n);
void countRadixSort(int arr[], int n, int exp);

int main() {
    int *arr = NULL;
    int size = 0;
    int choice;
    int *tempArr = NULL;

    char filename[] = "integers.txt"; 

    printf("Reading numbers from file: %s\n", filename);

    arr = readFile(filename, &size);
    if (!arr) {
        printf("Failed to read file or file empty.\n");
        return 1;
    }

    do {
        printf("\n--- Sorting Menu ---\n");
        printf("1. Bubble Sort\n");
        printf("2. Insertion Sort\n");
        printf("3. Radix Sort\n");
        printf("4. Merge Sort\n");
        printf("5. Quick Sort\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        tempArr = malloc(size * sizeof(int));
        if (!tempArr) {
            printf("Memory allocation failed.\n");
            free(arr);
            return 1;
        }
        memcpy(tempArr, arr, size * sizeof(int));

        switch (choice) {
            case 1:
                bubbleSteps = 0;
                bubbleSort(tempArr, size);
                printf("Sorted array (Bubble Sort, Descending):\n");
                printArray(tempArr, size);
                printf("Number of steps (comparisons + swaps): %ld\n", bubbleSteps);
                break;

            case 2:
                insertionSteps = 0;
                insertionSort(tempArr, size);
                printf("Sorted array (Insertion Sort, Descending):\n");
                printArray(tempArr, size);
                printf("Number of steps (comparisons + moves): %ld\n", insertionSteps);
                break;

            case 3:
                radixSteps = 0;
                radixSort(tempArr, size);
                printf("Sorted array (Radix Sort, Descending):\n");
                printArray(tempArr, size);
                printf("Number of steps (digit processing steps): %ld\n", radixSteps);
                break;

            case 4:
                mergeSteps = 0;
                mergeSort(tempArr, 0, size - 1);
                printf("Sorted array (Merge Sort, Descending):\n");
                printArray(tempArr, size);
                printf("Number of steps (comparisons + merges): %ld\n", mergeSteps);
                break;

            case 5:
                quickSteps = 0;
                quickSort(tempArr, 0, size - 1);
                printf("Sorted array (Quick Sort, Descending):\n");
                printArray(tempArr, size);
                printf("Number of steps (comparisons + swaps): %ld\n", quickSteps);
                break;

            case 6:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
        free(tempArr);

    } while (choice != 6);

    free(arr);
    return 0;
}

int *readFile(char *filename, int *size) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("File open error");
        return NULL;
    }

    int *arr = malloc(MAX_SIZE * sizeof(int));
    if (!arr) {
        fclose(fp);
        return NULL;
    }

    int num, count = 0;
    while (fscanf(fp, "%d", &num) == 1) {
        if (count == MAX_SIZE) break;
        arr[count++] = num;
    }
    fclose(fp);
    *size = count;
    return arr;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            bubbleSteps++; 
            if (arr[j] < arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                bubbleSteps++;
            }
        }
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        insertionSteps++;  

        while (j >= 0 && arr[j] < key) {
            insertionSteps++;  
            arr[j + 1] = arr[j];
            insertionSteps++;  
            j--;
        }
        if (j >= 0) insertionSteps++; 
        arr[j + 1] = key;
        insertionSteps++;  
    }
}

int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        radixSteps++;
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

void countRadixSort(int arr[], int n, int exp) {
    int output[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
        radixSteps++;
    }

    for (int i = 8; i >= 0; i--) {
        count[i] += count[i+1];
        radixSteps++;
    }

    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
        radixSteps++;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
        radixSteps++;
    }
}

void radixSort(int arr[], int n) {
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10) {
        countRadixSort(arr, n, exp);
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
        mergeSteps++;
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
        mergeSteps++;
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        mergeSteps++; 
        if (L[i] >= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) {
        arr[k++] = L[i++];
        mergeSteps++;
    }
    while (j < n2) {
        arr[k++] = R[j++];
        mergeSteps++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        quickSteps++;
        if (arr[j] >= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            quickSteps++;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    quickSteps++;
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
