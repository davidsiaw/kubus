#ifndef TILESET_INTERFACE_H
#define TILESET_INTERFACE_H

#include <boost/tr1/functional.hpp>
#include <boost/tr1/tuple.hpp>
#include <string>
#include "tileid.h"
#include "tileframe.h"

class tileset_interface 
{
public:
	virtual std::string gettexturemap()=0;
	virtual std::tr1::tuple<int, boost::shared_array<quad>> getframeforid(int x, int y, std::tr1::function<tileid(int,int)> reversequery)=0;
};

#endif // TILESET_INTERFACE_H
