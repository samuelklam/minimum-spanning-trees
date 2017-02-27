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
#include <array>
#include <cstdlib>
#include <vector>
#include <list>

struct Node {
    int v;
    float dist;
};

class DHeap {
private:
    int d;
    int size;
    int current_size;
    Node *array;
    
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
        size = capacity;
        current_size = 0;
        d = num_children;
        array = new Node[capacity];
        heap_vertex_pos = new int[capacity];
        for (int i = 0 ; i < capacity; i++) {
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
     * Returns heap position if in the heap else -1
     */
    int Find(int v) {
        return (heap_vertex_pos[v] != -1) ? heap_vertex_pos[v] : -1;
    }

    /*
     * Swaps index position in the heap
     */
    void SwapIndexPositionInHeap(Node v1, Node v2, int idx1, int idx2) {
        heap_vertex_pos[v1.v] = idx2;
        heap_vertex_pos[v2.v] = idx1;
    }

    /*
     * Insert element into the heap and Bubble Up to maintain heap properties
     * Note that we store heap elements in the form of [vertex #, distance/weight edge]
     */
    void Insert(int vertex, float distance) {
        if (IsFull()) {
            std::cout << "Warning! We've reached the max heap size." << std::endl;
            return;
        }

        // if we already have the vertex in the heap than we just update the distance
        if (Find(vertex) != -1) {
            array[heap_vertex_pos[vertex]].dist = distance;
            
            MinHeapify(heap_vertex_pos[vertex]);
            BubbleUp(heap_vertex_pos[vertex]);
        }
        // otherwise do our standard insert
        else {
            array[current_size].v = vertex;
            array[current_size].dist = distance;
            heap_vertex_pos[vertex] = current_size;

            BubbleUp(current_size);
            current_size++;
        }
    }

    /*
     * Function BubbleUp
     */
    void BubbleUp(int insert_pos) {
        while (insert_pos > 0 && array[insert_pos].dist < array[GetParent(insert_pos)].dist) {
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
    Node DeleteMin(Node min) {
        if (IsEmpty()) {
            std::cout << "Warning! There are no elements in the heap currently." << std::endl;
            return min;
        }

        min.v = array[0].v;
        min.dist = array[0].dist;

        heap_vertex_pos[array[0].v] = -1;
        if (!IsEmpty()) {
            heap_vertex_pos[array[current_size-1].v] = 0;
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
                if ((child_pos < current_size) && (array[child_pos].dist < array[swap_pos].dist)) {
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
            std::cout << "[" << array[i].v << ", " << array[i].dist << "], ";
        std::cout << std::endl;
    }
};

/*
 * Using adjacency list
 */
struct node{
    int index;
    float weight;
};

std::vector<std::list<node>> adj_list(int dim, int n){
    std::vector<std::list<node>> adjlist;
    
    std::list<node> clean;
    clean.clear();
    srand((unsigned)time(NULL));
    // adj list
    
    for (int i = 0; i < n; i++)
    {
        adjlist.push_back(clean);
    }
    
    if(dim == 0)
    {
        for (int i = 0; i < n; i ++)
        {
            adjlist.push_back(clean);
            for (int j = i + 1; j < n; j++)
            {
                node ins;
                ins.index = j;
                ins.weight = (float)rand() / RAND_MAX;
                adjlist[i].push_back(ins);
                adjlist[j].push_back(ins);
            }
        }
    }
    
    else if(dim == 2)
    {
        float x_coords[n];
        float y_coords[n];
        
        // initialize x_coords and y_coords
        // note that x[0], y[0] denotes the coords for the 0th vertex
        for (int a = 0; a < n; a++) {
            x_coords[a] = (float)rand() / RAND_MAX;
            y_coords[a] = (float)rand() / RAND_MAX;
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                node ins;
                ins.index = j;
                // standard Euclidean distance calculation
                ins.weight = sqrt(pow(x_coords[i] - x_coords[j], 2) + (pow(y_coords[i] - y_coords[j], 2)));
                adjlist[i].push_back(ins);
                adjlist[j].push_back(ins);
            }
        }
    }
    
    else if (dim == 3)
    {
        float x_coords[n];
        float y_coords[n];
        float z_coords[n];
        
        // initialize coordinates
        for (int a = 0; a < n; a++) {
            x_coords[a] = (float)rand() / RAND_MAX;
            y_coords[a] = (float)rand() / RAND_MAX;
            z_coords[a] = (float)rand() / RAND_MAX;
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                node ins;
                ins.index = j;
                ins.weight = sqrt(pow(x_coords[i] - x_coords[j], 2) + (pow(y_coords[i] - y_coords[j], 2)) + (pow(z_coords[i] - z_coords[j], 2)));
                adjlist[i].push_back(ins);
                adjlist[j].push_back(ins);
            }
        }
    }
    
    if (dim == 4) {
        
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
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                node ins;
                ins.index = j;
                ins.weight = sqrt(pow(x_coords[i] - x_coords[j], 2) + pow(y_coords[i] - y_coords[j], 2) + pow(z_coords[i] - z_coords[j], 2) + pow(v_coords[i] - v_coords[j], 2));
                adjlist[i].push_back(ins);
                adjlist[j].push_back(ins);
            }
        }
    }
    return adjlist;
    
}

/*
 * Prim's algorithm
 * @param n : # of vertices in the graph
 * @return sum : the sum of the weight of the MST
 */
float Prim(float *x_coords, float *y_coords, float *z_coords, float *v_coords, int n, int dim) {
    float dist[n];
    int prev[n];
    
    Node v = {-1, -1};

    float sum = 0;

    // we compute the optimal children value for the d-ary heap as well
    DHeap min_heap(n, 3);

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

        v = min_heap.DeleteMin(v);

        // mark removed vertex as visited
        vertices[v.v] = 1;
        sum += dist[v.v];

        // iterate over edges of that vertex
        for (int w = 0; w < n; w++) {
            if (vertices[w] == 0) {

                int vertex1 = v.v;
                int vertex2 = w;

                float edge_weight;

                if (dim == 0) {
                    edge_weight = (float)rand() / RAND_MAX;
                }

                else if (dim == 2) {
                    edge_weight = sqrt(pow(x_coords[vertex1] - x_coords[vertex2], 2.0) + (pow(y_coords[vertex1] - y_coords[vertex2], 2.0)));
                }

                else if (dim == 3) {
                    edge_weight = sqrt(pow(x_coords[vertex1] - x_coords[vertex2], 2.0) + (pow(y_coords[vertex1] - y_coords[vertex2], 2.0)) + (pow(z_coords[vertex1] - z_coords[vertex2], 2.0)));
                }

                else if (dim == 4) {
                    edge_weight = sqrt(pow(x_coords[vertex1] - x_coords[vertex2], 2.0) + (pow(y_coords[vertex1] - y_coords[vertex2], 2.0)) + (pow(z_coords[vertex1] - z_coords[vertex2], 2.0)) + (pow(v_coords[vertex1] - v_coords[vertex2], 2.0)));
                }

                if (dist[w] > edge_weight) {
                    dist[w] = edge_weight;
                    prev[w] = v.v;
                    min_heap.Insert(w, dist[w]);
                }
            }
        }
    }

