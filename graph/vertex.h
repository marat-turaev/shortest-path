typedef unsigned int uint;
#include <map>

struct vertex {
public:
	vertex(uint id, int x, int y): id(id), x(x), y(y) { }

	uint id; 
	int x; 
	int y;
};

struct weighted_vertex {
public:
	weighted_vertex(vertex* vert, double weight): weight(weight) { 
		vert_ = vert;
	}

	vertex* vert_;
	double weight;
};

struct vertex_factory {
public:
	static void register_vertex(vertex* vertex);
	static vertex* get_vertex(uint id);
private:
	static std::map<uint, vertex*> data_;
};