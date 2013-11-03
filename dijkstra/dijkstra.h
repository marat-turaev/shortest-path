#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph/graph.h"

struct dijkstra {
public:
	dijkstra(graph* graph);	
	double shortest_path(uint from, uint to);

private:
	graph* graph_;
};

#endif