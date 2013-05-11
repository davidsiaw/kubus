#include "btileset.h"

// maps from the corner and mask to the rawtile

const std::tr1::array<tilecorner, 4> btileset::autotile12map = 
{
	{
		{{10,  0,  1,  2,  6,  7,  9,  8}},
		{{10,  2,  3,  4,  0,  1,  9,  8}},
		{{10,  4,  5,  6,  2,  3,  9,  8}},
		{{10,  6,  7,  0,  4,  5,  9,  8}}
	}
};

const std::tr1::array<tilecorner, 4> btileset::autotile94map = 
{
	{
		{{ 0,  0,  1,  2,  6,  7,  9,  8}},
		{{ 2,  2,  3,  4,  0,  1, 10,  8}},
		{{ 4,  4,  5,  6,  2,  3, 11,  8}},
		{{ 6,  6,  7,  0,  4,  5, 12,  8}}
	}
};

unsigned char toprightcornermask(unsigned char surrounding)
{
	return (((surrounding >> 3) & 6) | (surrounding & 1));
}

unsigned char bottomrightcornermask(unsigned char surrounding)
{
	return (((surrounding >> 4) & 6) | ((surrounding >> 1) & 1));
}

unsigned char bottomleftcornermask(unsigned char surrounding)
{
	return (((surrounding >> 5) & 6) | ((surrounding >> 2) & 1));
}

unsigned char topleftcornermask(unsigned char surrounding)
{
	return (((surrounding >> 3) & 1) | ((surrounding >> 2) & 4) | ((surrounding >> 6) & 2));
}

const std::tr1::array<btileset::getcornermaskfunc, 4> btileset::cornermaskfuncs = 
{
	toprightcornermask,
	bottomrightcornermask,
	bottomleftcornermask,
	topleftcornermask,
};

