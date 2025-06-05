#include <stdio.h>

#define MAX_SIZE 100

int heap[MAX_SIZE];
char taskNames[MAX_SIZE];
int size = 0;

// Swap function
void swap(int *a, int *b, char *c, char *d) {
    int temp = *a;
    *a = *b;
    *b = temp;

    char tempChar = *c;
    *c = *d;
    *d = tempChar;
}

// Heapify down
void heapifyDown(int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < size && heap[left] > heap[largest])
        largest = left;
    if (right < size && heap[right] > heap[largest])
        largest = right;

    if (largest != i) {
        swap(&heap[i], &heap[largest], &taskNames[i], &taskNames[largest]);
        heapifyDown(largest);
    }
}

// Heapify up
void heapifyUp(int i) {
    while (i != 0 && heap[(i - 1) / 2] < heap[i]) {
        int parent = (i - 1) / 2;
        swap(&heap[i], &heap[parent], &taskNames[i], &taskNames[parent]);
        i = parent;
    }
}

// Insert task into heap
void insert(int priority, char name) {
    heap[size] = priority;
    taskNames[size] = name;
    heapifyUp(size);
    size++;
}

// Remove root (max) from heap
void deleteMax() {
    if (size == 0) return;
    heap[0] = heap[size - 1];
    taskNames[0] = taskNames[size - 1];
    size--;
    heapifyDown(0);
}

// Print heap as it is (not sorted)
void printHeap() {
    printf("Heap:\n");
    for (int i = 0; i < size; i++) {
        printf("%c(%d) ", taskNames[i], heap[i]);
    }
    printf("\n");
}

// Print tasks in descending order by repeatedly deleting max
void printDescendingOrder() {
    printf("\nTasks in descending priority:\n");
    int originalSize = size;
    int tempHeap[MAX_SIZE];
    char tempNames[MAX_SIZE];

    // Backup current heap
    for (int i = 0; i < size; i++) {
        tempHeap[i] = heap[i];
        tempNames[i] = taskNames[i];
    }

    while (size > 0) {
        printf("%c(%d) ", taskNames[0], heap[0]);
        deleteMax();
    }

    // Restore heap
    for (int i = 0; i < originalSize; i++) {
        heap[i] = tempHeap[i];
        taskNames[i] = tempNames[i];
    }
    size = originalSize;
}

// Build heap from initial array using bottom-up heapify
void buildHeap(int arr[], int n) {
    size = n;
    for (int i = 0; i < n; i++) {
        heap[i] = arr[i];
        taskNames[i] = 'A' + i;  // Assign names A, B, C...
    }

    for (int i = (size / 2) - 1; i >= 0; i--) {
        heapifyDown(i);
    }
}

int main() {
    // Initial task priorities
    int initial[] = {21, 18, 85, 15, 36, 75, 63, 65, 90, 70, 89};
    int n = sizeof(initial)/sizeof(initial[0]);

    // Step 1: Build max-heap from array
    buildHeap(initial, n);
    printf("Max-Heap after building:\n");
    printHeap();

    // Step 2: Insert L(96)
    insert(96, 'L');
    printf("\nAfter inserting L(96):\n");
    printHeap();

    // Step 3: Remove L(96)
    deleteMax();
    printf("\nAfter removing L(96):\n");
    printHeap();


    return 0;
}