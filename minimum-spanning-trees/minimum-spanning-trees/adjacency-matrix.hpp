//
//  adjacency-matrix.hpp
//  minimum-spanning-trees
//
//  Created by Samuel K. Lam on 2/26/17.
//  Copyright © 2017 Samuel K. Lam. All rights reserved.
//

#ifndef adjacency_matrix_hpp
#define adjacency_matrix_hpp

#include <stdio.h>

template<int MAX_ROW, int MAX_COL>
void MatrixGenerator(float (&matrix)[MAX_ROW][MAX_COL], int n, int dim);

template<int MAX_ROW, int MAX_COL>
void MatrixPrint(float (&matrix)[MAX_ROW][MAX_COL]);

#endif /* adjacency_matrix_hpp */
