SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: tan root

tan:
	g++ -c lagr_tan_graph.cpp 
	g++ lagr_tan_graph.o -o tan $(SFML_FLAGS)

root:
	g++ -c lagr_root_graph.cpp 
	g++ lagr_root_graph.o -o root $(SFML_FLAGS)

clean:
	rm lagr_root_graph.o lagr_tan_graph.o tan root 