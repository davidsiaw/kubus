#include <string>
#include <vector>

#include <boost/tr1/memory.hpp>
#include "boost/shared_array.hpp"
#include "textlayer.h"
#include "tilemapeditorscene.h"

tilemapeditorscene::tilemapeditorscene(std::tr1::shared_ptr<resources_interface> resources, std::tr1::shared_ptr<mapdesc_interface> mapdesc, std::tr1::shared_ptr<font_interface> font)
	: shader(new ordinarytexanimshader()), 
	font(font),
	tilelayer(new tilemaplayer(shader, resources, mapdesc,800,600)),
	campos(new textlayer(shader, resources, font))
{
}

tilemapeditorscene::~tilemapeditorscene()
{
}

void tilemapeditorscene::init(SDL_Surface* video)
{
}


void tilemapeditorscene::update()
{
	const int mult = 10;
	static float start = SDL_GetTicks();
	static int ticks = 0;
	static float fps = 0;

	char msg[128];
	sprintf(msg, "x=%d_y=%d_fps=%f", tilelayer->getx(), tilelayer->gety(), fps);

	if (ticks % mult == 0)
	{
		fps = mult * 1000.0f/(SDL_GetTicks() - start);
		start = SDL_GetTicks();
	}

	ticks++;

	campos->settext(msg);
}

void tilemapeditorscene::render()
{
	static int a = 0;
	glLoadIdentity();

	tilelayer->render((a/20)%4);
	
	glEnable2D(50,50);
	campos->render(1.0);
	glDisable2D();
	
	a++;
}

void tilemapeditorscene::cleanup()
{
}

void tilemapeditorscene::event(SDL_Event* evt)
{
	if (evt->type == SDL_MOUSEMOTION)
	{
		if(evt->motion.state & SDL_BUTTON_LMASK)
		{
			tilelayer->setcamera(
				tilelayer->getx() + evt->motion.xrel, 
				tilelayer->gety() + evt->motion.yrel);

			
		}
	}
}

bool tilemapeditorscene::running()
{
	return true;
}
