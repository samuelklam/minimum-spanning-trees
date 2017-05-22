# Minimum Spanning Trees (MST)

This repo calculates the expected (average) weight of the MST using Prim's algorithm as a function of n (up to 131072) from the following complete, undirected graphs. 

1. Complete graphs on n vertices, where the weight of each edge is a real number chosen uniformly at random on [0, 1]. 
2. Complete graphs on n vertices, where the vertices are points chosen uniformly at random inside the unit square (That is, the points are (x,y), with x and y each a real number chosen uniformly at random from [0, 1].) The weight of an edge is the Euclidean distance between its endpoints. 
3. Complete graphs on n vertices, where the vertices are points chosen uniformly at random inside the unit cube (3 dimensions) and hypercube (4 dimensions). As with the unit square case above, the weight of an edge is just the Euclidean distance between its endpoints.

For a full write-up refer to: `minimum-spanning-tree-writeup.pdf`.

## Usage
In the command line:
```
$ make
$ ./randmst 0 numpoints numtrials dimension
```

The flag 0 can be used for testing, debugging, or extensions. The value `numpoints` is n, the number of points; the value `numtrials` is the number of runs to be done; the value `dimension` gives the dimension.

The output is: `average numpoints numtrials dimension`, where `average` is the average MST weight over the trials.
