randmst: main.o adjacency_list.o adjacency-matrix.o d-heap.o
	g++ main.o adjacency_list.o adjacency-matrix.o d-heap.o -o randmst

main.o: main.cpp
	g++ -std=gnu++11 -c main.cpp

adjacency_list.o: adjacency_list.cpp adjacency_list.hpp
	g++ -c adjacency_list.cpp

adjacency-matrix.o: adjacency-matrix.cpp adjacency-matrix.hpp
	g++ -c adjacency-matrix.cpp

d-heap.o: d-heap.cpp d-heap.hpp
	g++ -c d-heap.cpp

clean:
	rm *.o randmst
