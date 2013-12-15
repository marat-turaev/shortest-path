#include "graph/graph.h"
#include "a_star/a_star.h"
#include "dijkstra/dijkstra.h"
#include <iostream>
#include <fstream>
#include <ctime>

const uint from = 123;
const uint to = 2200000;

void print_path(std::vector<boost::optional<uint> >& v) {
	std::ofstream vertices("vertices.txt");
	for (size_t i = 0; i < v.size(); ++i) {
		if (v[i]) {
			vertices << i << std::endl;
		}
	}
	
	std::ofstream path("path.txt");
	int j = to;
	while (v[j] != from) {
		path << j << " " << *(v[j]) << std::endl;
		j = *v[j];
	}
	path << j << " " << from;
}

int main() {
	graph* g = graph::construct_from_file("input/USA-road-d.NY.mid.co", "input/USA-road-d.NY.mid.gr");
	// graph* g = graph::construct_from_file("input/USA-road-d.NY.small.co", "input/USA-road-d.NY.small.gr");
	// graph* g = graph::construct_from_file("input/mesh.co", "input/mesh.gr");
	// graph* g = graph::construct_from_file("input/circle.co", "input/circle.gr");
	// graph* g = graph::construct_from_file("input/ultralight.co", "input/ultralight.gr");
	// graph* g = graph::construct_from_file("input/light.co", "input/light.gr");
	// graph* g = graph::construct_from_file("input/USA-road-d.NY.co", "input/USA-road-d.NY.gr");
	// g->build_shortest_path_tree(0, 1);
	// g->exact_reaches();
	g->build_reaches();
	return 0;
}

void test() {
	graph* g = graph::construct_from_file("input/USA-road-d.USA.co", "input/USA-road-d.USA.gr");
	// graph* g = graph::construct_from_file("input/light.co", "input/light.gr");
	// g->print(std::cout);
	std::cout.precision(15);

	// vector<boost::optional<uint> > previous1(g->vertices_count(), boost::optional<uint>());
	clock_t begin = clock();
	// std::cout << dijkstra(g).shortest_path(from, to, previous1) << std::endl;
	clock_t end = clock();
	// std::cout << "Time: " <<(end - begin) / (double)CLOCKS_PER_SEC << std::endl;

	// print_path(previous1);

	vector<boost::optional<uint> > previous2(g->vertices_count(), boost::optional<uint>());
	begin = clock();
	std::cout << a_star(g).shortest_path(from, to, previous2) << std::endl;
	end = clock();
	std::cout << "Time: " << (end - begin) / (double)CLOCKS_PER_SEC << std::endl;

	print_path(previous2);
}