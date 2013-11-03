#include "vertex.h"

std::map<uint, vertex*> vertex_factory::data_;

void vertex_factory::register_vertex(vertex *vertex) {
	data_[vertex->id] = vertex;
}

vertex* vertex_factory::get_vertex(uint id) {
	return data_[id];
}

bool operator<(dijkstra_vertex const& first, dijkstra_vertex const& second) {
	return first.distance < second.distance;
}