#include "graph.h"

weighted_vertex::weighted_vertex(uint vertex, int weight) {
	this->vertex = vertex;
	this->weight = weight;
}

graph::graph(uint vertices): vertices(vertices) {
	adjacency_list = new adjacency_list_node*[10];
}

graph* graph::construct_from_file(char const *filename) {
	graph *result = 0;
	
	std::ifstream file(filename);
	if (file.is_open()) {
		uint vertices;
		file >> vertices;
		result = new graph(vertices);
		while (!file.eof()) {
			uint from, to;
			int weight;
			file >> from >> to >> weight;
			result->add_edge(from, to, weight);
		}
		file.close();
	}
	
	return result;
}

void graph::add_edge(uint from, uint to, int weight) {
	if (adjacency_list[from] == 0) {
		adjacency_list[from] = new adjacency_list_node(to, weight);
	}
	else {
		adjacency_list_node *last = adjacency_list[from];
		while (last->next != 0) {
			last = last->next;
		}
		last->next = new adjacency_list_node(to, weight);
	}
}

void graph::print(std::ostream& output) {
	output << "Graph represenation:" << std::endl;
	for (int i = 0; i < vertices; ++i) {
		output << i << " adjacency list: ";
		adjacency_list_node *cur = adjacency_list[i];
		while (cur != 0) {
			output << "(" << cur->data->vertex << "; " << cur->data->weight << ") ";
			cur = cur->next;
		}
		output << std::endl;
	}
}

std::vector<weighted_vertex>* graph::get_adjacent_nodes(uint vertex) {
	// std::vector<weighted_vertex> *v = new std::vector<weighted_vertex>();
	return 0;
}

graph::~graph() {
	for (int i = 0; i < vertices; ++i) {
		delete adjacency_list[i];
	}
	delete[] adjacency_list;
}