#include <iostream>
typedef unsigned int uint;

class graph {
public:
	graph(unsigned int vertices);
	void add_edge(uint from, uint to, int weight);
	void print(std::ostream& output);
	~graph();
private:
	/* data */
};

struct node {
public:
	int vertex;
	node* next;
};