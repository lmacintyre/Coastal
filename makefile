
CC = g++
FLAGS = -I include
LINKS = -lnoise -lGL -lSDL2 

heightmap.o: src/heightmap.cpp include/heightmap.h
	$(CC) $(FLAGS) $(LINKS) -c -o bin/heightmap.o src/heightmap.cpp

renderer.o: src/renderer.cpp include/renderer.h
	$(CC) $(FLAGS) $(LINKS) -c -o bin/renderer.o src/renderer.cpp

viewer.o: src/viewer.cpp include/worldparams.h
	$(CC) $(FLAGS) $(LINKS) -c -o bin/viewer.o src/viewer.cpp

terrain.o: src/terrain.cpp include/terrain.h include/worldparams.h
	$(CC) $(FLAGS) $(LINKS) -c -o bin/terrain.o src/terrain.cpp

squarediamond.o: src/squarediamond.cpp include/squarediamond.h include/worldparams.h
	$(CC) $(FLAGS) $(LINKS) -c -o bin/squarediamond.o src/squarediamond.cpp

world.o: src/world.cpp include/world.h include/worldparams.h
	$(CC) $(FLAGS) $(LINKS) -c -o bin/world.o src/world.cpp

all: heightmap.o renderer.o terrain.o viewer.o squarediamond.o world.o
	$(CC) -o bin/Coastal bin/*.o $(LINKS)

