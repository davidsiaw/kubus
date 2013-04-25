#include "scenariobasedscene.h"


scenariobasedscene::scenariobasedscene(boost::shared_ptr<scenario_interface> scenario)
	: scenario(scenario)
{
}

scenariobasedscene::~scenariobasedscene()
{
}

void scenariobasedscene::init(SDL_Surface* video)
{
	scenario->setresolution(video->w, video->h);
}

void scenariobasedscene::update()
{	
	int keystatelen = 0;
	Uint8* keystate = SDL_GetKeyState(&keystatelen);

	if (keystate[SDLK_LEFT])
	{
		scenario->commandcharacter(scenario->gethero(), LEFT, WALK);
	} 
	else if (keystate[SDLK_RIGHT])
	{
		scenario->commandcharacter(scenario->gethero(), RIGHT, WALK);
	} 
	else if (keystate[SDLK_DOWN])
	{
		scenario->commandcharacter(scenario->gethero(), DOWN, WALK);
	} 
	else if (keystate[SDLK_UP])
	{
		scenario->commandcharacter(scenario->gethero(), UP, WALK);
	} 
	else 
	{
		scenario->commandcharacter(scenario->gethero(), scenario->gethero()->getdirection(), STAND);
	}

	scenario->update();
}

void scenariobasedscene::render()
{
	scenario->render();
}

void scenariobasedscene::cleanup()
{
}

void scenariobasedscene::event(SDL_Event* evt)
{
	if (evt->type == SDL_QUIT)
	{
		exit(0);
	}
}

bool scenariobasedscene::running()
{
	return !scenario->ended();
}
