#include "graph.h"

int main() {
	graph g(4);
	g.add_edge(0, 1, 1);
	g.add_edge(0, 2, 2);
	g.add_edge(1, 0, 1);
	g.add_edge(1, 2, 2);
	g.add_edge(2, 0, 2);
	g.add_edge(2, 1, 1);
	g.add_edge(2, 3, 3);
	g.add_edge(3, 2, 3);
	g.print(std::cout);
}