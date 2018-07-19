#ifndef __HEIGHTMAP_H__
#define __HEIGHTMAP_H__

/**
 *	Heightmap:
 *	A class used to model a field of points representing terrain.
 *
 *	Author:
 *	Liam MacIntyre
 *	liam.macintyre@gmail.com
 */
class Heightmap {

	private:
		const int width;
		const int height;

		float *values;

	public:
		Heightmap(int w, int h): width(w), height(h) {}

		int get_width() {return width;}
		int get_height() {return height;}

		float sample(int x, int y);
		void put(int x, int y, float v);
};

#endif
