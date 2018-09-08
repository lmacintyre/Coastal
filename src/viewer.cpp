#include "SDL2/SDL.h"
#include "GL/gl.h"

#include "terrain.h"

const char* WINDOW_TITLE = "Coastal";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000/SCREEN_FPS;
SDL_Window *window;

SDL_Event event;

Terrain *terrain;

bool quit = false;
long last_tick;

float a = 0.f;

bool init_SDL() {
	
	if (! (window = SDL_CreateWindow(
			WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
			WINDOW_HEIGHT, SDL_WINDOW_OPENGL))) {
			
			fprintf(stderr, "SDL failed to create window.");
			return false;
	}

	last_tick = SDL_GetTicks();

	return true;
}

bool init_GL() {
	
	if (!SDL_GL_CreateContext(window)) {
		fprintf(stderr, "Could not create OpenGL context.");
		return false;
	}

	glClearColor(0x00, 0x00, 0x00, 0x00);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.f, 1.f, 1.f, -1.f, -1.f, 1.f);
	
	return true;
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	
	glScalef(0.5f, 0.5f, 0.5f);
	glRotatef(45, 1.f, 0.f, 1.f);

	terrain->get_renderer()->draw_targets();

	glPopMatrix();
	SDL_GL_SwapWindow(window);
}

void poll_events() {
	while (SDL_PollEvent(&event)) {
		switch (event.type) {

		case SDL_QUIT:
			quit = true;
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				
			case SDLK_ESCAPE:
				quit = true;
				break;

			} break;
		}
	}
}

int main(int argc, char* argv[]) {
	
	if (!init_SDL()) {
		fprintf(stderr, "SDL failed to initialize. Exiting...");
		return 1;
	}

	if (!init_GL()) {
		fprintf(stderr, "OpenGL failed to initialize. Exiting...");
		return 2;
	}

	terrain = new Terrain();

	while(!quit) {

		long time_since_last_tick = SDL_GetTicks() - last_tick;
		if (time_since_last_tick < SCREEN_TICKS_PER_FRAME)
				SDL_Delay(SCREEN_TICKS_PER_FRAME - time_since_last_tick);

		render();
		poll_events();
	}

	delete(terrain);

	return 0;
}
