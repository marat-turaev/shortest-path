typedef unsigned int uint;
#include <map>
#include <algorithm>

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
		distance = std::min(distance, new_distance);
	}

	double distance;
private:
	vertex* vertex_;
};

bool operator<(dijkstra_vertex const& first, dijkstra_vertex const& second);

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
	void register_vertex(vertex* vertex);
	vertex* get_vertex(uint id);
	~vertex_factory();
private:
	std::map<uint, vertex*> data_;
};