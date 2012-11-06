#ifndef TILE_INTERFACE_H
#define TILE_INTERFACE_H

#include "tile_type.h"

class tile_interface
{
public:
	virtual tile_type gettype()=0;
	virtual int getbasictile(unsigned char corner, unsigned char mask)=0;
};

#endif // TILE_INTERFACE_H
