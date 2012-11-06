#ifndef SIMPLETILE_H
#define SIMPLETILE_H

#include "tile_interface.h"
class simpletile : public tile_interface
{
	int tile;
public:
	simpletile(int tile) : tile(tile)
	{
	}

	virtual tile_type gettype()
	{
		return SIMPLE;
	}

	virtual int getbasictile(unsigned char corner, unsigned char mask)
	{
		return tile;
	}
};


#endif // SIMPLETILE_H
