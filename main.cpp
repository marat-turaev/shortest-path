#include "graph/graph.h"
#include <queue>

int main() {
	graph *g = graph::construct_from_file("input.txt");
	g->print(std::cout);

	std::priority_queue<weighted_vertex, std::vector<weighted_vertex>,std::less<std::vector<weighted_vertex>::value_type> > pq;
}