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
        for (int i = 0 ; i < capacity + 1; i++) {
            array[i] = new int[2];
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
     * Function to insert element
     * Note that we store heap elements in the form of [vertex #, distance/weight edge]
     */
    void insert(int vertex, int distance) {
        if (IsFull()) {
            std::cout << "Warning! We've reached the max heap size." << std::endl;
            return;
        }

        array[current_size][0] = vertex;
        array[current_size][1] = distance;
        
        BubbleUp(current_size);
        current_size++;
    }
    
    /*
     * Function BubbleUp
     */
    void BubbleUp(int insert_pos) {
        while (insert_pos > 0 && array[insert_pos][1] < array[GetParent(insert_pos)][1]) {
            int parent = GetParent(insert_pos);
            std::swap(array[insert_pos], array[parent]);
            insert_pos = parent;
        }
    }

    /*
     * Delete the min from the heap and rebalances
     * @param min : stores the deleted [vertex, distance]
     */
    int* DeleteMin() {
        if (IsEmpty()) {
            std::cout << "Warning! There are no elements in the heap currently." << std::endl;
            return 0;
        }

        int min[2];
        min[0] = array[0][0];
        min[1] = array[0][1];
        
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
        bool swap_bool = 1;
        
        while (swap_bool) {
            // iterate over the children to find the smallest value to swap with
            for (int i = 1; i < d + 1; i++) {
                int child_pos = GetKthChild(parent_pos, i);
                if ((child_pos < current_size) && (array[child_pos][1] < array[parent_pos][1])) {
                    swap_pos = child_pos;
                }
            }
            if (swap_pos != parent_pos) {
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


int main(int argc, const char * argv[]) {

//    int n = 6;
//    int d = 3;
//    float matrix[6][6];
    
//    MatrixGenerator(matrix, n, d);
    
//    DHeap min_heap(11, 2);
    
//    MatrixPrint(matrix);
    
    return 0;
}
