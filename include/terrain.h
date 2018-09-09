#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "heightmap.h"
#include "renderer.h"

class TerrainRenderer: public Renderer {
	private:
		Heightmap *heightmap;

		void draw_triangle(int x, int y, bool fwd);
		void draw_point(int x, int y);
		void set_color(float h);

		float x_step;
		float y_step;

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
	
	public:
		Terrain();
		Heightmap *get_heightmap() {return heightmap;}
		TerrainRenderer *get_renderer() {return renderer;}
};

void square_diamond(Heightmap*);

#endif
