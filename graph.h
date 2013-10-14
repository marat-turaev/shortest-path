#pragma once

#include <iostream>
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
	~graph();
private:
	uint vertices;
	node** nodes;
};