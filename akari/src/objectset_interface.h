#ifndef OBJECTSET_INTERFACE
#define OBJECTSET_INTERFACE

#include "mobilecharacter.h"

class objectset_interface
{
public:
	virtual std::string gettexturemap()=0;
	virtual std::tr1::shared_ptr<mobilecharacter> createobject(int id)=0;
};

#endif // OBJECTSET_INTERFACE
