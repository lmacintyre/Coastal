
CC = g++
FLAGS = -I include
LINKS = -lSDL2 -lGL

heightmap.o: src/heightmap.cpp include/heightmap.h
	$(CC) $(FLAGS) $(LINKS) -c -o bin/heightmap.o src/heightmap.cpp

renderer.o: src/renderer.cpp include/renderer.h
	$(CC) $(FLAGS) $(LINKS) -c -o bin/renderer.o src/renderer.cpp

viewer.o: src/viewer.cpp
	$(CC) $(FLAGS) $(LINKS) -c -o bin/viewer.o src/viewer.cpp

terrain.o: src/terrain.cpp include/terrain.h
	$(CC) $(FLAGS) $(LINKS) -c -o bin/terrain.o src/terrain.cpp

all: heightmap.o renderer.o terrain.o viewer.o
	$(CC) $(LINKS) -o bin/Coastal bin/*.o

