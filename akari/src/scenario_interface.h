#ifndef SCENARIOINTERFACE_H
#define SCENARIOINTERFACE_H

#include "mobilecharacter.h"

class scenario_interface
{
public:
	virtual void setresolution(int width, int height)=0;
	virtual std::tr1::shared_ptr<mobilecharacter> gethero()=0;
	virtual void update()=0;
	virtual void render()=0;
	virtual bool ended() const=0;

	virtual void commandcharacter(std::tr1::shared_ptr<mobilecharacter> character, objectdirection dir, characteraction act)=0;
};

#endif // SCENARIOINTERFACE_H

