#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int listIndex;
    int elemIndex;
} HeapNode;

typedef struct {
    HeapNode *arr;
    int size;
    int capacity;
} MinHeap;

void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MinHeap *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->arr[index].value < heap->arr[parent].value) {
            swap(&heap->arr[index], &heap->arr[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void heapifyDown(MinHeap *heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->arr[left].value < heap->arr[smallest].value)
        smallest = left;
    if (right < heap->size && heap->arr[right].value < heap->arr[smallest].value)
        smallest = right;

    if (smallest != index) {
        swap(&heap->arr[index], &heap->arr[smallest]);
        heapifyDown(heap, smallest);
    }
}

void insertHeap(MinHeap *heap, HeapNode node) {
    if (heap->size == heap->capacity) {
        printf("Heap capacity exceeded!\n");
        exit(1);
    }
    heap->arr[heap->size] = node;
    heapifyUp(heap, heap->size);
    heap->size++;
}

HeapNode removeMin(MinHeap *heap) {
    if (heap->size == 0) {
        printf("Heap is empty!\n");
        exit(1);
    }
    HeapNode root = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->size];
    heapifyDown(heap, 0);
    return root;
}

int main() {
    int k;
    printf("Enter number of sorted lists (k): ");
    scanf("%d", &k);

    int **lists = malloc(k * sizeof(int *));
    int *sizes = malloc(k * sizeof(int));

    printf("Enter size of each list and elements in sorted order:\n");
    for (int i = 0; i < k; i++) {
        printf("Size of list %d: ", i + 1);
        scanf("%d", &sizes[i]);
        lists[i] = malloc(sizes[i] * sizeof(int));
        printf("Elements of list %d: ", i + 1);
        for (int j = 0; j < sizes[i]; j++) {
            scanf("%d", &lists[i][j]);
        }
    }

    MinHeap heap;
    heap.arr = malloc(k * sizeof(HeapNode));
    heap.size = 0;
    heap.capacity = k;

    for (int i = 0; i < k; i++) {
        if (sizes[i] > 0) {
            HeapNode node = {lists[i][0], i, 0};
            insertHeap(&heap, node);
        }
    }

    int totalSize = 0;
    for (int i = 0; i < k; i++) totalSize += sizes[i];
    int *result = malloc(totalSize * sizeof(int));
    int resIndex = 0;

    while (heap.size > 0) {
        HeapNode minNode = removeMin(&heap);
        result[resIndex++] = minNode.value;

        int nextIndex = minNode.elemIndex + 1;
        int listIdx = minNode.listIndex;

        if (nextIndex < sizes[listIdx]) {
            HeapNode nextNode = {lists[listIdx][nextIndex], listIdx, nextIndex};
            insertHeap(&heap, nextNode);
        }
    }

    printf("Merged sorted list: ");
    for (int i = 0; i < resIndex; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    for (int i = 0; i < k; i++) {
        free(lists[i]);
    }
    free(lists);
    free(sizes);
    free(heap.arr);
    free(result);

    return 0;
}
