#ifndef TILEMAPSCENE_H
#define TILEMAPSCENE_H

#include <boost/shared_ptr.hpp>

#include "scene_interface.h"
#include "resources_interface.h"
#include "textlayer.h"
#include "tilemaplayer.h"
#include "ordinarytexanimshader.h"
#include "mobilecharacterset.h"
#include "objectlayer.h"

class tilemapscene : public scene_interface
{
	boost::shared_ptr<ordinarytexanimshader> shader;
	boost::shared_ptr<font_interface> font;
	boost::shared_ptr<tilemaplayer> tilelayer;

	boost::shared_ptr<objectset_interface> objectset;

	boost::shared_ptr<textlayer> campos;
	boost::shared_ptr<objectlayer> objects;

	boost::shared_ptr<mobilecharacter> playerobject;

	boost::shared_ptr<mobilecharacter> otherobject;
	int playerindex;

public:
	tilemapscene(boost::shared_ptr<resources_interface> resources,  boost::shared_ptr<mapdesc_interface> mapdesc, boost::shared_ptr<font_interface> font);
	~tilemapscene();
	virtual void init(SDL_Surface* video);
	virtual void update();
	virtual void render();
	virtual void cleanup();
	virtual void event(SDL_Event* evt);
	virtual bool running();
};


#endif // TILEMAPSCENE_H
