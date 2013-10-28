#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../graph/graph.h"

struct dijkstra_vertex {
public:
	dijkstra_vertex(vertex* vertex, double distance) : vertex_(vertex) {
		this->distance = distance;
	}

	uint id() {
		return vertex_->id;
	}

	double distance;
private:
	vertex* vertex_;
};

struct dijkstra {
public:
	dijkstra(graph* graph);	
	int shortest_path(uint from, uint to);

private:
	graph* graph_;
};

#endif