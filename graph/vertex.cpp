#include "vertex.h"

void vertex_factory::register_vertex(vertex *vertex) {
	data_[vertex->id] = vertex;
}

vertex* vertex_factory::get_vertex(uint id) {
	return data_[id];
}