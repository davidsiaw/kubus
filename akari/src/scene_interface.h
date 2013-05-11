#ifndef SCENE_INTERFACE
#define SCENE_INTERFACE

#include <SDL.h>

class scene_interface
{
public:
	virtual void init(SDL_Surface* video)=0;
	virtual void update()=0;
	virtual void render()=0;
	virtual void cleanup()=0;
	virtual void event(SDL_Event* evt)=0;
	virtual bool running()=0;
};

#endif // SCENE_INTERFACE
