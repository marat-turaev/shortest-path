#include "a_star.h"
#include "../priority_queue/priority_queue.h"
#include <cmath>
#include <iostream>

a_star::a_star(graph* graph): graph_(graph) { }

double a_star::heuristic(vertex* current, vertex* destination) {
	return sqrt((current->x-(double)destination->x) * (current->x-(double)destination->x) + (current->y-(double)destination->y) * (current->y-(double)destination->y));
}

double a_star::shortest_path(uint from, uint to) {
	vertex* to_vertex = graph_->vertex_factory_->get_vertex(to);
	std::vector<size_t> vec(graph_->vertices_count(), 0);
	std::vector<size_t> prev(graph_->vertices_count(), 0);
	std::vector<char> visited(graph_->vertices_count(), 0);
	std::vector<double> dist(graph_->vertices_count(), 0);

	priority_queue<dijkstra_vertex> queue(&vec);

	dijkstra_vertex from_vertex(graph_->vertex_factory_->get_vertex(from), 0);
	queue.push(from_vertex);
	dist[from] = 0;
	
	while (!queue.empty()) {
		dijkstra_vertex cur = queue.top();
		queue.pop();
		visited[cur.id()] = 1;

		if (cur.id() == to) {
			int j = to;
			while (prev[j] != from) {
				std::cout << j << " ";
				j = prev[j];
			}
			std::cout << from << std::endl;
			return dist[to];
		}

		std::vector<weighted_vertex> adjacent = graph_->get_adjacent_nodes(cur.id());
		for (std::vector<weighted_vertex>::iterator i = adjacent.begin(); i != adjacent.end(); ++i) {
			if (visited[i->vert_->id] == 1) {
				continue;
			}

			if (vec[i->vert_->id] == 0) {
				dist[i->vert_->id] = dist[cur.id()] + i->weight;
				prev[i->vert_->id] = cur.id();
				dijkstra_vertex temp(i->vert_, i->weight + dist[cur.id()] + heuristic(i->vert_, to_vertex));
				queue.push(temp);
				continue;
			}

			dijkstra_vertex temp = queue.at(vec[i->vert_->id]);

			if (dist[cur.id()] + i->weight < dist[i->vert_->id]) {
				dist[i->vert_->id] = dist[cur.id()] + i->weight;
				prev[i->vert_->id] = cur.id();
				temp.update_distance(i->weight + dist[cur.id()] + heuristic(i->vert_, to_vertex));
				queue.change_key(temp);
			}
		}
	}

	return -1;

}