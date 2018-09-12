#include <iostream>

#include "SDL2/SDL.h"
#include "noise/noise.h"

#include "heightmap.h"
#include "worldparams.h"

#define RAND_MAX_HALF RAND_MAX / 2

float randf() {
	return -1.f + static_cast<float> (rand()) / (static_cast<float> (RAND_MAX_HALF));
}

void square_step(Heightmap *heightmap, int x, int y, int step_size, float value) {

	int hs = step_size / 2;

	double a = heightmap->sample(x, y);
	double b = heightmap->sample(x + hs, y);
	double c = heightmap->sample(x + hs, y + hs);
	double d = heightmap->sample(x, y + hs);

	heightmap->put(x + (step_size/2), y + (step_size/2), ((a+b+c+d)/4.f) + value);
}

void diamond_step(Heightmap *heightmap, int x, int y, int step_size, float value) {
	
	int hs = step_size / 2;

	double a = heightmap->sample(x - hs, y);
	double b = heightmap->sample(x + hs, y);
	double c = heightmap->sample(x, y - hs);
	double d = heightmap->sample(x, y + hs);

	heightmap->put(x, y, ((a+b+c+d)/4.f) + value);
}

float get_noise(noise::module::Perlin p, int x, int y, int c) {
	float nx = c % (WORLD_WIDTH) + static_cast<float> (x) / (CHUNK_SIZE-1);
	float ny = c / (WORLD_WIDTH) + static_cast<float> (y) / (CHUNK_SIZE-1);

	return p.GetValue(nx, ny, 0.f);
}

void square_diamond(Heightmap *heightmap, int chunk, int stepsize, float scale) {
	
	noise::module::Perlin noise;

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
			heightmap->put(i, j, get_noise(noise, i, j, chunk));

	// Generate terrain
	
	while (stepsize > 1) {
		int halfstep = stepsize / 2;

		for (int y = 0; y < height-1; y += stepsize) {
			for (int x = 0; x < width-1; x += stepsize) {
				square_step(heightmap, x, y, stepsize,
							   get_noise(noise, x, y, chunk) * scale);
			}
		}

		for (int x = 0; y < width-1; x += halfstep) {
			for (int y = (x + halfstep)%stepsize; x < width-1; x += stepsize) {
				diamond_step(heightmap, x + halfstep, y, stepsize,
							   get_noise(noise, x, y, chunk) * scale);
				diamond_step(heightmap, x, y + halfstep, stepsize,
							   get_noise(noise, x, y, chunk) * scale);
			}
		}

		stepsize /= 2;
		scale /= 2.f;
	}
	
}
