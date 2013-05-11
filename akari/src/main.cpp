#include <stdio.h>
#include <stdlib.h>
#include <sdl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <GL/glew.h>
#include <boost/shared_ptr.hpp>
#include "akari.h"

#include "scene_interface.h"

#include "tilemapscene.h"

#include "scenario_interface.h"
#include "scenariobasedscene.h"

#include <map>
#include "btileset.h"
#include "directoryresources.h"


const char* title = "Dark Flame Master";
int screenWidth = 800;
int screenHeight = 600;
SDL_Surface* screen;
Uint32 currtime = 0;

void run(boost::shared_ptr<scene_interface> scene)
{
	currtime = SDL_GetTicks();
	scene->init(screen);
	
    SDL_Event evt;
    while(scene->running())
    {
        if(SDL_PollEvent(&evt))
        {
			scene->event(&evt);
        }

        scene->update();
		
		Uint32 now = SDL_GetTicks();
		if (now - currtime > 15) {

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			scene->render();
			SDL_GL_SwapBuffers();
			currtime = SDL_GetTicks();
		}
	}

	scene->cleanup();
}

int initialize()
{
	log("Initializing SDL\n");
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {	
		log("SDL_Init: %s\n", SDL_GetError());
		return EXIT_FAILURE;
    }
	
	log("Initializing SDL_TTF\n");
	if(TTF_Init() == -1) {
		log("TTF_Init: %s\n", TTF_GetError());
		return EXIT_FAILURE;
	}
	
	log("Initializing Video\n");
    if((screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL )) == NULL)
    {
		log("SDL_Init: %s\n", SDL_GetError());
		return EXIT_FAILURE;
    }

	SDL_WM_SetCaption(title, NULL);
	
	log("Initializing Glew\n");
    glewInit();
	Init3D(screenWidth, screenHeight);

    return EXIT_SUCCESS;
}

class mymapdesc : public mapdesc_interface
{
public:
	virtual std::string gettilesetname()
	{
		return "rmxpnew";
	}

	virtual tileid getid(int x, int y)
	{
		tileid id;
		id.id =  (unsigned int)( (unsigned int)x / 12 +  (unsigned int)y / 12) % 2;
		return id;
	}
};

class controller_interface 
{

};

class myscenario : public scenario_interface
{

	boost::shared_ptr<ordinarytexanimshader> shader;
	boost::shared_ptr<font_interface> font;
	boost::shared_ptr<tilemaplayer> tilelayer;

	boost::shared_ptr<objectset_interface> objectset;

	boost::shared_ptr<textlayer> campos;
	boost::shared_ptr<objectlayer> objects;

	boost::shared_ptr<mobilecharacter> playerobject;

	boost::shared_ptr<mobilecharacter> addobject(int id)
	{
		auto anotherobject = objectset->createobject(id);
		objects->addobject(anotherobject);
		return anotherobject;
	}

public:
	myscenario(
			boost::shared_ptr<resources_interface> resources, 
			boost::shared_ptr<mapdesc_interface> mapdesc, 
			boost::shared_ptr<font_interface> font,
			boost::shared_ptr<objectset_interface> charmap) :
			
		shader(new ordinarytexanimshader()), 
		font(font),
		tilelayer(new tilemaplayer(shader, resources, mapdesc,800,600)),
		campos(new textlayer(shader, resources, font)),
		objectset(charmap),
		objects(new objectlayer(shader, resources, objectset, 800, 600))
	{
		playerobject = addobject(4);

		auto anotherobject = addobject(1);
		anotherobject->setlocation(400,50);
		anotherobject->setdirection(DOWN);
		objects->updateobject(anotherobject);
	}

	virtual void setresolution(int width, int height)
	{
	}

	virtual boost::shared_ptr<mobilecharacter> gethero()
	{
		return playerobject;
	}

	virtual void update()
	{
		tilelayer->setcamera(-playerobject->getx(), -playerobject->gety());
	}

	void updatefps()
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

	virtual void render()
	{
		updatefps();

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

	virtual bool ended() const
	{
		return false;
	}

	virtual void commandcharacter(boost::shared_ptr<mobilecharacter> character, objectdirection dir, characteraction act)
	{
		if ((SDL_GetTicks() - character->getlastupdated()) < 30)
		{
			return;
		}
		character->setlastupdated(SDL_GetTicks());
		int dx=0;
		int dy=0;
		const int walkspeed = 2;

		if (act == WALK)
		{
			switch(dir)
			{
			case LEFT:
				dx = -walkspeed;
				break;
			case RIGHT:
				dx = +walkspeed;
				break;
			case UP:
				dy = -walkspeed;
				break;
			case DOWN:
				dy = +walkspeed;
				break;
			}
		}

		if (dx != 0 || dy != 0)
		{
			int newx = character->getx() + dx;
			int newy = character->gety() + dy;
			objects->foreachobject([&](boost::shared_ptr<object_interface> obj) -> bool
			{
				mobilecharacter* o = (mobilecharacter*)obj.get();
				int distx = newx - o->getx();
				int disty = newy - o->gety();
				if (o != character.get() && distx*distx+disty*disty < 1024)
				{
					newx = character->getx();
					newy = character->gety();
					return false;
				}
				return true;
			});

			character->setlocation(newx, newy);
		}

		character->setaction(act);
		character->setdirection(dir);
		objects->updateobject(character);
	}
};

int main(int argc, char* argv[])
{
	if (initialize() != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	boost::shared_ptr<directoryresources> dirres(new directoryresources("../res/"));
	boost::shared_ptr<mapdesc_interface> mapd(new mymapdesc());
	boost::shared_ptr<font_interface> font = dirres->getfont("myfont");
	boost::shared_ptr<objectset_interface> charmap = dirres->getcharmap("maincm");

	boost::shared_ptr<scenario_interface> scenario(new myscenario(dirres, mapd, font, charmap));
	boost::shared_ptr<scenariobasedscene> scene(new scenariobasedscene(scenario));
	run(scene);


	boost::shared_ptr<tilemapscene> tms(new tilemapscene(dirres, mapd, font));
	run(tms);

	return EXIT_SUCCESS;
}
