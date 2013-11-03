#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph/graph.h"
using std::vector;

struct dijkstra {
public:
	dijkstra(graph* graph);	
	double shortest_path(uint from, uint to, vector<uint>& previous);

private:
	graph* graph_;
};

#endif