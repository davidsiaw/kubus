#ifndef OBJECT_INTERFACE
#define OBJECT_INTERFACE

#include "primitives.h"

class object_interface
{
public:
	virtual quad getcurrentquad()=0;
	virtual void setid(int)=0;
	virtual int getid()=0;
};

#endif // OBJECT_INTERFACE
