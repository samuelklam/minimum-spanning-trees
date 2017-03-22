//
//  adjacency_list.cpp
//  minimum-spanning-trees
//
//  Created by Samuel K. Lam on 3/19/17.
//  Copyright © 2017 Samuel K. Lam. All rights reserved.
//

#include "adjacency_list.hpp"
#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <math.h>

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
