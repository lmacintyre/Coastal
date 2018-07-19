#include "GL/gl.h"

#include "heightmap.h"
#include "renderer.h"

class TerrainRenderer: public Renderer {
	private:
		Heightmap *heightmap;

		void draw_triangle(int x, int y, bool fwd);
		void draw_point(int x, int y);
		virtual void set_color(float h) = 0;

	public:
		void draw();
};

void max3(float a, float b, float c)
{
	if (a > b) {
		return (a > c) ? a : c;	
	} else {
		return (b > c) ? b : c;
	}
}

void TerrainRenderer::draw_point(int x, int y) {

}

void TerrainRenderer::draw_triangle(int x, int y, bool fwd) {
	if (fwd) {
		set_color(max3(
			heightmap->sample(x,y);
			heightmap->sample(x,y+1);
			heightmap->sample(x+1,y);
		));

		draw_point(x, y);
		draw_point(x, y+1);
		draw_point(x+1, y);
	} else {
		set_color(max3(
			heightmap->sample(x,y);
			heightmap->sample(x+1,y);
			heightmap->sample(x+1,y-1);
		));

		draw_point(x, y);
		draw_point(x+1, y);
		draw_point(x+1, y-1);
	}
}

class IslandRenderer: public TerrainRenderer {
	private:
		void set_color(float h);
};

void TerrainRenderer::draw() {
	for (int i=0; i<heightmap->get_width-1(); i++) {
		for (int j=0; j<heightmap->get_height()-1; j++) {
			draw_triangle(i,j,true);
		}
	}
	
	for (int i=0; i<heightmap->get_width()-1; i++) {
		for (int j=1; j<heightmap->get_height(); j++) {
			draw_triangle(i,j,false);
		}
	}
}

class IslandRenderer: public TerrainRenderer() {

}
 
class Terrain {
	private:
		Heightmap *heightmap;
		TerrainRenderer *renderer;
	
	public:
		Heightmap *get_heightmap() {return heightmap;}
		TerrainRenderer *get_renderer() {return renderer;}
};
