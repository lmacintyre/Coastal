#include "SDL2/SDL.h"

const char* WINDOW_TITLE = "Coastal";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
SDL_Window *window;

SDL_Event event;

bool init_SDL() {
	window = SDL_CreateWindow(
			WINDOW_TITLE,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			SDL_WINDOW_OPENGL);
	
	if (!window) {
			fprintf(stderr, "SDL failed to create window.");
			return false;
	}

	return true;
}

bool init_GL() {
	return true;
}

int main(int argc, char* argv[]) {
	
	if (!init_SDL()) {
		fprintf(stderr, "SDL failed to initialize. Exiting...");
		return 1;
	}

	SDL_Delay(1000);

	return 0;
}
