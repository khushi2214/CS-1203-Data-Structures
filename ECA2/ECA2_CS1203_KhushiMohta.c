
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Node structure for adjacency list
struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
};

// Structure to represent the adjacency list
struct AdjList {
    struct AdjListNode* head;
};

// Structure to represent the priority queue node
struct MinHeapNode {
    int v;// Vertex number
    int dist;// Distance value
};

// Structure to represent the priority queue
struct MinHeap {
    int size;// Current size of the heap
    int capacity;// Capacity of the heap
    int* pos;// Positions of vertices in the heap
    struct MinHeapNode** array; // Array to store heap nodes
};

// Function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest, int weight) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
struct AdjList* createGraph(int V) {
    struct AdjList* array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
    for (int i = 0; i < V; ++i)
        array[i].head = NULL;
    return array;
}

// Function to add an edge to the graph
void addEdge(struct AdjList* array, int src, int dest, int weight) {
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = array[src].head;
    array[src].head = newNode;
}

// Function to create a new Min Heap Node
struct MinHeapNode* newMinHeapNode(int v, int dist) {
    struct MinHeapNode* minHeapNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

// Function to create a Min Heap
struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// Function to swap two nodes of the min heap
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Heapify function to maintain the min-heap property
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx) {
        // The nodes to be swapped in min heap
        struct MinHeapNode* smallestNode = minHeap->array[smallest];
        struct MinHeapNode* idxNode = minHeap->array[idx];

        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

// Function to check if the min heap is empty
int isEmpty(struct MinHeap* minHeap) {
    return minHeap->size == 0;
}

// Function to extract the minimum node from the heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    if (isEmpty(minHeap))
        return NULL;

    // Store the root node
    struct MinHeapNode* root = minHeap->array[0];

    // Replace the root node with the last node
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    // Update position of the last node
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    // Reduce heap size and heapify the root
    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// Function to decrease the dist value of a given vertex
void decreaseKey(struct MinHeap* minHeap, int v, int dist) {
    // Get the index of v in heap array
    int i = minHeap->pos[v];

    // Get the node and update its dist value
    minHeap->array[i]->dist = dist;

    // Heapify the heap to maintain heap property
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        // Move to the parent index
        i = (i - 1) / 2;
    }
}

// Function to check if a given vertex is in the min heap
bool isInMinHeap(struct MinHeap* minHeap, int v) {
    if (minHeap->pos[v] < minHeap->size)
        return true;
    return false;
}

// Function to print the solution
void printSolution(int dist[], int n, int parent[]) {
    printf("Vertex \t\t Distance from Source \t\t Parent\n");
    for (int i = 0; i < n; i++)
        printf("%d \t\t\t %d \t\t\t %d\n", i, dist[i], parent[i]);
}

// Dijkstra's algorithm with min heap and adjacency list
void dijkstra(struct AdjList* graph, int src, int V) {
    int dist[V];
    int parent[V];

    // Create a min heap and initialise
    struct MinHeap* minHeap = createMinHeap(V);

    // Initialise distances and heap
    for (int v = 0; v < V; ++v) {
        dist[v] = INT_MAX;
        parent[v] = -1;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    // Set the distance of the source vertex to 0
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    // Initially, the size of the heap is V
    minHeap->size = V;

    // Dijkstra's algorithm
    while (!isEmpty(minHeap)) {
        // Extract the vertex with the minimum distance value
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;

        // Traverse through all adjacent vertices of u and update their distance values
        struct AdjListNode* pCrawl = graph[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;

            // If the new distance is smaller than the current distance, update it
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->weight + dist[u] < dist[v]) {
                dist[v] = dist[u] + pCrawl->weight;
                parent[v] = u;
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }

    // Print the solution
    printSolution(dist, V, parent);

    // Free allocated memory
    free(minHeap->array);
    free(minHeap->pos);
    free(minHeap);
}

int main() {
    int V = 5;
    struct AdjList* graph = createGraph(V);

    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 2, 4);
    addEdge(graph, 1, 3, 5);
    addEdge(graph, 2, 3, 1);
    addEdge(graph, 3, 4, 3);

    dijkstra(graph, 0, V);

    // Free allocated memory
    for (int i = 0; i < V; ++i) {
        struct AdjListNode* current = graph[i].head;
        while (current != NULL) {
            struct AdjListNode* next = current->next;
            free(current);
            current = next;
        }
    }
    free(graph);

    return 0;
}