#ifndef A_STAR_H
#define A_STAR_H

#include "graph/graph.h"
using std::vector;

struct a_star {
public:
	a_star(graph* graph);	
	double shortest_path(uint from, uint to, vector<uint>& previous);

private:
	double heuristic(vertex* current, vertex* destination);
	graph* graph_;
};

#endif