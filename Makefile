default: program
main.o: 
	g++ -Wall -c main.cpp -o bin/main.o
graph.o:
	g++ -Wall -c graph/graph.cpp -o bin/graph.o
dijkstra.o:
	g++ -Wall -c dijkstra/dijkstra.cpp -o bin/dijkstra.o
priority_queue.o:
	g++ -Wall -c priority_queue/priority_queue.cpp -o bin/priority_queue.o
vertex.o:
	g++ -Wall -c graph/vertex.cpp -o bin/vertex.o
program: main.o graph.o dijkstra.o vertex.o priority_queue.o
	g++ -Wall bin/priority_queue.o bin/vertex.o bin/main.o bin/graph.o bin/dijkstra.o -o program
clean:
	rm -f bin/*
.PHONY:
	clean