#include "dijkstra.h"
#include "priority_queue/priority_queue.h"
#include <iostream>

dijkstra::dijkstra(graph* graph): graph_(graph) { }

double dijkstra::shortest_path(uint from, uint to, vector<boost::optional<uint> >& previous) {
	vector<size_t> vec(graph_->vertices_count(), 0);
	vector<double> dist(graph_->vertices_count(), -1);

	priority_queue<dijkstra_vertex> queue(&vec);

	dijkstra_vertex from_vertex(graph_->vertex_factory_->get_vertex(from), 0);
	queue.push(from_vertex);

	while (!queue.empty()) {
		dijkstra_vertex cur = queue.top();
		queue.pop();
		dist[cur.id()] = cur.distance;

		if (cur.id() == to) {
			return cur.distance;
		}

		vector<weighted_vertex> adjacent = graph_->get_adjacent_nodes(cur.id());

		for (vector<weighted_vertex>::iterator i = adjacent.begin(); i != adjacent.end(); ++i) {
			if (dist[i->vert_->id] != -1) {
				continue;
			}

			if (vec[i->vert_->id] == 0) {
				dijkstra_vertex temp(i->vert_, i->weight + cur.distance);
				previous[i->vert_->id] = cur.id();
				queue.push(temp);
				continue;
			}

			dijkstra_vertex temp = queue.at(vec[i->vert_->id]);

			if (temp.distance > i->weight + cur.distance) {
				temp.update_distance(i->weight + cur.distance);
				previous[i->vert_->id] = cur.id();
				queue.change_key(temp);
			}
		}	
	}

	return -1;
}