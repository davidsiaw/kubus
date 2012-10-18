#ifndef TILESET_INTERFACE_H
#define TILESET_INTERFACE_H

#include <string>
#include "tileid.h"
#include "tileframe.h"

class tileset_interface 
{
public:
	virtual std::string gettexturemap()=0;
	virtual tileframe getframeforid(int x, int y, std::function<tileid(int,int)> reversequery)=0;
};

#endif // TILESET_INTERFACE_H
