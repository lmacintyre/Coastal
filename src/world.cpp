#include "terrain.h"
#include "worldparams.h"

class World {
	private:
		Terrain **chunks;

	public:
		World();
		Terrain *get_chunk(int c) {return chunks[c];}
};

World::World() {

	int wh = WORLD_WIDTH*WORLD_HEIGHT;
	chunks = new Terrain*[wh];

	for (int i = 0; i < wh; i++) {
		chunks[i] = new Terrain(i);
	}
	
}
