#include "tree.h"
#include <cmath>
using std::vector;

tree::tree(uint vertices): vertices(vertices) {
	penalties = std::vector<double>(vertices, 0);
	adjacency_list = std::vector<std::vector<light_weighted_vertex> >(vertices);
	for (size_t i = 0; i < vertices; ++i) {
		adjacency_list[i] = std::vector<light_weighted_vertex>();
	}
}

void tree::add_edge(uint from, uint to, double weight) {
	adjacency_list[from].push_back(light_weighted_vertex(to, weight));
}

void tree::print(std::ostream& output) {
	output << "Tree represenation:" << std::endl;
	for (uint i = 0; i < vertices; ++i) {
		output << i << " adjacency list: ";
		std::vector<light_weighted_vertex> adjacent_nodes = get_adjacent_nodes(i);
		for (std::vector<light_weighted_vertex>::iterator j = adjacent_nodes.begin(); j != adjacent_nodes.end(); ++j) {
			output << "(" << j->id << "; " <<  j->weight << ") ";			
		}
		output << std::endl;
	}
}

double tree::dfs_height(uint from, vector<double>& height) {
	vector<light_weighted_vertex> adjacent = get_adjacent_nodes(from);
	for (vector<light_weighted_vertex>::iterator i = adjacent.begin(); i != adjacent.end(); ++i) {
		height[from] = height[from] == -1
			? i->weight + dfs_height(i->id, height)
			: fmax(i->weight + dfs_height(i->id, height), height[from]);
	}
	return height[from] == -1 ? height[from] = penalties[from] : height[from];
}

std::vector<light_weighted_vertex> tree::get_adjacent_nodes(uint id) {
	return adjacency_list[id];
}