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
 * Function generates and returns an adjacency matrix
 * @param n : # of vertices in the matrix
 * @param dim : dimension of the matrix
 */
template<int MAX_ROW, int MAX_COL>

void matrix_generator(float (&matrix)[MAX_ROW][MAX_COL], int n, int dim) {
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

///*
// * Prints resulting matrix for debugging and testing purpose
// */
template<int MAX_ROW, int MAX_COL>

void matrix_print(float (&matrix)[MAX_ROW][MAX_COL]) {
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            std::cout << std::setw(10) << std::left << matrix[i][j];
        }
        std::cout << std::endl;
    }
}

int main(int argc, const char * argv[]) {

    int n = 6;
    int d = 3;
    float matrix[6][6];
    
    matrix_generator(matrix, n, d);
    
//    matrix_print(matrix);
    
    return 0;
}
