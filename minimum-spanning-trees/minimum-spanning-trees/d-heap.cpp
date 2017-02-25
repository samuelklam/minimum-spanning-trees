//
//  d-heap.cpp
//  minimum-spanning-trees
//
//  C++ Program to Implement a D-Heap
//

#include "d-heap.hpp"
#include <iostream>

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
            array = new int* [capacity + 1];
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
         * Note that we store heap elements in the form of [vertex #, distance (or weight)]
         */
        void insert(int vertex, int distance) {
            if (IsFull()) {
                std::cout << "Warning! We've reached the max heap size." << std::endl;
                return;
            }
            int insert_position = current_size;
            int new_heap_elem[2] = {vertex, distance};
            array[insert_position] = new_heap_elem;
            
            BubbleUp(insert_position);
            current_size++;
        }
        
        /*
         * Gets the smallest element in the heap
         */
        int* FindMin() {
            if (IsEmpty()) {
                std::cout<<"Warning! There are no elements in the heap currently." << std::endl;
                return 0;
            }
            return array[0];
        }
        
        /*
         * Function BubbleUp
         */
        void BubbleUp(int insert_pos)
        {
            int *tmp = array[insert_pos];
            int parent = GetParent(insert_pos);
            while (insert_pos > 0 && tmp[1] < array[parent][1]) {
                array[insert_pos] = array[parent];
                array[parent] = tmp;
                tmp = array[parent];
            }
        }
        
        /*
         * Prints heap for debugging and testing purposes
         */
        void printHeap() {
            for (int i = 0; i < current_size; i++)
                std::cout << "[" << array[i][0] << array[i][1] << "]";
            std::cout << std::endl;
        }
};
