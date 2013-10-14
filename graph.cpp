#include "graph.h"

graph::graph(uint vertices): vertices(vertices) {
	nodes = new node*[10];
}

void graph::add_edge(uint from, uint to, int weight) {
	if (nodes[from] == 0) {
		nodes[from] = new node(to, weight);
	}
	else {
		node *last = nodes[from];
		while (last->next != 0) {
			last = last->next;
		}
		last->next = new node(to, weight);
	}
}

void graph::print(std::ostream& output) {
	output << "Graph represenation:" << std::endl;
	for (int i = 0; i < vertices; ++i) {
		output << i << " adjacency list: ";
		node *cur = nodes[i];
		while (cur != 0) {
			output << "(" << cur->vertex << "; " << cur->weight << ") ";
			cur = cur->next;
		}
		output << std::endl;
	}
}

graph* graph::construct_from_file(char const *filename) {
	graph* result = 0;
	
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

graph::~graph() {
	for (int i = 0; i < vertices; ++i) {
		delete nodes[i];
	}
	delete[] nodes;
}