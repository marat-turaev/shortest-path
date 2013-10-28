typedef unsigned int uint;

struct vertex {
public:
	vertex(uint id, int x, int y): id(id), x(x), y(y) { }

	//TODO: incapsulate these fields
	uint id; 
	int x; 
	int y;
};

struct weighted_vertex {
public:
	weighted_vertex(vertex* vert, double weight) { 
		vert_ = vert;
	}

	vertex* vert_;
};

