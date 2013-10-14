#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <vector>

typedef unsigned int uint;

struct weighted_vertex {
public:
	weighted_vertex(uint vertex, int weight) {
		this->vertex = vertex;
		this->weight = weight;
	}

	//TODO: incapsulate these two fields
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
	void print(std::ostream& output);
	std::vector<weighted_vertex> get_adjacent_nodes(uint vertex);
	~graph();
private:
	graph(graph& other);
	graph& operator=(graph& other);
	uint vertices;
	adjacency_list_node** adjacency_list;
};

#endif