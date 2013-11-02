typedef unsigned int uint;
#include <map>

struct vertex {
public:
	vertex(uint id, int x, int y): id(id), x(x), y(y) { }

	uint id; 
	int x; 
	int y;
};

struct dijkstra_vertex {
public:
	dijkstra_vertex(vertex* vertex, double distance) : vertex_(vertex) {
		this->distance = distance;
	}

	uint id() const {
		return vertex_->id;
	}

	void update_distance(double new_distance) {
		if (new_distance < distance) {
			distance = new_distance;
		}
	}

	double distance;
private:
	vertex* vertex_;
};

struct weighted_vertex {
public:
	weighted_vertex(vertex* vert, double weight): weight(weight) { 
		vert_ = vert;
	}

	~weighted_vertex() {
		//TODO: Implement destructor!
		// delete vert_;
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