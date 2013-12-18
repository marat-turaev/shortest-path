#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph/graph.h"
#include "boost/optional.hpp"
using std::vector;

struct dijkstra {
public:
	dijkstra(graph* graph);	
	double shortest_path(uint from, uint to, vector<boost::optional<uint> >& previous);
	double shortest_path_with_reaches(uint from, uint to, vector<boost::optional<uint> >& previous);

private:
	graph* graph_;
};

#endif