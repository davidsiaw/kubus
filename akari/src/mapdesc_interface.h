#ifndef MAPDESC_INTERFACE_H
#define MAPDESC_INTERFACE_H

#include <string>
#include "tileset_interface.h"

class mapdesc_interface {
public:
	virtual std::string gettilesetname()=0;
	virtual tileid getid(int x, int y)=0;
};

#endif // MAPDESC_INTERFACE_H
