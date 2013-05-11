#ifndef MOBILECHARACTERSET_H
#define MOBILECHARACTERSET_H

#include "objectset_interface.h"
#include "charmapinfo.h"

class mobilecharacterset : public objectset_interface
{
	std::string map;
	std::vector<charmapinformation> charmapinfo;
public:

	mobilecharacterset (std::string map, std::vector<charmapinformation> charmapinfo) : map(map + ".png"), charmapinfo(charmapinfo)
	{
	}
	
	virtual std::string gettexturemap()
	{
		return map;
	}

	virtual std::tr1::shared_ptr<mobilecharacter> createobject(int id)
	{

		return std::tr1::shared_ptr<mobilecharacter>(new mobilecharacter(charmapinfo[id]));
	}
};

#endif // MOBILECHARACTERSET_H
