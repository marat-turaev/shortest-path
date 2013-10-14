default: program
main.o: main.cpp
	g++ -c main.cpp -o main.o
graph.o: graph.cpp
	g++ -c graph.cpp -o graph.o
program: main.o graph.o
	g++ main.o graph.o -o program
clean:
	rm -rf *.o *.s program
.PHONY:
	clean