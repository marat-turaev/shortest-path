#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <vector>
#include "vertex.h"

struct adjacency_list_node {
public:
	adjacency_list_node(vertex* vert, double weight) {
		data = new weighted_vertex(vert, weight);
	}

	~adjacency_list_node() {
		delete data;
	}

	adjacency_list_node* next;
	weighted_vertex *data;
private:
	adjacency_list_node(adjacency_list_node& other);
	adjacency_list_node& operator=(adjacency_list_node& other);
};

class graph {
public:
	graph(uint vertices);
	static graph* construct_from_file(char const *filename);
	void add_edge(uint from, uint to, int weight);
	// void print(std::ostream& output);
	// std::vector<weighted_vertex> get_adjacent_nodes(uint vertex);
	~graph();
private:
	graph(graph& other);
	graph& operator=(graph& other);
	uint vertices;
	adjacency_list_node** adjacency_list;
};

#endif