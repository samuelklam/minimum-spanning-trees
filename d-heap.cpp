//
//  d-heap.cpp
//  minimum-spanning-trees
//
//  C++ Program to Implement a D-Heap
//

#include "d-heap.hpp"
#include <iostream>

/*
 * Constructor function
 * @param capacity : # of vertexes in the graph
 * @param num_children : # of children that each node has
 */
DHeap::DHeap(int capacity, int num_children) {
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
bool DHeap::IsEmpty() {
    return current_size == 0;
}

/*
 * Checks whether the heap is full or not
 */
bool DHeap::IsFull() {
    return current_size == size;
}

/*
 * Gets the Parent Index from the Child Index
 * @param i : child index
 * @return index of the parent
 */
int DHeap::GetParent(int i) {
    return (i - 1) / d;
}

/*
 * Gets the Kth child's Index from the Parent Index
 * @param i : parent index
 * @param k : k'th child
 * @return index of the kth child
 */
int DHeap::GetKthChild(int i, int k) {
    return (d * i) + k;
}

/*
 * Checks to see what position the vertex is in the heap
 * @param v : vertex #
 * @return : heap position, positive int if in the heap else -1
 */
int DHeap::Find(int v) {
    return (heap_vertex_pos[v] != -1) ? heap_vertex_pos[v] : -1;
}

/*
 * Swaps index position in the heap
 * @param v1 : vertex 1
 * @param v2 : vertex 2
 * @idx1 : heap position index for vertex 1
 * @idx2 : heap position index for vertex 2
 */
void DHeap::SwapIndexPositionInHeap(Node v1, Node v2, int idx1, int idx2) {
    heap_vertex_pos[v1.v] = idx2;
    heap_vertex_pos[v2.v] = idx1;
}

/*
 * Insert element into the heap and MinHeapify and/or Bubble Up to maintain heap properties
 * @param vertex : vertex #
 * @param distance : distance from the vertex
 */
void DHeap::Insert(int vertex, float distance) {
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
 * @param insert_pos : index of the vertex that needs to be Bubble'd up
 */
void DHeap::BubbleUp(int insert_pos) {
    while (insert_pos > 0 && array[insert_pos].dist < array[GetParent(insert_pos)].dist) {
        int parent_pos = GetParent(insert_pos);
        SwapIndexPositionInHeap(array[insert_pos], array[parent_pos], insert_pos, parent_pos);
        std::swap(array[insert_pos], array[parent_pos]);
        insert_pos = parent_pos;
    }
}

/*
 * Deletes the min from the heap and rebalances
 * @param min : stores the min node to be returned
 * @return the minimum distance vertex
 */
Node DHeap::DeleteMin(Node min) {
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
 * @param parent_pos : position of the parent index
 */
void DHeap::MinHeapify(int parent_pos) {
    
    int swap_pos = parent_pos;
    int swap_bool = 1;
    
    while (swap_bool) {
        // iterate over the children to find the smallest value to swap with
        for (int i = 1; i < d + 1; i++) {
            int child_pos = GetKthChild(parent_pos, i);
            if (child_pos < current_size) {
                if (array[child_pos].dist < array[swap_pos].dist) {
                    swap_pos = child_pos;
                }
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
void DHeap::printHeap() {
    for (int i = 0; i < current_size; i++)
        std::cout << "[" << array[i].v << ", " << array[i].dist << "], ";
    std::cout << std::endl;
}
