default: program
main.o: 
	g++ -Wall -c main.cpp -o bin/main.o
graph.o:
	g++ -Wall -c graph/graph.cpp -o bin/graph.o
dijkstra.o:
	g++ -Wall -c dijkstra/dijkstra.cpp -o bin/dijkstra.o
program: main.o graph.o dijkstra.o
	g++ -Wall bin/main.o bin/graph.o bin/dijkstra.o -o bin/program
clean:
	rm -f bin/*
.PHONY:
	clean