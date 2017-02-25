//
//  main.cpp
//  minimum-spanning-trees
//
//  Created on 2/24/17.
//

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <iomanip>
#include <array>

/*
 * Generates and returns an adjacency matrix
 * @param n : # of vertices in the matrix
 * @param dim : dimension of the matrix
 */
template<int MAX_ROW, int MAX_COL>

void MatrixGenerator(float (&matrix)[MAX_ROW][MAX_COL], int n, int dim) {
    srand((unsigned)time(NULL));
    
    if (dim == 0) {
        // skips the diagonal and copies symmetric value of matrix to other side
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                matrix[i][j] = (float)rand() / RAND_MAX;
                matrix[j][i] = matrix[i][j];
            }
        }
    }
    
    else if (dim == 2) {
        
        float x_coords[n];
        float y_coords[n];
        
        // initialize x_coords and y_coords
        // note that x[0], y[0] denotes the coords for the 0th vertex
        for (int a = 0; a < n; a++) {
            x_coords[a] = (float)rand() / RAND_MAX;
            y_coords[a] = (float)rand() / RAND_MAX;
        }
        
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                // standard Euclidean distance calculation
                matrix[i][j] = sqrt(pow(x_coords[i] - x_coords[j], 2) + (pow(y_coords[i] - y_coords[j], 2)));
                matrix[j][i] = matrix[i][j];
            }
        }
        
    }
    
    else if (dim == 3) {
        
        float x_coords[n];
        float y_coords[n];
        float z_coords[n];
        
        // initialize coordinates
        for (int a = 0; a < n; a++) {
            x_coords[a] = (float)rand() / RAND_MAX;
            y_coords[a] = (float)rand() / RAND_MAX;
            z_coords[a] = (float)rand() / RAND_MAX;
        }
        
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                matrix[i][j] = sqrt(pow(x_coords[i] - x_coords[j], 2) + (pow(y_coords[i] - y_coords[j], 2)) + (pow(z_coords[i] - z_coords[j], 2)));
                matrix[j][i] = matrix[i][j];
            }
        }
    }
    
    else if (dim == 4) {
        
        float x_coords[n];
        float y_coords[n];
        float z_coords[n];
        float v_coords[n];
        
        // initialize coordinates
        for (int a = 0; a < n; a++) {
            x_coords[a] = (float)rand() / RAND_MAX;
            y_coords[a] = (float)rand() / RAND_MAX;
            z_coords[a] = (float)rand() / RAND_MAX;
            v_coords[a] = (float)rand() / RAND_MAX;
        }
        
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                matrix[i][j] = sqrt(pow(x_coords[i] - x_coords[j], 2) + pow(y_coords[i] - y_coords[j], 2) + pow(z_coords[i] - z_coords[j], 2) + pow(v_coords[i] - v_coords[j], 2));
                matrix[j][i] = matrix[i][j];
            }
        }
    }
    
}

/*
 * Prints resulting matrix for debugging and testing purpose
 * @param matrix : pointer to a 2d matrix
 */
template<int MAX_ROW, int MAX_COL>

void MatrixPrint(float (&matrix)[MAX_ROW][MAX_COL]) {
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            std::cout << std::setw(10) << std::left << matrix[i][j];
        }
        std::cout << std::endl;
    }
}

/*
 * Min Binary heap
 */


/*
 * Prim's algorithm
 */


class DHeap {
private:
    int d;
    int size;
    int current_size;
    int **array;
    // we use this array to track the position of the vertex in the heap
    // positive int denotes its position in the array, -1 if not in the heap
    int *heap_vertex_pos;
    
public:
    /*
     * Constructor function
     * @param capacity : should be the # of vertexes in the graph
     * @param num_children : "d" should be optimally calculated beforehand
     */
    DHeap(int capacity, int num_children) {
        size = capacity + 1;
        current_size = 0;
        d = num_children;
        array = new int* [capacity];
        heap_vertex_pos = new int[capacity];
        for (int i = 0 ; i < capacity; i++) {
            array[i] = new int[2];
            heap_vertex_pos[i] = -1;
        }
    }
    
    /*
     * Checks whether the heap is empty or not
     */
    bool IsEmpty() {
        return current_size == 0;
    }
    
    /*
     * Checks whether the heap is full or not
     */
    bool IsFull() {
        return current_size == size;
    }
    
    /*
     * Gets the Parent Index from the Child Index
     */
    int GetParent(int i) {
        return (i - 1) / d;
    }
    
    /*
     * Gets the Kth child's Index from the Parent Index
     */
    int GetKthChild(int i, int k) {
        return (d * i) + k;
    }
    
    /*
     * Checks to see what position the vertex is in the heap
     */
    int Find(int v) {
        return (heap_vertex_pos[v] != -1) ? heap_vertex_pos[v] : -1;
    }
    
    /*
     * Swaps index position in the heap
     */
    void SwapIndexPositionInHeap(int *v1, int *v2, int idx1, int idx2) {
        heap_vertex_pos[v1[0]] = idx2;
        heap_vertex_pos[v2[0]] = idx1;
    }
    
    /*
     * Insert element into the heap and Bubble Up to maintain heap properties
     * Note that we store heap elements in the form of [vertex #, distance/weight edge]
     */
    void Insert(int vertex, int distance) {
        if (IsFull()) {
            std::cout << "Warning! We've reached the max heap size." << std::endl;
            return;
        }
        
        // if we already have the vertex in the heap than we just update the distance
        if (Find(vertex) != -1) {
            array[heap_vertex_pos[vertex]][1] = distance;
            MinHeapify(heap_vertex_pos[vertex]);
            BubbleUp(heap_vertex_pos[vertex]);
        }
        // otherwise do our standard insert
        else {
            array[current_size][0] = vertex;
            array[current_size][1] = distance;
            heap_vertex_pos[vertex] = current_size;
            
            BubbleUp(current_size);
            current_size++;
        }
    }
    
