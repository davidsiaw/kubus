#ifndef OBJECT_INTERFACE
#define OBJECT_INTERFACE

#include "primitives.h"

class object_interface
{
	Uint32 lastupdated;
public:
	virtual quad getcurrentquad()=0;
	virtual void setid(int)=0;
	virtual int getid()=0;
	virtual Uint32 getlastupdated() const { return lastupdated; }
	virtual void setlastupdated(Uint32 updated) { lastupdated = updated; }
};

#endif // OBJECT_INTERFACE
