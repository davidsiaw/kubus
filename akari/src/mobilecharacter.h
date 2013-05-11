#ifndef MOBILECHARACTER_H
#define MOBILECHARACTER_H


#include "object_interface.h"
#include "objectdirection.h"
#include "characteraction.h"
#include "charmapinfo.h"


class mobilecharacter : public object_interface
{
	objectdirection dir;
	characteraction action;
	int x;
	int y;

	charmapinformation info;

	int id;

public:
	mobilecharacter(charmapinformation info) : id(-1), x(0), y(0), info(info), dir(UP), action(STAND)
	{ }

	void setaction(characteraction action)
	{
		this->action = action;
	}

	void setdirection(objectdirection dir)
	{
		this->dir = dir;
	}

	objectdirection getdirection() const
	{
		return this->dir;
	}

	int getx() const
	{
		return x;
	}

	int gety() const
	{
		return y;
	}

	void setlocation(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	
	virtual void setid(int id)
	{
		this->id = id;
	}

	virtual int getid()
	{
		return id;
	}

	virtual quad getcurrentquad()
	{
		quad q = MakeQuad(x + info.xoffset,y + info.yoffset,info.xpixsize,info.ypixsize);
		
		q.e[0].tileOffset = info.xsize;
		q.e[1].tileOffset = info.xsize;
		q.e[2].tileOffset = info.xsize;
		q.e[3].tileOffset = info.xsize;

		q.e[0].v.z = 10 + y/100.0;
		q.e[1].v.z = 10 + y/100.0;
		q.e[2].v.z = 10 + y/100.0;
		q.e[3].v.z = 10 + y/100.0;

		if (action == STAND)
		{
			q.e[0].numtiles = 1;
			q.e[1].numtiles = 1;
			q.e[2].numtiles = 1;
			q.e[3].numtiles = 1;

			q.e[0].t.x = info.xstart;
			q.e[0].t.y = info.ystart + dir * info.ysize;

			q.e[1].t.x = info.xstart;
			q.e[1].t.y = info.ystart + dir * info.ysize + info.ysize;

			q.e[2].t.x = info.xstart + info.xsize;
			q.e[2].t.y = info.ystart + dir * info.ysize + info.ysize;

			q.e[3].t.x = info.xstart + info.xsize;
			q.e[3].t.y = info.ystart + dir * info.ysize;
		}
		else if (action == WALK)
		{
			q.e[0].numtiles = info.numtiles;
			q.e[1].numtiles = info.numtiles;
			q.e[2].numtiles = info.numtiles;
			q.e[3].numtiles = info.numtiles;

			q.e[0].t.x = info.xstart;
			q.e[0].t.y = info.ystart + dir * info.ysize;

			q.e[1].t.x = info.xstart;
			q.e[1].t.y = info.ystart + dir * info.ysize + info.ysize;

			q.e[2].t.x = info.xstart + info.xsize;
			q.e[2].t.y = info.ystart + dir * info.ysize + info.ysize;

			q.e[3].t.x = info.xstart + info.xsize;
			q.e[3].t.y = info.ystart + dir * info.ysize;
		}


		return q;
	}
};

#endif // MOBILECHARACTER_H
