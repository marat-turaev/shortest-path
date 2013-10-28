#include "graph/graph.h"

int main() {
	graph* g = graph::construct_from_file("input/USA-road-d.NY.co", "input/USA-road-d.NY.gr");
	g->print(std::cout);
}