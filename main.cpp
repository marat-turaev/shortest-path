#include "graph/graph.h"
#include "a_star/a_star.h"
#include "dijkstra/dijkstra.h"
#include <iostream>
#include <ctime>

int main() {
	graph* g = graph::construct_from_file("input/USA-road-d.NY.co", "input/USA-road-d.NY.gr");
	// graph* g = graph::construct_from_file("input/light.co", "input/light.gr");
	// g->print(std::cout);
	std::cout.precision(15);

	clock_t begin = clock();
	std::cout << dijkstra(g).shortest_path(123, 220000) << std::endl;
	clock_t end = clock();
	std::cout << "Time: " <<(end - begin) / (double)CLOCKS_PER_SEC << std::endl;


	begin = clock();
	std::cout << a_star(g).shortest_path(123, 220000) << std::endl;
	end = clock();
	std::cout << "Time: " << (end - begin) / (double)CLOCKS_PER_SEC << std::endl;
}