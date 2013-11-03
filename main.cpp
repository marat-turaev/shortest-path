#include "graph/graph.h"
#include "a_star/a_star.h"
#include "dijkstra/dijkstra.h"
#include <iostream>
#include <ctime>

const uint from = 123;
const uint to = 220000;

void print_path(std::vector<uint>& v) {
	int j = to;
	while (v[j] != from) {
		std::cout << j << " ";
		j = v[j];
	}
	std::cout << from << std::endl;
}

int main() {
	graph* g = graph::construct_from_file("input/USA-road-d.NY.co", "input/USA-road-d.NY.gr");
	// graph* g = graph::construct_from_file("input/light.co", "input/light.gr");
	// g->print(std::cout);
	std::cout.precision(15);

	vector<uint> previous1(g->vertices_count(), 0);
	clock_t begin = clock();
	std::cout << dijkstra(g).shortest_path(from, to, previous1) << std::endl;
	clock_t end = clock();
	std::cout << "Time: " <<(end - begin) / (double)CLOCKS_PER_SEC << std::endl;

	print_path(previous1);

	vector<uint> previous2(g->vertices_count(), 0);
	begin = clock();
	std::cout << a_star(g).shortest_path(from, to, previous2) << std::endl;
	end = clock();
	std::cout << "Time: " << (end - begin) / (double)CLOCKS_PER_SEC << std::endl;

	print_path(previous2);
}