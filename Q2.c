#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100

typedef struct {
    char name[50];
    int severity;
} Patient;

Patient heap[MAX_PATIENTS];
int size = 0;

// Swap two patients
void swap(Patient *a, Patient *b) {
    Patient temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify up (after insert)
void heapifyUp(int index) {
    if (index == 0) return;
    int parent = (index - 1) / 2;
    if (heap[index].severity > heap[parent].severity) {
        swap(&heap[index], &heap[parent]);
        heapifyUp(parent);
    }
}

// Heapify down (after removal)
void heapifyDown(int index) {
    int largest = index;
    int left = 2*index + 1;
    int right = 2*index + 2;

    if (left < size && heap[left].severity > heap[largest].severity)
        largest = left;
    if (right < size && heap[right].severity > heap[largest].severity)
        largest = right;

    if (largest != index) {
        swap(&heap[index], &heap[largest]);
        heapifyDown(largest);
    }
}

// Insert new patient
void insertPatient(char name[], int severity) {
    strcpy(heap[size].name, name);
    heap[size].severity = severity;
    heapifyUp(size);
    size++;
}

// Extract (treat) most severe patient
Patient treatPatient() {
    Patient mostSevere = heap[0];
    heap[0] = heap[size - 1];
    size--;
    heapifyDown(0);
    return mostSevere;
}

// Remove a patient by severity score (e.g., patient transferred)
void removeBySeverity(int severity) {
    int index = -1;
    for (int i = 0; i < size; i++) {
        if (heap[i].severity == severity) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Patient with severity %d not found.\n", severity);
        return;
    }

    heap[index] = heap[size - 1];
    size--;
    heapifyDown(index);
}

// Display heap (current queue)
void displayQueue() {
    printf("\nCurrent Emergency Queue:\n");
    for (int i = 0; i < size; i++) {
        printf("Patient: %-10s | Severity: %d\n", heap[i].name, heap[i].severity);
    }
}

// Display treatment order (by severity)
void displayTreatmentOrder() {
    printf("\nTreatment Order (by severity):\n");
    while (size > 0) {
        Patient p = treatPatient();
        printf("Treating: %-10s | Severity: %d\n", p.name, p.severity);
    }
}

int main() {
    // Step 1: Add initial patients
    insertPatient("John", 70);
    insertPatient("Maria", 85);
    insertPatient("Liam", 60);
    insertPatient("Amina", 95);
    insertPatient("Grace", 75);
    insertPatient("David", 80);

    displayQueue();

    // Step 2: Insert a new critical patient
    printf("\nNew critical patient 'Elijah' with severity 96 arrives.\n");
    insertPatient("Elijah", 96);
    displayQueue();

    // Step 3: Remove Elijah (transferred elsewhere)
    printf("\nPatient 'Elijah' (severity 96) transferred elsewhere. Removing...\n");
    removeBySeverity(96);
    displayQueue();

    // Step 4: Display treatment order
    displayTreatmentOrder();

    return 0;
}