//
//  d-heap.hpp
//  minimum-spanning-trees
//
//  C++ Program to Implement a D-Heap
//

#ifndef d_heap_hpp
#define d_heap_hpp

#include <stdio.h>
#include <iostream>

/*
 * Represents a node in the heap
 */
struct Node {
    // vertex #
    int v;
    // distance to the vertex (used in Prim's)
    float dist;
};

/*
 * D-Heap Class
 */
class DHeap {
private:
    // number of children in the heap
    int d;
    // max size of the heap
    int size;
    // current size of the heap
    int current_size;
    // pointer to an array that holds the heap's contents
    Node *array;
    // we use this array to track the position of the vertex in the heap
    // positive int denotes its position in the array, -1 if not in the heap
    int *heap_vertex_pos;
    
public:
    /*
     * Constructor function
     * @param capacity : # of vertexes in the graph
     * @param num_children : # of children that each node has
     */
    DHeap(int capacity, int num_children);
    
    /*
     * Checks whether the heap is empty or not
     */
    bool IsEmpty();
    
    /*
     * Checks whether the heap is full or not
     */
    bool IsFull();
    
    /*
     * Gets the Parent Index from the Child Index
     * @param i : child index
     * @return index of the parent
     */
    int GetParent(int i);
    
    /*
     * Gets the Kth child's Index from the Parent Index
     * @param i : parent index
     * @param k : k'th child
     * @return index of the kth child
     */
    int GetKthChild(int i, int k);
    
    /*
     * Checks to see what position the vertex is in the heap
     * @param v : vertex #
     * @return : heap position, positive int if in the heap else -1
     */
    int Find(int v);
    
    /*
     * Swaps index position in the heap
     * @param v1 : vertex 1
     * @param v2 : vertex 2
     * @idx1 : heap position index for vertex 1
     * @idx2 : heap position index for vertex 2
     */
    void SwapIndexPositionInHeap(Node v1, Node v2, int idx1, int idx2);
    
    /*
     * Insert element into the heap and MinHeapify and/or Bubble Up to maintain heap properties
     * @param vertex : vertex #
     * @param distance : distance from the vertex
     */
    void Insert(int vertex, float distance);
    
    /*
     * Function BubbleUp
     * @param insert_pos : index of the vertex that needs to be Bubble'd up
     */
    void BubbleUp(int insert_pos);
    
    /*
     * Deletes the min from the heap and rebalances
     * @param min : stores the min node to be returned
     * @return the minimum distance vertex
     */
    Node DeleteMin(Node min);
    
    /*
     * Rearranges the tree rooted at N to be a MIN-HEAP
     * @param parent_pos : position of the parent index
     */
    void MinHeapify(int parent_pos);
    
    /*
     * Prints heap for debugging and testing purposes
     */
    void printHeap();
};

#endif /* d_heap_hpp */
