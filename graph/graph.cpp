#include "graph.h"
#include <cmath>
#include <sstream>
#include <fstream>
#include <string>
#include "priority_queue/priority_queue.h"

#include <iostream>
#include <map>
#include <stack>
#include "tree.h"
using std::vector;
using std::stack;

template <class T>
void print_vector(vector<T>& v, std::string name) {
	return;
	int counter = 0;
	for (typename std::vector<T>::iterator i = v.begin(); i != v.end(); ++i) {
		std::cout << name << " " << counter << " " <<*i << std::endl;
		counter++;
	}
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

graph::graph(uint vertices): 
	vertex_factory_(new vertex_factory()),
	vertices(vertices),
	deleted_nodes(0),
	vertices_delete_flag(std::vector<bool>(vertices, false)),
	adjacency_list(std::vector<std::vector<weighted_vertex> >(vertices, std::vector<weighted_vertex>())) {
}

graph* graph::construct_from_file(char const* coordinates_file_name, char const* graph_file_name) {
	graph *result = 0;
	std::ifstream coordinates_file(coordinates_file_name);
	std::string str;
	while (getline(coordinates_file, str)) {
		std::string tag = str.substr(0, 1);
		if (tag == "p") {
			uint vertices = 0;
			std::istringstream buffer(split(str, ' ')[4]);
			buffer >> vertices;
			result = new graph(vertices);
		}
		if (tag == "v") {
			int id = 0;
			int x = 0;
			int y = 0;
			std::string temp;
			std::istringstream buffer(str);
			buffer >> temp >> id >> x >> y;
			result->vertex_factory_->register_vertex(new vertex(id - 1, x, y));
		}
	}
	coordinates_file.close();

	std::ifstream graph_file(graph_file_name);
	while (getline(graph_file, str)) {
		std::string tag = str.substr(0, 1);
		if (tag == "a") {
			uint from = 0;
			uint to = 0;
			std::string temp;
			std::istringstream buffer(str);
			buffer >> temp >> from >> to;
			--from;
			--to;
			vertex* from_vertex = result->vertex_factory_->get_vertex(from);
			vertex* to_vertex = result->vertex_factory_->get_vertex(to);
			double distance = sqrt((from_vertex->x-(double)to_vertex->x)*(from_vertex->x-(double)to_vertex->x) + (from_vertex->y-(double)to_vertex->y)*(from_vertex->y-(double)to_vertex->y));
			result->add_edge(from, to, distance);
		}
	}
	graph_file.close();

	return result;
}

void graph::add_edge(uint from, uint to, double weight) {
	vertex* vertex = vertex_factory_->get_vertex(to);
	adjacency_list[from].push_back(weighted_vertex(vertex, weight));
}

void graph::print(std::ostream& output) {
	output << "Graph represenation:" << std::endl;
	for (uint i = 0; i < vertices; ++i) {
		output << i << " adjacency list: ";
		std::vector<weighted_vertex>& adjacent_nodes = get_adjacent_nodes(i);
		for (std::vector<weighted_vertex>::iterator j = adjacent_nodes.begin(); j != adjacent_nodes.end(); ++j) {
			output << "(" << j->vert_->id << "; " <<  j->weight << ") ";			
		}
		output << std::endl;
	}
}

std::vector<weighted_vertex>& graph::get_adjacent_nodes(uint id) {
	return adjacency_list[id];
}

uint graph::vertices_count() {
	return vertices;
}

graph::~graph() {
	delete vertex_factory_;
}

void graph::delete_node(uint id) {
	vertices_delete_flag[id] = true;
	deleted_nodes++;
}

inline double average_of_three(double a, double b, double c) {
	if (a > b) {
		if (c > a) {
			return a;
		} else {
			return fmax(c, b);
		}
	} else {
		if (c > b) {
			return b;
		} else {
			return fmax(c, a);
		}
	}
}

void graph::build_shortest_path_tree(uint from, int epsilon) {
	if (from % 1000 == 0) std::cout << "build_shortest_path_tree " << from << " " << epsilon << std::endl;
	size_t visited_count = 0;

	priority_queue<dijkstra_vertex> queue(&vec);

	dijkstra_vertex from_vertex(vertex_factory_->get_vertex(from), 0);
	queue.push(from_vertex);

	while (!queue.empty()) {
		dijkstra_vertex cur = queue.top();
		queue.pop();

		if (cur.id() != from) {
			if (distance_from_previous_milestone[cur.id()] > epsilon) {
				distance_from_previous_milestone[cur.id()] = 0;
				milestones_passed[cur.id()]++;
			}
		}

		distance[cur.id()] = cur.distance;
		back_reference[cur.id()] = visited_count;
		visited[visited_count] = cur.id();
		visited_count++;

		if (milestones_passed[cur.id()] == 3) {
			continue;
		}

		vector<weighted_vertex>& adjacent = get_adjacent_nodes(cur.id());

		for (vector<weighted_vertex>::iterator i = adjacent.begin(); i != adjacent.end(); ++i) {
			if (vertices_delete_flag[i->vert_->id]) {
				continue;
			}

			if (distance[i->vert_->id] != -1) {
				continue;
			}

			if (vec[i->vert_->id] == 0) {
				dijkstra_vertex temp(i->vert_, i->weight + cur.distance);

				milestones_passed[i->vert_->id] = milestones_passed[cur.id()];
				distance_from_previous_milestone[i->vert_->id] = i->weight + distance_from_previous_milestone[cur.id()];
				previous[i->vert_->id] = cur.id();

				queue.push(temp);
				continue;
			}

			dijkstra_vertex temp = queue.at(vec[i->vert_->id]);

			if (temp.distance > i->weight + cur.distance) {
				temp.update_distance(i->weight + cur.distance);

				milestones_passed[i->vert_->id] = milestones_passed[cur.id()];
				distance_from_previous_milestone[i->vert_->id] = i->weight + distance_from_previous_milestone[cur.id()];
				previous[i->vert_->id] = cur.id();

				queue.change_key(temp);
			}
		}	
	}

	tree dfs_tree(visited_count);

	for (int i = 0; i < visited_count; ++i) {
		uint id = visited[i];
		if (id != from)  {
			dfs_tree.add_edge(back_reference[previous[id]], back_reference[id], distance[id] - distance[previous[id]]);
		}
		dfs_tree.penalties[back_reference[id]] = penalties[id];
	}

	dfs_tree.dfs_height(0, local_height);

	for (int i = 0; i < visited_count; ++i) {
		uint id = visited[i];
		visited[i] = 0;
		reaches[id] = fmax(reaches[id], average_of_three(local_height[back_reference[id]], distance[id] + penalties[from], penalties[id]));
		vec[id] = 0;
		previous[id] = -1;
		milestones_passed[id] = 0;
		distance_from_previous_milestone[id] = 0;
		distance[id] = -1;
		back_reference[id] = 0;
		local_height[i] = -1;
	}
}

void graph::remove_vertices_with_low_reaches(int epsilon) {
	int deleted_count = 0;
	for (size_t i = 0; i < vertices; ++i) {
		if (vertices_delete_flag[i]) {
			continue;
		}

		if (reaches[i] < epsilon) {
			final_reaches[i] = reaches[i];
			std::cout << "Calculated reach of " << i << " : " << reaches[i] << std::endl;
			delete_node(i);
			std::vector<weighted_vertex>& adjacent = get_adjacent_nodes(i);
			for (std::vector<weighted_vertex>::iterator vertex = adjacent.begin(); vertex != adjacent.end(); ++vertex) {
				if (vertices_delete_flag[vertex->vert_->id]) {
					continue;
				}
				penalties[vertex->vert_->id] = fmax(penalties[vertex->vert_->id], reaches[i] + vertex->weight);
			}
			deleted_count++;
		}

		reaches[i] = -1;
	}

	std::cout << "REMOVED nodes with low reach: " << deleted_count << std::endl;
}

void graph::build_reaches() {
	reaches = std::vector<double>(vertices, -1);
	final_reaches = std::vector<double>(vertices, -1);
	penalties = std::vector<double>(vertices, 0);
	back_reference = vector<size_t> (vertices, 0);
	vec = vector<size_t> (vertices, 0);
	visited = vector<uint> (vertices, 0);
	previous = vector<size_t> (vertices, -1);
	milestones_passed = vector<size_t> (vertices, 0);
	distance_from_previous_milestone = vector<double> (vertices, 0);
	distance = vector<double> (vertices, -1);
	local_height = std::vector<double> (vertices, -1);

	int epsilon = 1000;
	while (deleted_nodes != vertices) {
		std::cout << "Epsilon: " << epsilon << std::endl;
		for (size_t i = 0; i < vertices; ++i) {
			if (vertices_delete_flag[i] == false) {
				build_shortest_path_tree(i, epsilon);
			}
		}
		remove_vertices_with_low_reaches(epsilon);
		epsilon *= 3;
	}

	std::cout << "---REACHES---" << std::endl;
	std::cout.precision(15);
	for (int i = 0; i < vertices; ++i) {
		std::cout << final_reaches[i] << std::endl;
	}

	std::cout << "Done" << std::endl;
}

void graph::load_reaches(char const* reaches_file_name) {
	std::ifstream reaches_file(reaches_file_name);
	for (int i = 0; i < vertices; ++i) {
		double reach;
		reaches_file >> reach;
		reaches.push_back(reach);
	}
	reaches_file.close();	
}