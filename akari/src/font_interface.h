#ifndef FONT_INTERFACE_H
#define FONT_INTERFACE_H

#include <string>
#include "primitives.h"

class font_interface
{
public:
	virtual std::string gettexturemap()=0;
	virtual quad getquadforchar(unsigned int chr)=0;
	virtual unsigned int getspaceforchar(unsigned int chr1, unsigned int chr2)=0;
};

#endif // FONT_INTERFACE_H
