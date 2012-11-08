#include <string>
#include <vector>

#include "boost/shared_ptr.hpp"
#include "boost/shared_array.hpp"
#include "textlayer.h"
#include "tilemapscene.h"

tilemapscene::tilemapscene(boost::shared_ptr<resources_interface> resources, boost::shared_ptr<mapdesc_interface> mapdesc, boost::shared_ptr<font_interface> font)
	: shader(new ordinarytexanimshader()), 
	font(font),
	tilelayer(new tilemaplayer(shader, resources, mapdesc,800,600)),
	campos(new textlayer(shader, resources, font)),
	objectset(new mobilecharacterset()),
	objects(new objectlayer(shader, resources, objectset, 800, 600)),
	playerobject(objectset->createobject(1)),
	otherobject(objectset->createobject(1))
{
	objects->addobject(playerobject);
	objects->addobject(otherobject);
}

tilemapscene::~tilemapscene()
{
}

void tilemapscene::init(SDL_Surface* video)
{
}

void tilemapscene::update()
{
	int keystatelen = 0;
	Uint8* keystate = SDL_GetKeyState(&keystatelen);
	int speed = 2;

	otherobject->setlocation(50,50);
	objects->updateobject(otherobject);

	int dx=0;
	int dy=0;
	playerobject->setaction(WALK);
	if (keystate[SDLK_LEFT])
	{
		playerobject->setdirection(LEFT);
		dx = -speed;
	} 
	else if (keystate[SDLK_RIGHT])
	{
		playerobject->setdirection(RIGHT);
		dx = +speed;
	} 
	else if (keystate[SDLK_DOWN])
	{
		playerobject->setdirection(DOWN);
		dy = +speed;
	} 
	else if (keystate[SDLK_UP])
	{
		playerobject->setdirection(UP);
		dy = -speed;
	} 
	else 
	{
		playerobject->setaction(STAND);
	}

	playerobject->setlocation(playerobject->getx()+dx, playerobject->gety()+dy);
	objects->updateobject(playerobject);
	tilelayer->setcamera(-playerobject->getx(), -playerobject->gety());
	


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

void tilemapscene::render()
{
	static int a = 0;
	glLoadIdentity();

	tilelayer->render((a/15)%4);
	
	objects->setcamera(tilelayer->getx(), tilelayer->gety());
	objects->render((a/15)%4);

	glEnable2D(50,50);
	campos->render(1.0);

	glDisable2D();
	a++;
}

void tilemapscene::cleanup()
{
}

void tilemapscene::event(SDL_Event* evt)
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

bool tilemapscene::running()
{
	return true;
}
