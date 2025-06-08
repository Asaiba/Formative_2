#include <stdio.h>
#include <stdlib.h>

#define VILLAGES 7
#define EDGES 10

typedef struct {
    int src, dest, cost;
} Edge;

// Adjacency Matrix
int adjMatrix[VILLAGES][VILLAGES] = {0};

// Disjoint Set for Kruskal’s
int parent[VILLAGES];

// Initialize disjoint sets
void makeSet() {
    for (int i = 0; i < VILLAGES; i++)
        parent[i] = i;
}

// Find root of set
int find(int i) {
    if (parent[i] != i)
        parent[i] = find(parent[i]);
    return parent[i];
}

// Union of two sets
void unionSet(int u, int v) {
    int uRoot = find(u);
    int vRoot = find(v);
    parent[uRoot] = vRoot;
}

// Compare edges by cost
int compare(const void *a, const void *b) {
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    return e1->cost - e2->cost;
}

int main() {
    // Step 1: Define all edges
    Edge edges[EDGES] = {
        {0, 1, 6},   // A-B
        {0, 6, 15},  // A-G
        {1, 2, 11},  // B-C
        {1, 3, 5},   // B-D
        {2, 3, 17},  // C-D
        {2, 5, 9},   // C-F
        {2, 6, 25},  // C-G
        {3, 4, 22},  // D-E
        {4, 5, 10},  // E-F
        {6, 5, 12}   // G-F
    };

    // Step 2: Initialize sets
    makeSet();

    // Step 3: Sort edges by cost
    qsort(edges, EDGES, sizeof(Edge), compare);

    // Step 4: Kruskal’s Algorithm
    Edge mst[VILLAGES - 1];
    int totalCost = 0, mstCount = 0;

    for (int i = 0; i < EDGES && mstCount < VILLAGES - 1; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int cost = edges[i].cost;

        if (find(u) != find(v)) {
            unionSet(u, v);
            mst[mstCount++] = edges[i];
            totalCost += cost;
            adjMatrix[u][v] = cost;
            adjMatrix[v][u] = cost;  // undirected
        }
    }

    // Step 5: Output MST
    printf("Selected Roads (Village-to-Village):\n");
    for (int i = 0; i < mstCount; i++) {
        char from = 'A' + mst[i].src;
        char to = 'A' + mst[i].dest;
        printf("%c - %c : %d\n", from, to, mst[i].cost);
    }

    printf("\nTotal Construction Cost: %d\n", totalCost);

    // Step 6: Output Adjacency Matrix
    printf("\nAdjacency Matrix of MST :\n   ");
    for (int i = 0; i < VILLAGES; i++) printf("%c ", 'A' + i);
    printf("\n");

    for (int i = 0; i < VILLAGES; i++) {
        printf("%c  ", 'A' + i);
        for (int j = 0; j < VILLAGES; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
