#pragma once
#include "../graph/graph.h"
#include <queue>

class dijkstra {
public:
	dijkstra(graph *graph1);	
	int shortest_path(uint from, uint to);
	~dijkstra();
private:
	graph* graph1;
};