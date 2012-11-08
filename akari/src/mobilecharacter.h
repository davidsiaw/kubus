#ifndef MOBILECHARACTER_H
#define MOBILECHARACTER_H


#include "object_interface.h"
#include "objectdirection.h"
#include "characteraction.h"


class mobilecharacter : public object_interface
{
	objectdirection dir;
	characteraction action;
	int x;
	int y;

	int offsetx;
	int offsety;

	int id;

public:
	mobilecharacter() : id(-1), x(0), y(0), offsetx((-48+32)/2), offsety(-64+32/2), dir(UP), action(STAND)
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
		quad q = MakeQuad(x + offsetx,y + offsety,48,64);
		
		q.e[0].tileOffset = 0.25;
		q.e[1].tileOffset = 0.25;
		q.e[2].tileOffset = 0.25;
		q.e[3].tileOffset = 0.25;

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

			q.e[0].t.x = 0.75;
			q.e[0].t.y = dir * 0.25;

			q.e[1].t.x = 0.75;
			q.e[1].t.y = dir * 0.25 + 0.25;

			q.e[2].t.x = 1.0;
			q.e[2].t.y = dir * 0.25 + 0.25;

			q.e[3].t.x = 1.0;
			q.e[3].t.y = dir * 0.25;
		}
		else if (action == WALK)
		{
			q.e[0].numtiles = 4;
			q.e[1].numtiles = 4;
			q.e[2].numtiles = 4;
			q.e[3].numtiles = 4;

			q.e[0].t.x = 0;
			q.e[0].t.y = dir * 0.25;

			q.e[1].t.x = 0;
			q.e[1].t.y = dir * 0.25 + 0.25;

			q.e[2].t.x = 0.25;
			q.e[2].t.y = dir * 0.25 + 0.25;

			q.e[3].t.x = 0.25;
			q.e[3].t.y = dir * 0.25;
		}


		return q;
	}
};

#endif // MOBILECHARACTER_H
