#ifndef BITMAPFONT_H
#define BITMAPFONT_H

#include <map>
#include <string>
#include <boost/shared_array.hpp>
#include "primitives.h"
#include "fontinfo.h"
#include "font_interface.h"

class bitmapfont : public font_interface
{
	std::map<unsigned int, quad> quads;
	std::string fontdesc;
	std::string texmap;

public:
	bitmapfont(FILE* fontfile, std::string texmap) : texmap(texmap)
	{
		int numofchars=0;
		fread(&numofchars, sizeof(int), 1, fontfile);
		auto tinfo = boost::shared_array<fontinfo>(new fontinfo[numofchars]);
		fread(tinfo.get(), sizeof(fontinfo), numofchars, fontfile);

		for (int i=0;i<numofchars;i++)
		{
			quad q = MakeQuad(0,0,tinfo[i].width,tinfo[i].height);
			q.e[0].t.x = tinfo[i].x4;
			q.e[1].t.x = tinfo[i].x1;
			q.e[2].t.x = tinfo[i].x2;
			q.e[3].t.x = tinfo[i].x3;

			q.e[0].t.y = tinfo[i].y4;
			q.e[1].t.y = tinfo[i].y1;
			q.e[2].t.y = tinfo[i].y2;
			q.e[3].t.y = tinfo[i].y3;
			quads[tinfo[i].chr] = q;
		}
	}

	virtual std::string gettexturemap()
	{
		return texmap;
	}

	virtual quad getquadforchar(unsigned int chr)
	{
		return quads[chr];
	}

	virtual unsigned int getspaceforchar(unsigned int chr1, unsigned int chr2)
	{
		return quads[chr1].e[2].v.x;
	}
};

#endif // BITMAPFONT_H
