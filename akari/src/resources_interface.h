#ifndef RESOURCES_INTERFACE_H
#define RESOURCES_INTERFACE_H

#include <string>
#include <boost/shared_ptr.hpp>
#include "tileset_interface.h"
#include "mapdesc_interface.h"
#include "font_interface.h"

class resources_interface {
public:
	virtual GLuint getimage(std::string identifier)=0;
	virtual boost::shared_ptr<tileset_interface> gettileset(std::string identifier)=0;
	virtual boost::shared_ptr<font_interface> getfont(std::string identifier)=0;
};

#endif // RESOURCES_INTERFACE_H
