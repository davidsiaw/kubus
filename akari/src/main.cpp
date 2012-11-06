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

#include <map>
#include "btileset.h"
#include "directoryresources.h"

#include <cmath>

const char* title = "Dark Flame Master";
int screenWidth = 800;
int screenHeight = 600;
SDL_Surface* screen;

void run(boost::shared_ptr<scene_interface> scene)
{
	scene->init(screen);
	
    SDL_Event evt;
    while(scene->running())
    {
        if(SDL_PollEvent(&evt))
        {
			scene->event(&evt);
        }

        scene->update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene->render();
		SDL_GL_SwapBuffers();
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


int main(int argc, char* argv[])
{
	if (initialize() != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	boost::shared_ptr<directoryresources> dirres(new directoryresources("D:/gcc/akari/res/"));
	boost::shared_ptr<mapdesc_interface> mapd(new mymapdesc());
	boost::shared_ptr<font_interface> font = dirres->getfont("myfont");

	boost::shared_ptr<tilemapscene> tms(new tilemapscene(dirres, mapd, font));
	run(tms);

	return EXIT_SUCCESS;
}
