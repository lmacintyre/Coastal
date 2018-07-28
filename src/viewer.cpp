#include "SDL2/SDL.h"
#include "GL/gl.h"

const char* WINDOW_TITLE = "Coastal";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
SDL_Window *window;

SDL_Event event;

bool quit = false;

bool init_SDL() {
	
	if (! (window = SDL_CreateWindow(
			WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
			WINDOW_HEIGHT, SDL_WINDOW_OPENGL))) {
			
			fprintf(stderr, "SDL failed to create window.");
			return false;
	}

	return true;
}

bool init_GL() {
	
	if (!SDL_GL_CreateContext(window)) {
		fprintf(stderr, "Could not create OpenGL context.");
		return false;
	}

	
	return true;
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapWindow(window);
}

void poll_events() {
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
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

	while(!quit) {
		render();
		poll_events();
		SDL_Delay(100);
	}

	return 0;
}
