#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "heightmap.h"
#include "renderer.h"

class TerrainRenderer: public Renderer {
	private:
		Heightmap *heightmap;

		float x_step;
		float y_step;

		void draw_triangle(int x, int y, bool fwd);
		void draw_point(int x, int y);
		void set_color(float h);

	public:
		TerrainRenderer(Heightmap *heightmap): heightmap(heightmap) {
			x_step = 2.f / (heightmap->get_width()-1);
			y_step = 2.f / (heightmap->get_height()-1);
		};
		void draw_targets() override;
};

class Terrain {
	private:
		Heightmap *heightmap;
		TerrainRenderer *renderer;
		short chunk_number;
	
	public:
		Terrain();
		Terrain(short chunk_number);
		Heightmap *get_heightmap() {return heightmap;}
		TerrainRenderer *get_renderer() {return renderer;}
};

#endif
