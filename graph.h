#pragma once

#include <iostream>
#include <fstream>

typedef unsigned int uint;

struct weighted_vertex {
public:
	weighted_vertex(uint vertex, int weight) {
		this->vertex = vertex;
		this->weight = weight;
	}
	uint vertex;
	int weight;
};

struct adjacency_list_node {
public:
	adjacency_list_node(uint vertex, int weight) {
		data = new weighted_vertex(vertex, weight);
	}

	~adjacency_list_node() {
		delete data;
	}
	
	uint vertex;
	adjacency_list_node* next;
	weighted_vertex *data;
};

class graph {
public:
	graph(uint vertices);
	static graph* construct_from_file(char const *filename);
	void add_edge(uint from, uint to, int weight);
	void print(std::ostream& output);
	adjacency_list_node* get_adjacent_nodes(uint vertex);
	~graph();
private:
	uint vertices;
	adjacency_list_node** adjacency_list;
};