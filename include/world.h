#ifndef __WORLD_H__
#define __WORLD_H__

#include "terrain.h"

class World {
	private:
		Terrain **chunks;

	public:
		World();
		Terrain *get_chunk(int c) {return chunks[c];}
};

#endif
