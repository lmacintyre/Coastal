#include <iostream>

#include "GL/gl.h"

#include "renderer.h"
#include "heightmap.h"

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

float max3(float a, float b, float c)
{
	if (a > b) {
		return (a > c) ? a : c;	
	} else {
		return (b > c) ? b : c;
	}
}

void TerrainRenderer::draw_point(int x, int y) {

	float X = -1 + x_step*x;
	float Y = -1 + y_step*y;
	float Z = heightmap->sample(x,y);

	glVertex3f(X, Y, Z);
}

void TerrainRenderer::draw_triangle(int x, int y, bool fwd) {

	if (fwd) {
		set_color(max3(
			heightmap->sample(x,y),
			heightmap->sample(x,y+1),
			heightmap->sample(x+1,y)
		));
		
		draw_point(x, y);
		draw_point(x, y+1);
		draw_point(x+1, y);
	} else {
		set_color(max3(
			heightmap->sample(x,y),
			heightmap->sample(x+1,y),
			heightmap->sample(x+1,y-1)
		));

		draw_point(x, y);
		draw_point(x+1, y);
		draw_point(x+1, y-1);
	}
}

void TerrainRenderer::draw_targets() {

	glBegin(GL_TRIANGLES);

	for (int i=0; i<heightmap->get_width()-1; i++) {
		for (int j=0; j<heightmap->get_height()-1; j++) {
			draw_triangle(i,j,true);
		}
	}
	
	for (int i=0; i<heightmap->get_width()-1; i++) {
		for (int j=1; j<heightmap->get_height(); j++) {
			draw_triangle(i,j,false);
		}
	}
	glEnd();
}

void TerrainRenderer::set_color(float h) {

	glColor3f(h, h, h);
}
 
class Terrain {
	private:
		Heightmap *heightmap;
		TerrainRenderer *renderer;
	
	public:
		Terrain();

		Heightmap *get_heightmap() {return heightmap;}
		TerrainRenderer *get_renderer() {return renderer;}
};

Terrain::Terrain(){
	heightmap = new Heightmap(129, 129);
	renderer = new TerrainRenderer(heightmap);
}
