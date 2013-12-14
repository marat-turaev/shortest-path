#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <iostream>
#include "vertex.h"

struct adjacency_list_node {
public:
	adjacency_list_node(vertex* vert, double weight) {
		data = new weighted_vertex(vert, weight);
		next = 0;
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
	graph(graph const & other);
	static graph* construct_from_file(char const* coordinates_file_name, char const* graph_file_name);
	void add_edge(uint from, uint to, double weight);
	void print(std::ostream& output);
	std::vector<weighted_vertex> get_adjacent_nodes(uint id);
	void delete_node(uint id);
	uint vertices_count();    
	void build_reaches();
	void exact_reaches();
	~graph();
	vertex_factory* vertex_factory_;

	void build_shortest_path_tree(uint from, int epsilon);
private:
	graph& operator=(graph& other);
	uint vertices;
	uint deleted_nodes;
	std::vector<bool> vertices_delete_flag;
	adjacency_list_node** adjacency_list;
	bool cloned;

	std::vector<double> reaches;
	std::vector<double> penalties;
	void remove_vertices_with_low_reaches(int epsilon);
	double dfs_height(uint from, std::vector<double>& dist, std::vector<double>& height, std::vector<bool>& was);

	std::vector<size_t> vec;
	std::vector<size_t> previous;
	std::vector<size_t> milestones_passed;
	std::vector<double> distance_from_previous_milestone;
	std::vector<double> dist;
	std::vector<double> height;
	std::vector<bool> was;

	std::vector<size_t> dirty;
};

#endif