default: program
main.o: 
	g++ -c main.cpp -o bin/main.o
graph.o:
	g++ -c graph/graph.cpp -o bin/graph.o
dijkstra.o:
	g++ -c dijkstra/dijkstra.cpp -o bin/dijkstra.o
program: main.o graph.o dijkstra.o
	g++ bin/main.o bin/graph.o bin/dijkstra.o -o bin/program
clean:
	rm -rf bin/
.PHONY:
	clean