#include "dijkstra.h"

bool operator<(weighted_vertex const& first, weighted_vertex const& second) {
	return first.weight < second.weight;
}

dijkstra::dijkstra(graph *graph1) {

}

int dijkstra::shortest_path(uint from, uint to) {
	std::priority_queue<weighted_vertex, std::vector<weighted_vertex>,std::less<std::vector<weighted_vertex>::value_type> > priority_queue;
	return 0;
}

dijkstra::~dijkstra() {

}
