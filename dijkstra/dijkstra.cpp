#include "dijkstra.h"
#include "../priority_queue/priority_queue.h"
#include <climits>

bool operator<(dijkstra_vertex const& first, dijkstra_vertex const& second) {
	return first.distance < second.distance;
}

dijkstra::dijkstra(graph* graph): graph_(graph) { }

int dijkstra::shortest_path(uint from, uint to) {
	std::vector<size_t> vec;
	priority_queue<dijkstra_vertex> queue(&vec);

	dijkstra_vertex from_vertex(vertex_factory::get_vertex(from), 0);

	for (int i = 0; i < graph_->vertices_count(); ++i) {
		dijkstra_vertex d_vertex(vertex_factory::get_vertex(i), LONG_MAX);
		if (i == from) {
			d_vertex.distance = 0;
		}
		queue.push(d_vertex);
	}

	while (!queue.empty()) {
		dijkstra_vertex cur = queue.top();
		if (cur.id() == to) {
			return cur.distance;
		}

		std::vector<weighted_vertex> adjacent = graph_->get_adjacent_nodes(cur.id());

		for (std::vector<weighted_vertex>::iterator i = adjacent.begin(); i != adjacent.end(); ++i) {
			if (queue.at(i->vert_->id).distance > i->weight + cur.distance) {
				dijkstra_vertex temp = queue.at(i->vert_->id);
				temp.distance = i->weight + cur.distance;
				queue.change_key(temp.id(), temp);
			}
		}
	}
	return 0;
}

