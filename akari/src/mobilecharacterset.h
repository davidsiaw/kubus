#ifndef MOBILECHARACTERSET_H
#define MOBILECHARACTERSET_H

#include "objectset_interface.h"
#include "charmapinfo.h"

class mobilecharacterset : public objectset_interface
{
	std::string map;
	std::vector<charmapinformation> charmapinfo;
public:

	mobilecharacterset (std::string map)
	{
		this->map = map + ".png";
		FILE* fp = fopen((map + ".charmap").c_str(), "rb");
		std::cout << "meow" << map << std::endl;
		int numcharacters;
		fread(&numcharacters, sizeof(int), 1, fp);
		for (int i=0; i<numcharacters; i++)
		{
			charmapinformation cmi;
			fread(&cmi, sizeof(charmapinformation), 1, fp);
			charmapinfo.push_back(cmi);
		}
		fclose(fp);
	}
	
	virtual std::string gettexturemap()
	{
		return map;
	}

	virtual boost::shared_ptr<mobilecharacter> createobject(int id)
	{
		return boost::shared_ptr<mobilecharacter>(new mobilecharacter(charmapinfo[id]));
	}
};

#endif // MOBILECHARACTERSET_H
