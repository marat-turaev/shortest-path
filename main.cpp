#include "graph/graph.h"

int main() {
	graph *g = graph::construct_from_file("input.txt");
	g->print(std::cout);
	
	std::vector<weighted_vertex> vec = g->get_adjacent_nodes(1);
	for (std::vector<weighted_vertex>::iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << it->vertex << std::endl;
}