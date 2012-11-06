#ifndef MOBILECHARACTERSET_H
#define MOBILECHARACTERSET_H

#include "objectset_interface.h"

class mobilecharacterset : public objectset_interface
{
public:
	virtual std::string gettexturemap()
	{
		return "boy2.png";
	}

	virtual boost::shared_ptr<mobilecharacter> createobject(int id)
	{
		return boost::shared_ptr<mobilecharacter>(new mobilecharacter());
	}
};

#endif // MOBILECHARACTERSET_H