#include "graph.h"

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
	adjacency_list = new adjacency_list_node*[vertices];
	for (int i = 0; i < vertices; ++i) {
		adjacency_list[i] = 0;
	}
}

graph* graph::construct_from_file(char const* coordinates_file_name, char const* graph_file_name) {
	graph *result = 0;
	std::ifstream coordinates_file(coordinates_file_name);
	std::string str;
	while (getline(coordinates_file, str)) {
		std::string tag = str.substr(0, 1);
		if (tag == "v") {
			int id = 0;
			int x = 0;
			int y = 0;
			std::string temp;
			std::istringstream buffer(str);
			buffer >> temp >> id >> x >> y;
			vertex_factory::register_vertex(new vertex(id - 1, x, y));
		}
	}
	coordinates_file.close();

	std::ifstream graph_file(graph_file_name);
	while (getline(graph_file, str)) {
		std::string tag = str.substr(0, 1);
		if (tag == "p") {
			uint vertices = 0;
			std::istringstream buffer(split(str, ' ')[2]);
			buffer >> vertices;
			result = new graph(vertices);
		}
		if (tag == "a") {
			uint from = 0;
			uint to = 0;
			std::string temp;
			std::istringstream buffer(str);
			buffer >> temp >> from >> to;
			--from;
			--to;
			vertex* from_vertex = vertex_factory::get_vertex(from);
			vertex* to_vertex = vertex_factory::get_vertex(to);
			double distance = sqrt((from_vertex->x-(double)to_vertex->x)*(from_vertex->x-(double)to_vertex->x) + (from_vertex->y-(double)to_vertex->y)*(from_vertex->y-(double)to_vertex->y));
			result->add_edge(from, to, distance);
		}
	}
	graph_file.close();

	return result;
}

void graph::add_edge(uint from, uint to, double weight) {
	vertex* vertex = vertex_factory::get_vertex(to);

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
	for (int i = 0; i < vertices; ++i) {
		output << i << " adjacency list: ";
		adjacency_list_node *cur = adjacency_list[i];
		while (cur != 0) {
			output << "(" << cur->data->vert_->id << "; " << cur->data->weight << ") ";
			cur = cur->next;
		}
		output << std::endl;
	}
}

std::vector<weighted_vertex> graph::get_adjacent_nodes(uint id) {
	std::vector<weighted_vertex> vec;
	adjacency_list_node* node = adjacency_list[id];
	while (node != 0) {
		vec.push_back(*(node->data));
		node = node->next;
	}
	return vec;
}

uint graph::vertices_count() {
	return vertices;
}

graph::~graph() {
	for (int i = 0; i < vertices; ++i) {
		delete adjacency_list[i];
	}
	delete[] adjacency_list;
}