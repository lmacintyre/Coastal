#ifndef __HEIGHTMAP_H__
#define __HEIGHTMAP_H__

#include <iostream>
#include <stdlib.h>
#include <time.h>

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
		Heightmap(int w, int h): width(w), height(h) {
			int wh = w*h;
			values = new float[wh];

			for (int i=0; i<wh; i++) 
				values[i] = 0.f;
		};

		int get_width() {return width;}
		int get_height() {return height;}

		float sample(int x, int y);
		void put(int x, int y, float v);
};

#endif
