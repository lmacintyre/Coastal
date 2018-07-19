#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <vector>

class Drawable {};

class Renderer {

	private:
		std::vector<Drawable*> targets;

	public:
		virtual void draw_targets() = 0;
		std::vector<Drawable*> get_targets();
};

#endif
