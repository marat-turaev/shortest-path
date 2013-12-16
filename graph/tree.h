#ifndef TREE_H
#define TREE_H

#include "vertex.h"
#include <iostream>
#include <vector>

class tree {
public:
	tree(uint vertices);
	void add_edge(uint from, uint to, double weight);
	void print(std::ostream& output);
	std::vector<double> penalties;
	double dfs_height(uint from, std::vector<double>& height);
private:
	std::vector<std::vector<light_weighted_vertex> > adjacency_list;
	std::vector<light_weighted_vertex>& get_adjacent_nodes(uint id);
	uint vertices;
};

#endif