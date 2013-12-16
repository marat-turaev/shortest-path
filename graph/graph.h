#ifndef GRAPH_H
#define GRAPH_H

#include "vertex.h"
#include <vector>
#include <iostream>

class graph {
public:
	graph(uint vertices);
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
	std::vector<std::vector<weighted_vertex> > adjacency_list;

	std::vector<double> reaches;
	std::vector<double> final_reaches;
	std::vector<double> penalties;
	void remove_vertices_with_low_reaches(int epsilon);
	double dfs_height(uint from, std::vector<double>& height);

	std::vector<size_t> back_reference;
	std::vector<size_t> vec;
	std::vector<size_t> previous;
	std::vector<size_t> milestones_passed;
	std::vector<double> distance_from_previous_milestone;
	std::vector<double> dist;
	std::vector<uint> visited;

	std::vector<size_t> dirty;
};

#endif