#ifndef TILEFRAME_INTERFACE_H
#define TILEFRAME_INTERFACE_H

#include <boost/shared_array.hpp>
#include "primitives.h"

struct tileframe 
{
	unsigned int numframes;
	float width;
	float height;
	boost::shared_array<texcoord> startframecoord;
};

#endif // TILEFRAME_INTERFACE_H
