from graph_tool.all import *
# filename = "USA-road-d.NY.mid"
filename = "USA-road-d.NY.small"
# filename = "mesh"
# filename = "circle"
# filename = "light"
# filename = "USA-road-d.NY"
# filename = "USA-road-d.USA"

vertices_count = 0
vertices = []

print "Vertices processing"
g = Graph(directed=False)
with open('../input/' + filename + ".co", 'r') as f:
    for line in f:
        words = line.split()
        if line[0] == 'p':
            vertices_count = int(words[-1])
            pos = g.new_vertex_property("vector<double>")
            vertices_color = g.new_vertex_property("vector<double>")
            edge_color = g.new_edge_property("vector<double>")
            pen = g.new_edge_property("double")
        if line[0] == 'v':
            vertices.append(g.add_vertex())
            current_vertice = g.vertex(int(words[1]) - 1)
            pos[current_vertice] = (int(words[2]), int(words[3]))
            vertices_color[current_vertice] = [0.5, 0, 0, 1];

with open('../vertices.txt', 'r') as f:
    for line in f:
        current_vertice = g.vertex(int(line))
        vertices_color[current_vertice] = [0, 1, 0, 1]

print "Edges processing"
with open('../input/' + filename + ".gr", 'r') as f:
    for line in f:
        words = line.split()
        if line[0] == 'a':
            from_ = int(words[1]) - 1
            to_ = int(words[2]) - 1
            if g.edge(vertices[from_], vertices[to_]): continue;
            current_edge = g.add_edge(vertices[from_], vertices[to_])
            pen[current_edge] = 1
            edge_color[current_edge] = [0.179, 0.203,0.210, 0.8]


with open('../path.txt', 'r') as f:
    for line in f:
        words = line.split()
        current_edge = g.edge(int(words[0]), int(words[1]))
        pen[current_edge] = 10
        edge_color[current_edge] = [0, 0, 1, 1]


print "Drawing processing"
graph_draw(g, pos=pos, edge_color = edge_color, edge_pen_width = pen, vertex_fill_color=vertices_color, output="out.png", output_size=(4000,4000))
print "Done"