    return sum;
}

int main(int argc, const char * argv[]) {

    if (argc != 5) {
        printf("Invalid arguments.");
        return 1;
    }

    // denotes # of vertices in the graph
    int n = atoi(argv[2]);

    // how many times to calculate prim
    int trials = atoi(argv[3]);

    // dimensons for the problem
    int dim = atoi(argv[4]);

    std::cout << "Command line args: " << n << " " << trials << " " << dim << std::endl;
    
    float sum = 0.0;

    //create and print out adj list
//    std::vector<std::list<node>> adjlist = adj_list(dim, n);
//
//    for (int i = 0; i < n; i++)
//    {
//        for (auto ci = adjlist[i].begin(); ci != adjlist[i].end(); ++ci)
//        {
//            node k = *ci;
//            std::cout<<k.weight<<" ";
//        }
//        std::cout<<std::endl;
//    }

    srand((unsigned)time(NULL));
    for (int i = 0; i < trials; i++) {

        if (dim == 0) {
            float x_coords[1];
            float y_coords[1];
            float z_coords[1];
            float v_coords[1];

            sum += Prim(x_coords, y_coords, z_coords, v_coords, n, dim);
        }

        if (dim == 2) {
            float x_coords[n];
            float y_coords[n];
            float z_coords[1];
            float v_coords[1];

            // initialize coordinates
            for (int a = 0; a < n; a++) {
                x_coords[a] = (float)rand() / RAND_MAX;
                y_coords[a] = (float)rand() / RAND_MAX;
            }

            sum += Prim(x_coords, y_coords, z_coords, v_coords, n, dim);

        }

        else if (dim == 3) {
            float x_coords[n];
            float y_coords[n];
            float z_coords[n];
            float v_coords[1];

            // initialize coordinates
            for (int a = 0; a < n; a++) {
                x_coords[a] = (float)rand() / RAND_MAX;
                y_coords[a] = (float)rand() / RAND_MAX;
                z_coords[a] = (float)rand() / RAND_MAX;
            }

            sum += Prim(x_coords, y_coords, z_coords, v_coords, n, dim);
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

            sum += Prim(x_coords, y_coords, z_coords, v_coords, n, dim);
        }

    }

    sum /= trials;

    std::cout << "Calculated sum: " << sum << std::endl;

    return 0;
}

