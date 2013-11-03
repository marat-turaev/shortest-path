CC=g++
CFLAGS=-c -Wall -g
all: program
default: program
main.o: 
	$(CC) $(CFLAGS) main.cpp -o bin/main.o
graph.o:
	$(CC) $(CFLAGS) graph/graph.cpp -o bin/graph.o
dijkstra.o:
	$(CC) $(CFLAGS) dijkstra/dijkstra.cpp -o bin/dijkstra.o
a_star.o:
	$(CC) $(CFLAGS) a_star/a_star.cpp -o bin/a_star.o
priority_queue.o:
	$(CC) $(CFLAGS) priority_queue/priority_queue.cpp -o bin/priority_queue.o
vertex.o:
	$(CC) $(CFLAGS) graph/vertex.cpp -o bin/vertex.o
program: main.o graph.o vertex.o priority_queue.o dijkstra.o a_star.o
	g++ bin/priority_queue.o bin/vertex.o bin/main.o bin/graph.o bin/a_star.o bin/dijkstra.o -o program
clean:
	rm -f bin/*
.PHONY:
	clean