#include "graph.h"

graph::graph(uint vertices): vertices(vertices) {
	nodes = new node*[10];
}

void graph::add_edge(uint from, uint to, int weight) {
	if (nodes[from] == 0) {
		nodes[from] = new node(to, weight);
	}
	else {
		node* last = nodes[from];
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
		node* cur = nodes[i];
		while (cur != 0) {
			output << "(" << cur->vertex << "; " << cur->weight << ") ";
			cur = cur->next;
		}
		output << std::endl;
	}
}

graph::~graph() {
	delete[] nodes;
	//TODO: memory leak here.
}