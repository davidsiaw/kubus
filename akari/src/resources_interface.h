#ifndef RESOURCES_INTERFACE_H
#define RESOURCES_INTERFACE_H

#include <string>
#include <boost/tr1/memory.hpp>
#include "tileset_interface.h"
#include "mapdesc_interface.h"
#include "font_interface.h"
#include "objectset_interface.h"

class resources_interface {
public:
	virtual GLuint getimage(std::string identifier)=0;
	virtual std::tr1::shared_ptr<tileset_interface> gettileset(std::string identifier)=0;
	virtual std::tr1::shared_ptr<font_interface> getfont(std::string identifier)=0;
	virtual std::tr1::shared_ptr<objectset_interface> getcharmap(std::string identifier)=0;

};

#endif // RESOURCES_INTERFACE_H
