#include "graph/graph.h"
#include "dijkstra/dijkstra.h"

int main() {
	graph* g = graph::construct_from_file("input/USA-road-d.NY.co", "input/USA-road-d.NY.gr");
	// graph* g = graph::construct_from_file("input/light.co", "input/light.gr");
	// g->print(std::cout);
	std::cout.precision(15);
	std::cout<<dijkstra(g).shortest_path(1, 50000)<<std::endl;
}