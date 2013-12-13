#include "graph.h"
#include <cmath>
#include <sstream>
#include <fstream>
#include <string>
#include "priority_queue/priority_queue.h"

#include <iostream>
#include <stack>
using std::vector;
using std::stack;

template <class T>
void print_vector(vector<T> v, std::string name) {
	return;
	int counter = 0;
	for (typename std::vector<T>::iterator i = v.begin(); i != v.end(); ++i) {
		std::cout << name << " " << counter << " " <<*i << std::endl;
		counter++;
	}
}

template <class T>
void print_vector2(vector<T> v, std::string name) {
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


graph::graph(uint vertices): vertices(vertices) {
	reaches = std::vector<double>(vertices, -1);
	penalties = std::vector<double>(vertices, 0);
	deleted_nodes = 0;
	cloned = false;
	vertex_factory_ = new vertex_factory();
	adjacency_list = new adjacency_list_node*[vertices];
	for (int i = 0; i < vertices; ++i) {
		adjacency_list[i] = 0;
	}
	vertices_delete_flag = std::vector<bool>(vertices, false);
}

graph::graph(graph const & other) {
	reaches = std::vector<double>(vertices, -1);
	penalties = std::vector<double>(vertices, 0);
	deleted_nodes = 0;
	printf("%s\n", "copied!");
	cloned = true;
	//vertex_factory and adjacency_list intentionally left shared due to author's lazyness
	vertex_factory_ = other.vertex_factory_;
	adjacency_list = other.adjacency_list;
	vertices = other.vertices;
	vertices_delete_flag = std::vector<bool>(vertices, false);
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

	if (adjacency_list[from] == 0) {
		adjacency_list[from] = new adjacency_list_node(vertex, weight);
	}
	else {
		adjacency_list_node* last = adjacency_list[from];
		while (last->next != 0) {
			last = last->next;
		}
		last->next = new adjacency_list_node(vertex, weight);
	}
}

void graph::print(std::ostream& output) {
	output << "Graph represenation:" << std::endl;
	for (uint i = 0; i < vertices; ++i) {
		output << i << " adjacency list: ";
		std::vector<weighted_vertex> adjacent_nodes = get_adjacent_nodes(i);
		for (std::vector<weighted_vertex>::iterator j = adjacent_nodes.begin(); j != adjacent_nodes.end(); ++j) {
			output << "(" << j->vert_->id << "; " <<  j->weight << ") ";			
		}
		output << std::endl;
	}
}

std::vector<weighted_vertex> graph::get_adjacent_nodes(uint id) {
	std::vector<weighted_vertex> vec;
	adjacency_list_node* node = adjacency_list[id];
	while (node != 0) {
		if (vertices_delete_flag[node->data->vert_->id] == false) {
			vec.push_back(*(node->data));
		}
		node = node->next;
	}
	return vec;
}

uint graph::vertices_count() {
	return vertices;
}

graph::~graph() {
	if (cloned) {
		return;
	}

	for (int i = 0; i < vertices; ++i) {
		delete adjacency_list[i];
	}
	delete[] adjacency_list;
	delete vertex_factory_;
}

void graph::delete_node(uint id) {
	vertices_delete_flag[id] = true;
	deleted_nodes++;
}

void graph::build_shortest_path_tree(uint from, int epsilon) {
	vector<uint> visited;
	vector<size_t> vec(vertices, 0);
	vector<size_t> previous(vertices, -1);
	vector<size_t> milestones_passed(vertices, 0);
	vector<double> distance_from_previous_milestone(vertices, 0);
	vector<double> dist(vertices, -1);
	vector<double> height(vertices, -1);
	vector<bool> was(vertices, 0);

	priority_queue<dijkstra_vertex> queue(&vec);

	dijkstra_vertex from_vertex(vertex_factory_->get_vertex(from), penalties[from]);
	distance_from_previous_milestone[from] = penalties[from];
	queue.push(from_vertex);

	while (!queue.empty()) {
		dijkstra_vertex cur = queue.top();
		queue.pop();

		if (milestones_passed[cur.id()] == 0 ) {
			if (distance_from_previous_milestone[cur.id()] > epsilon) {
				distance_from_previous_milestone[cur.id()] = 0;
				milestones_passed[cur.id()]++;
			}
		}

		if (milestones_passed[cur.id()] == 1 ) {
			if (distance_from_previous_milestone[cur.id()] + penalties[cur.id()] > epsilon) {
				distance_from_previous_milestone[cur.id()] = 0;
				milestones_passed[cur.id()]++;
			}
		}

		dist[cur.id()] = cur.distance;
		visited.push_back(cur.id());

		if (milestones_passed[cur.id()] == 2) {
			continue;
		}

		vector<weighted_vertex> adjacent = get_adjacent_nodes(cur.id());

		for (vector<weighted_vertex>::iterator i = adjacent.begin(); i != adjacent.end(); ++i) {
			if (dist[i->vert_->id] != -1) {
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

	print_vector(visited, "visited");
	print_vector(dist, "dist");
	print_vector(milestones_passed, "milestones_passed");
	print_vector(distance_from_previous_milestone, "distance_from_previous_milestone");

	// dfs over min-path tree to calculate reaches

	dfs_height(from, dist, height, was);

	print_vector(height, "height");

	for (std::vector<uint>::iterator i = visited.begin(); i != visited.end(); ++i) {
		reaches[*i] = fmax(reaches[*i], fmin(height[*i], dist[*i]));
	}

	print_vector(reaches, "reaches");
}

//TODO: visit only tree's edges
double graph::dfs_height(uint from, vector<double>& dist, vector<double>& height, vector<bool>& was) {
	was[from] = true;
	vector<weighted_vertex> adjacent = get_adjacent_nodes(from);
	for (vector<weighted_vertex>::iterator i = adjacent.begin(); i != adjacent.end(); ++i) {
		if (was[i->vert_->id] || dist[i->vert_->id] == -1) {
			continue;
		}

		height[from] = height[from] == -1 ? i->weight + dfs_height(i->vert_->id, dist, height, was) : fmax(i->weight + dfs_height(i->vert_->id, dist, height, was), height[from]);
	}
	return height[from] == -1 ? height[from] = penalties[from] : height[from];
}

void graph::remove_vertices_with_low_reaches(int epsilon) {
	int deleted_count = 0;
	for (size_t i = 0; i < vertices; ++i) {
		if (vertices_delete_flag[i]) {
			continue;
		}

		if (reaches[i] < epsilon) {
			std::cout << "Final reach of " << i << " : " << reaches[i] << std::endl;
			delete_node(i);
			std::vector<weighted_vertex> adjacent = get_adjacent_nodes(i);
			for (std::vector<weighted_vertex>::iterator vertex = adjacent.begin(); vertex != adjacent.end(); ++vertex) {
				penalties[vertex->vert_->id] += reaches[i] + vertex->weight;
			}
			deleted_count++;
		}

		reaches[i] = -1;
	}
	print_vector2(penalties, "penalties");
	std::cout << "removed nodes with low reach: " << deleted_count << std::endl;
}

void graph::exact_reaches() {
	int epsilon = 100;

	for (int i = 0; i < vertices; ++i) {
		build_shortest_path_tree(i, epsilon);
	}

	for (int i = 0; i < vertices; ++i) {
		std::cout << "Final reach of " << i << " : " << reaches[i] << std::endl;
	}

	std::cout << "Done" << std::endl;
}

void graph::build_reaches() {
	int epsilon = 1;

	while (deleted_nodes != vertices) {
		std::cout << "Epsilon: " << epsilon << std::endl;
		for (int i = 0; i < vertices; ++i) {
			build_shortest_path_tree(i, epsilon);
		}
		remove_vertices_with_low_reaches(epsilon);
		epsilon *= 3;
	}

	std::cout << "Done" << std::endl;
}