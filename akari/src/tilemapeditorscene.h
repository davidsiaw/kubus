#ifndef TILEMAPEDITORSCENE_H
#define TILEMAPEDITORSCENE_H

#include <tr1/memory>

#include "scene_interface.h"
#include "resources_interface.h"
#include "textlayer.h"
#include "tilemaplayer.h"
#include "ordinarytexanimshader.h"

class tilemapeditorscene : public scene_interface
{
	std::tr1::shared_ptr<ordinarytexanimshader> shader;
	std::tr1::shared_ptr<font_interface> font;
	std::tr1::shared_ptr<tilemaplayer> tilelayer;

	std::tr1::shared_ptr<textlayer> campos;

public:
	tilemapeditorscene(std::tr1::shared_ptr<resources_interface> resources,  std::tr1::shared_ptr<mapdesc_interface> mapdesc, std::tr1::shared_ptr<font_interface> font);
	~tilemapeditorscene();
	virtual void init(SDL_Surface* video);
	virtual void update();
	virtual void render();
	virtual void cleanup();
	virtual void event(SDL_Event* evt);
	virtual bool running();
};


#endif // TILEMAPEDITORSCENE_H
