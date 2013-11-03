#include "vertex.h"

void vertex_factory::register_vertex(vertex *vertex) {
	data_[vertex->id] = vertex;
}

vertex* vertex_factory::get_vertex(uint id) {
	return data_[id];
}

vertex_factory::~vertex_factory() {
	for (std::map<uint, vertex*>::iterator it=data_.begin(); it!=data_.end(); ++it) {
		delete it->second;
	}
}

bool operator<(dijkstra_vertex const& first, dijkstra_vertex const& second) {
	return first.distance < second.distance;
}