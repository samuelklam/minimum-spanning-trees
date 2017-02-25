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
#include "helpers.h"

int main(int argc, const char * argv[]) {

    std::cout << "Hello world!" << std::endl;

    int n = 6;
    int d = 2;
    float matrix[6][6];

    MatrixGenerator(matrix, n, d);
//    MatrixPrint(matrix);


//    int sum = Prim(matrix, n);
//
//    std::cout << "Sum here: " <<sum << std::endl;

    // Testing for DHeap Implemetation
    DHeap min_heap(n, 2);
    min_heap.Insert(0, 1);
    min_heap.Insert(1, 3);
    min_heap.Insert(2, 2);
    min_heap.Insert(3, 3);
    min_heap.Insert(3, 4);
    min_heap.Insert(4, 3);
    min_heap.Insert(4, 0);
    min_heap.printHeap();
    int v[2];
    min_heap.DeleteMin(v);
    min_heap.printHeap();
    min_heap.DeleteMin(v);
    min_heap.printHeap();
    min_heap.Insert(1, 3);
    min_heap.Insert(2, 2);
    min_heap.Insert(0, 3);
    min_heap.printHeap();
    min_heap.Insert(0, 0);
    min_heap.printHeap();

    return 0;
}
