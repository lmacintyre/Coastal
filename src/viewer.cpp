#include "SDL2/SDL.h"
#include "GL/gl.h"

#include "world.h"
#include "terrain.h"

const char* WINDOW_TITLE = "Coastal";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000/SCREEN_FPS;
SDL_Window *window;

SDL_Event event;

World *world;

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
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.f, 1.f, -1.f, 1.f, 2.f, -2.f);
	
	return true;
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	
	glScalef(0.25f, 0.25f, 0.25f);
	glRotatef(45.0, 1.f, 0.f, 0.f);
	glRotatef(a, 0.f, 0.f, 1.f);
	a += 0.5;

	glPushMatrix();
	glTranslatef(-3.f, -3.f, 0.f);
	world->get_chunk(0)->get_renderer()->draw_targets();
	glTranslatef(2.f, 0.f, 0.f);
	world->get_chunk(1)->get_renderer()->draw_targets();
	glTranslatef(2.f, 0.f, 0.f);
	world->get_chunk(2)->get_renderer()->draw_targets();
	glTranslatef(2.f, 0.f, 0.f);
	world->get_chunk(3)->get_renderer()->draw_targets();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.f, -1.f, 0.f);
	world->get_chunk(4)->get_renderer()->draw_targets();
	glTranslatef(2.f, 0.f, 0.f);
	world->get_chunk(5)->get_renderer()->draw_targets();
	glTranslatef(2.f, 0.f, 0.f);
	world->get_chunk(6)->get_renderer()->draw_targets();
	glTranslatef(2.f, 0.f, 0.f);
	world->get_chunk(7)->get_renderer()->draw_targets();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.f, 1.f, 0.f);
	world->get_chunk(8)->get_renderer()->draw_targets();
	glTranslatef(2.f, 0.f, 0.f);
	world->get_chunk(9)->get_renderer()->draw_targets();
	glTranslatef(2.f, 0.f, 0.f);
	world->get_chunk(10)->get_renderer()->draw_targets();
	glTranslatef(2.f, 0.f, 0.f);
	world->get_chunk(11)->get_renderer()->draw_targets();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.f, 3.f, 0.f);
	world->get_chunk(12)->get_renderer()->draw_targets();
	glTranslatef(2.f, 0.f, 0.f);
	world->get_chunk(13)->get_renderer()->draw_targets();
	glTranslatef(2.f, 0.f, 0.f);
	world->get_chunk(14)->get_renderer()->draw_targets();
	glTranslatef(2.f, 0.f, 0.f);
	world->get_chunk(15)->get_renderer()->draw_targets();
	glPopMatrix();

	glColor4f(0.f, 0.3f, 0.8f, 0.5f);
	glBegin(GL_QUADS);
	glVertex3f(-4.f, -4.f, 0.f);
	glVertex3f(-4.f, 4.f, 0.f);
	glVertex3f(4.f, 4.f, 0.f);
	glVertex3f(4.f, -4.f, 0.f);
	glEnd();

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

	world = new World();

	while(!quit) {

		long time_since_last_tick = SDL_GetTicks() - last_tick;
		if (time_since_last_tick < SCREEN_TICKS_PER_FRAME)
				SDL_Delay(SCREEN_TICKS_PER_FRAME - time_since_last_tick);

		render();
		poll_events();
	}

	delete(world);

	return 0;
}
