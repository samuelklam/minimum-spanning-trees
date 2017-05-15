//
//  adjacency_list.hpp
//  minimum-spanning-trees
//
//  Created by Samuel K. Lam on 3/19/17.
//  Copyright © 2017 Samuel K. Lam. All rights reserved.
//

#ifndef adjacency_list_hpp
#define adjacency_list_hpp

#include <stdio.h>
#include <list>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <math.h>

/*
 * Using adjacency list
 */
struct node {
    int index;
    float weight;
};

std::vector<std::list<node>> adj_list(int dim, int n);

#endif /* adjacency_list_hpp */
