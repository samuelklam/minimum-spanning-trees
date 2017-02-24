//
//  main.cpp
//  minimum-spanning-trees
//
//  Created on 2/24/17.
//

#include <iostream>
#include <time.h>

/*
 * Function generates and returns an adjacency matrix
 * @param n : # of vertices in the matrix
 * @param dim : dimension of the matrix
 */
void matrix_generator(int n, int dim) {
    srand((unsigned)time(NULL));
    int matrix[n][n];
    
    if (dim == 0) {
        // skips the diagonal and copies symmetric value of matrix to other side
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                matrix[i][j] = (double)rand() / RAND_MAX;
                matrix[j][i] = matrix[j][i];
            }
        }
    }
    
    else if (dim == 1) {
        
        int x_coords[n];
        int y_coords[n];
        
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                matrix[i][j] = (double)rand() / RAND_MAX;
                matrix[j][i] = matrix[j][i];
            }
        }
    }
    
    else if (dim == 2) {
        
        int x_coords[n];
        int y_coords[n];
        
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                matrix[i][j] = (double)rand() / RAND_MAX;
                matrix[j][i] = matrix[j][i];
            }
        }
    }
    
    else if (dim == 3) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                matrix[i][j] = (double)rand() / RAND_MAX;
                matrix[j][i] = matrix[j][i];
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    matrix_generator(3, 2);
    return 0;
}
