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
#include <time.h>
#include <fstream>
#include "d-heap.hpp"

clock_t start, end;

/*
 * Prim's algorithm
 * @param *x_coords : pointer to x_coordinate array (denotes 1D)
 * @param *y_coords : pointer to y_coordinate array (denotes 2D)
 * @param *z_coords : pointer to z_coordinate array (denotes 3D)
 * @param *v_coords : pointer to v_coordinate array (denotes 4D)
 * @param n : # of vertexes in the graph
 * @param dim : dimension to calculate
 * @return sum : the sum of the weight of the MST
 */
float Prim(float *x_coords, float *y_coords, float *z_coords, float *v_coords, int n, int dim) {
    float dist[n];
    int prev[n];

    Node v = {-1, -1};

    float sum = 0;

    // we compute the optimal children value for the d-ary heap as well
    int optimal_value = n/8;
    if (n == 131072) {
        optimal_value = n/16;
    }
    DHeap min_heap(n, optimal_value);

    int vertices[n];

    for (int i = 1; i < n; i++) {

        // initialize all the vertices to not visited
        vertices[i] = 0;

        // note that this value should be sufficiently large since the max distance (for hypercube) is less than this
        dist[i] = 10000;
    }

    // we will start Prim's from the 0th vertex
    vertices[0] = 1;
    dist[0] = 0;

    min_heap.Insert(0, dist[0]);

    float largest_edge = -10.0;

    while (!min_heap.IsEmpty()) {

        v = min_heap.DeleteMin(v);

        if(dist[v.v] > largest_edge)
            largest_edge = dist[v.v];

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

/*
 * Helper function to run Prim's for a given number of trials and dimensions
 * @param n : number of vertexes in the graph
 * @param trials : # of trials to run Prim's
 * @param dim : dimension to run Prim's at
 * @return : average sum of the MSTs
 */
float run_prims(int n, int trials, int dim) {
    srand((unsigned)time(NULL));
    float sum = 0.0;
    for (int i = 0; i < trials; i++) {
        if (dim == 0) {
            // no use to store coordinates, can compute on the fly
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

            // initialize 2D coordinates
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

            // initialize 3D coordinates
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

            // initialize 4D coordinates
            for (int a = 0; a < n; a++) {
                x_coords[a] = (float)rand() / RAND_MAX;
                y_coords[a] = (float)rand() / RAND_MAX;
                z_coords[a] = (float)rand() / RAND_MAX;
                v_coords[a] = (float)rand() / RAND_MAX;
            }

            sum += Prim(x_coords, y_coords, z_coords, v_coords, n, dim);
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

    // dimensions for the problem
    int dim = atoi(argv[4]);

    float sum = run_prims(n, trials, dim);
    std::cout << sum / trials << " " << n << " " << trials << " " << dim << std::endl;

    return 0;
}