    /*
     * Function BubbleUp
     */
    void BubbleUp(int insert_pos) {
        while (insert_pos > 0 && array[insert_pos][1] < array[GetParent(insert_pos)][1]) {
            int parent_pos = GetParent(insert_pos);
            SwapIndexPositionInHeap(array[insert_pos], array[parent_pos], insert_pos, parent_pos);
            std::swap(array[insert_pos], array[parent_pos]);
            insert_pos = parent_pos;
        }
    }

    /*
     * Delete the min from the heap and rebalances
     * @param min : stores the deleted [vertex, distance]
     */
    float* DeleteMin(float min[2]) {
        if (IsEmpty()) {
            std::cout << "Warning! There are no elements in the heap currently." << std::endl;
            return 0;
        }

        min[0] = array[0][0];
        min[1] = array[0][1];
        
        heap_vertex_pos[array[0][0]] = -1;
        if (!IsEmpty()) {
            heap_vertex_pos[array[current_size-1][0]] = 0;
        }
        array[0] = array[current_size-1];
        current_size--;
        
        MinHeapify(0);
        
        return min;
    }
    
    /*
     * Rearranges the tree rooted at N to be a MIN-HEAP
     */
    void MinHeapify(int parent_pos) {
        
        int swap_pos = parent_pos;
        int swap_bool = 1;
        
        while (swap_bool) {
            // iterate over the children to find the smallest value to swap with
            for (int i = 1; i < d + 1; i++) {
                int child_pos = GetKthChild(parent_pos, i);
                if ((child_pos < current_size) && (array[child_pos][1] < array[swap_pos][1])) {
                    swap_pos = child_pos;
                }
            }
            if (swap_pos != parent_pos) {
                SwapIndexPositionInHeap(array[parent_pos], array[swap_pos], parent_pos, swap_pos);
                std::swap(array[parent_pos], array[swap_pos]);
                parent_pos = swap_pos;
            }
            else {
                swap_bool = 0;
            }
        }
    }
    
    /*
     * Prints heap for debugging and testing purposes
     */
    void printHeap() {
        for (int i = 0; i < current_size; i++)
            std::cout << "[" << array[i][0] << ", " << array[i][1] << "], ";
        std::cout << std::endl;
    }
};

/*
 * Prim's algorithm
 * @param matrix : matrix containing the graph representation
 * @param n : # of vertices in the graph
 * @return sum : the sum of the weight of the MST
 */
template<int MAX_ROW, int MAX_COL>
float Prim(float (&matrix)[MAX_ROW][MAX_COL], int n) {
    float dist[n];
    float prev[n];
    float v[2];
    
    float sum = 0;
    
    DHeap min_heap(n, (pow(n, n-2) / n));
    
    // serves as our set to contain [1, 0] <-> [0th vertex is in MST, 1th vertex not in MST]
    int vertices[n];
    
    for (int i = 1; i < n; i++) {
        
        // initialize all the vertices to not visited
        vertices[i] = 0;
        
        // note that this value should be sufficiently large since the max distance (in hypercube) is less than this
        dist[i] = 10000;
    }
    
    // we will start Prim's from the 0th vertex
    vertices[0] = 1;
    dist[0] = 0;
    
    min_heap.Insert(0, dist[0]);
    
    while (!min_heap.IsEmpty()) {
        
        min_heap.DeleteMin(v);
        
        // mark removed vertex as visited
        vertices[(int)v[0]] = 1;
        sum += dist[(int)v[0]];
        
        // iterate over edges of that vertex
        for (int w = 0; w < n; w++) {
            // check that this vertex is not itself & we haven't visited it before
            if ((v[0] != w) && (v[w] == 0)) {
                if (dist[w] > matrix[(int)v[0]][w]) {
                    dist[w] = matrix[(int)v[0]][w];
                    prev[w] = v[0];
                    min_heap.Insert(w, dist[w]);
                }
            }
        }
    }
    
    return sum;
}


int main(int argc, const char * argv[]) {

    std::cout << "Hello world!" << std::endl;
    
    int n = 3;
    int d = 2;
    float matrix[3][3];
    
    MatrixGenerator(matrix, n, d);
    MatrixPrint(matrix);
    
    float sum = Prim(matrix, n);
    
    std::cout << "Sum here: " << sum << std::endl;
    
    // Testing for DHeap Implemetation
//    DHeap min_heap(n, 2);
//    min_heap.Insert(0, 1);
//    min_heap.Insert(1, 3);
//    min_heap.Insert(2, 2);
//    min_heap.Insert(3, 3);
//    min_heap.Insert(3, 4);
//    min_heap.Insert(4, 3);
//    min_heap.Insert(4, 0);
//    min_heap.printHeap();
//    int v[2];
//    min_heap.DeleteMin(v);
//    min_heap.printHeap();
//    min_heap.DeleteMin(v);
//    min_heap.printHeap();
//    min_heap.Insert(1, 3);
//    min_heap.Insert(2, 2);
//    min_heap.Insert(0, 3);
//    min_heap.printHeap();
//    min_heap.Insert(0, 0);
//    min_heap.printHeap();
//    
    return 0;
}
