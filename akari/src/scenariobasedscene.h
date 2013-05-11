#ifndef SCENARIOBASEDSCENE_H
#define SCENARIOBASEDSCENE_H

#include <boost/shared_ptr.hpp>

#include "scene_interface.h"
#include "scenario_interface.h"

class scenariobasedscene : public scene_interface
{
	boost::shared_ptr<scenario_interface> scenario;

public:
	scenariobasedscene(boost::shared_ptr<scenario_interface> scenario);
	~scenariobasedscene();
	virtual void init(SDL_Surface* video);
	virtual void update();
	virtual void render();
	virtual void cleanup();
	virtual void event(SDL_Event* evt);
	virtual bool running();
};


#endif // SCENARIOBASEDSCENE_H
