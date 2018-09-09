#include "SDL2/SDL.h"

#include "heightmap.h"

#define RAND_MAX_HALF RAND_MAX / 2

float randf() {
	return -1.f + static_cast<float> (rand()) / (static_cast<float> (RAND_MAX_HALF));
}

void square_step(Heightmap *heightmap, int x, int y, int step_size, float value) {

	int hs = step_size / 2;

	double a = heightmap->sample(x - hs, y - hs);
	double b = heightmap->sample(x - hs, y + hs);
	double c = heightmap->sample(x + hs, y + hs);
	double d = heightmap->sample(x + hs, y - hs);

	heightmap->put(x, y, ((a+b+c+d)/4.f) + value);
}

void diamond_step(Heightmap *heightmap, int x, int y, int step_size, float value) {
	
	int hs = step_size / 2;

	double a = heightmap->sample(x - hs, y);
	double b = heightmap->sample(x + hs, y);
	double c = heightmap->sample(x, y - hs);
	double d = heightmap->sample(x, y + hs);

	heightmap->put(x, y, ((a+b+c+d)/4.f) + value);
}

void square_diamond(Heightmap *heightmap, int stepsize, float scale) {
	
	int width = heightmap->get_width();
	int height = heightmap->get_height();

	// Clear map
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			heightmap->put(i, j, 0.f);


	// Seed map
	srand(SDL_GetTicks());
	for (int i = 0; i < width; i += stepsize)
		for (int j = 0; j < height; j += stepsize)
			heightmap->put(i, j, randf());

	// Generate terrain
	while (stepsize > 1) {
		int halfstep = stepsize / 2;

		for (int y = halfstep; y < height + halfstep; y += stepsize) {
			for (int x = halfstep; x < width + halfstep; x += stepsize) {
				square_step(heightmap, x, y, stepsize, randf() * scale);
			}
		}

		for (int y = 0; y < height; y += stepsize) {
			for (int x = 0; x < width; x += stepsize) {
				diamond_step(heightmap, x + halfstep, y, stepsize, randf() * scale);
				diamond_step(heightmap, x, y + halfstep, stepsize, randf() * scale);
			}
		}

		stepsize /= 2;
		scale /= 2.f;
	}
}
