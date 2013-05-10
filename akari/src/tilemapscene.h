#ifndef TILEMAPSCENE_H
#define TILEMAPSCENE_H

#include <tr1/memory>

#include "scene_interface.h"
#include "resources_interface.h"
#include "textlayer.h"
#include "tilemaplayer.h"
#include "ordinarytexanimshader.h"
#include "mobilecharacterset.h"
#include "objectlayer.h"

class tilemapscene : public scene_interface
{
	std::tr1::shared_ptr<ordinarytexanimshader> shader;
	std::tr1::shared_ptr<font_interface> font;
	std::tr1::shared_ptr<tilemaplayer> tilelayer;

	std::tr1::shared_ptr<objectset_interface> objectset;

	std::tr1::shared_ptr<textlayer> campos;
	std::tr1::shared_ptr<objectlayer> objects;

	std::tr1::shared_ptr<mobilecharacter> playerobject;

	std::tr1::shared_ptr<mobilecharacter> otherobject;
	int playerindex;

public:
	tilemapscene(std::tr1::shared_ptr<resources_interface> resources,  std::tr1::shared_ptr<mapdesc_interface> mapdesc, std::tr1::shared_ptr<font_interface> font);
	~tilemapscene();
	virtual void init(SDL_Surface* video);
	virtual void update();
	virtual void render();
	virtual void cleanup();
	virtual void event(SDL_Event* evt);
	virtual bool running();
};


#endif // TILEMAPSCENE_H
