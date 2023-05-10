# Interval graph recognition algorithm

According to Derek G. Corneil, Stephan Olariu and Lorna Stewart an independent set of three vertices is called an asteroidal triple if between every two vertices in the triple there exists a path avoiding the neighbourhood of the third. A graph is asteroidal triple-free (AT-free, for short) if it contains no asteroidal triple. A classic result states that a graph is an interval graph if and only if it is chordal and AT-free.

Our main contribution is to exhibit a very simple, lineartime, [recognition algorithm for interval graphs](https://citeseerx.ist.psu.edu/document?repid=rep1&type=pdf&doi=fc49a11c5c752e83c29aa804fb75d7b9dbc3f88c) involving four sweeps of the we&known Lexicographic Breadth First Search. Unlike the vast majority of existing algorithms, we do not use maximal cliques in our algorithm - we rely, instead, on a less well-known characterization by a linear order of the vertices.

You can see in the repository 3 files.
- Graph_diagram.png
- Graph_input.txt
- interval_graph_recognition_algorithm.c

The 1st one is just an image how our diagram looks like.

The 2nd file is the conversion of the diagram into a format readable by the program that we implemented.
On the 1st line we have the number of the vertices. On the 2nd line we have the number of the edges. Finally on the other lines we have the connections between the vertices.
So, in our example we have 6 vertices, 10 edges and 10 more rows in the txt file for the connections.

The 3rd file is the code in C. The only think that you have to do is to compile this file (gcc) and run the executable. On the execution we pass all the arguments through our keyboard.
