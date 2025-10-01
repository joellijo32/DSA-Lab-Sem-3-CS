#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int listIndex;
    int elementIndex;
} HeapNode;

typedef struct {
    HeapNode* arr;
    int size;
} MinHeap;

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(MinHeap* heap, int i) {
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < heap->size && heap->arr[left].value < heap->arr[smallest].value)
        smallest = left;
    if (right < heap->size && heap->arr[right].value < heap->arr[smallest].value)
        smallest = right;

    if (smallest != i) {
        swap(&heap->arr[i], &heap->arr[smallest]);
        heapify(heap, smallest);
    }
}

HeapNode extractMin(MinHeap* heap) {
    HeapNode root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapify(heap, 0);
    return root;
}

void insertHeap(MinHeap* heap, HeapNode node) {
    heap->size++;
    int i = heap->size - 1;
    heap->arr[i] = node;

    while (i != 0 && heap->arr[(i-1)/2].value > heap->arr[i].value) {
        swap(&heap->arr[i], &heap->arr[(i-1)/2]);
        i = (i-1)/2;
    }
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void mergeKSortedArrays(int** lists, int* sizes, int K) {
    MinHeap heap;
    heap.arr = (HeapNode*) malloc(sizeof(HeapNode) * K);
    heap.size = 0;

    for (int i = 0; i < K; i++) {
        if (sizes[i] > 0) {
            HeapNode node;
            node.value = lists[i][0];
            node.listIndex = i;
            node.elementIndex = 1;
            insertHeap(&heap, node);
        }
    }

    printf("\nMerged list: ");
    while (heap.size > 0) {
        HeapNode minNode = extractMin(&heap);
        printf("%d ", minNode.value);

        int li = minNode.listIndex;
        int ei = minNode.elementIndex;

        if (ei < sizes[li]) {
            HeapNode nextNode;
            nextNode.value = lists[li][ei];
            nextNode.listIndex = li;
            nextNode.elementIndex = ei + 1;
            insertHeap(&heap, nextNode);
        }
    }
    printf("\n");

    free(heap.arr);
}

int main() {
    int K;
    printf("Enter number of lists: ");
    scanf("%d", &K);

    int** lists = (int**) malloc(K * sizeof(int*));
    int* sizes = (int*) malloc(K * sizeof(int));

    for (int i = 0; i < K; i++) {
        printf("Enter size of list %d: ", i+1);
        scanf("%d", &sizes[i]);
        lists[i] = (int*) malloc(sizes[i] * sizeof(int));
        printf("Enter elements of list %d: ", i+1);
        for (int j = 0; j < sizes[i]; j++) {
            scanf("%d", &lists[i][j]);
        }
      
        qsort(lists[i], sizes[i], sizeof(int), compare);
    }

    mergeKSortedArrays(lists, sizes, K);

    for (int i = 0; i < K; i++) free(lists[i]);
    free(lists);
    free(sizes);

    return 0;
}
