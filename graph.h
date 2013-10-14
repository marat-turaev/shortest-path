#pragma once

#include <iostream>
#include <fstream>

typedef unsigned int uint;

struct node {
public:
	node(uint vertex, int weight): vertex(vertex), weight(weight), next(0) {}
	uint vertex;
	int weight;
	node* next;
};

class graph {
public:
	graph(uint vertices);
	void add_edge(uint from, uint to, int weight);
	void print(std::ostream& output);
	static graph* construct_from_file(char const *filename);
	~graph();
private:
	uint vertices;
	node** nodes;
};