CC=g++
CFLAGS=-c -Wall -g
INC=-I. 
all: program
default: program
main.o: 
	$(CC) $(CFLAGS) $(INC) main.cpp -o bin/main.o
graph.o:
	$(CC) $(CFLAGS) $(INC) graph/graph.cpp -o bin/graph.o
dijkstra.o:
	$(CC) $(CFLAGS) $(INC) dijkstra/dijkstra.cpp -o bin/dijkstra.o
a_star.o:
	$(CC) $(CFLAGS) $(INC) a_star/a_star.cpp -o bin/a_star.o
priority_queue.o:
	$(CC) $(CFLAGS) $(INC) priority_queue/priority_queue.cpp -o bin/priority_queue.o
vertex.o:
	$(CC) $(CFLAGS) $(INC) graph/vertex.cpp -o bin/vertex.o
program: main.o graph.o vertex.o priority_queue.o dijkstra.o a_star.o
	g++ bin/priority_queue.o bin/vertex.o bin/main.o bin/graph.o bin/a_star.o bin/dijkstra.o -o program
clean:
	rm -f bin/*
.PHONY:
	clean