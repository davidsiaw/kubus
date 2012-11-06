#ifndef AUTOTILE_H
#define AUTOTILE_H

#include <array>
#include <boost/shared_array.hpp>
#include "tile_interface.h"

struct tilecorner
{
	int sides[8];
};

class autotile : public tile_interface
{
	boost::shared_array<int> rawtiles;
	std::array<tilecorner, 4> posAndMaskToTile;
	tile_type type;

public:
	autotile(boost::shared_array<int> rawtiles, std::array<tilecorner, 4> posAndMaskToTile, tile_type type) : 
	  rawtiles(rawtiles), posAndMaskToTile(posAndMaskToTile), type(type)
	{
	}

	virtual tile_type gettype()
	{
		return type;
	}

	virtual int getbasictile(unsigned char corner, unsigned char mask)
	{
		return rawtiles[posAndMaskToTile[corner].sides[mask]];
	}
};

#endif // AUTOTILE_H

