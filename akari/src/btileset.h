#ifndef BTILESET_H
#define BTILESET_H

#include <vector>
#include <boost/tr1/memory.hpp>
#include "tileset_interface.h"
#include "autotile.h"
#include "simpletile.h"
#include "tileinfo.h"
#include "tile_type.h"


class btileset : public tileset_interface
{
	typedef unsigned char (*getcornermaskfunc)(unsigned char);

	boost::shared_array<tileinfo> tinfo;
	std::vector<std::tr1::shared_ptr<tile_interface>> tiles;
	std::string texmap;

	const static std::tr1::array<tilecorner, 4> autotile12map;
	const static std::tr1::array<tilecorner, 4> autotile94map;
	const static std::tr1::array<getcornermaskfunc, 4> cornermaskfuncs;
	
	unsigned char getcornermask(unsigned char pos, unsigned char surround)
	{
		return cornermaskfuncs[pos](surround);
	}

	void populatequad(tileinfo& info, quad& q, float xshift, float yshift)
	{
		q.e[0].t.x = info.x4+xshift;
		q.e[0].t.y = info.y4+yshift;
		q.e[1].t.x = info.x1+xshift;
		q.e[1].t.y = info.y1+yshift-info.height/2;
		q.e[2].t.x = info.x2+xshift-info.width/2;
		q.e[2].t.y = info.y2+yshift-info.height/2;
		q.e[3].t.x = info.x3+xshift-info.width/2;
		q.e[3].t.y = info.y3+yshift;
		q.e[0].tileOffset = info.width;
		q.e[1].tileOffset = info.width;
		q.e[2].tileOffset = info.width;
		q.e[3].tileOffset = info.width;
		q.e[0].numtiles = info.numframes;
		q.e[1].numtiles = info.numframes;
		q.e[2].numtiles = info.numframes;
		q.e[3].numtiles = info.numframes;
	}

public:
	btileset(FILE* basictilesfile, FILE* tilesfile, std::string texmap) : texmap(texmap)
	{
		int numoftiles;
		fread(&numoftiles, sizeof(int), 1, basictilesfile);
		tinfo = boost::shared_array<tileinfo>(new tileinfo[numoftiles]);
		fread(tinfo.get(), sizeof(tileinfo), numoftiles, basictilesfile);
		
		fread(&numoftiles, sizeof(int), 1, tilesfile);
		for (int i=0;i<numoftiles;i++)
		{
			tile_type type;
			fread(&type, sizeof(int), 1, tilesfile);

			if (type == SIMPLE)
			{
				int idx;
				fread(&idx, sizeof(int), 1, tilesfile);
				tiles.push_back(std::tr1::shared_ptr<tile_interface>(new simpletile(idx)));
			}
			else if (type == AUTOTILE12 || type == AUTOTILE94)
			{
				int numvariations;
				fread(&numvariations, sizeof(int), 1, tilesfile);
				boost::shared_array<int> rawtiles(new int[numvariations]);

				for (int v=0;v<numvariations;v++)
				{
					int idx;
					fread(&idx,sizeof(int),1,tilesfile);
					rawtiles[v] = idx;
				}

				std::tr1::array<tilecorner, 4> posmap;
				if (type == AUTOTILE12)
				{
					posmap = autotile12map;
				}
				else
				{
					posmap = autotile94map;
				}

				tiles.push_back(std::tr1::shared_ptr<tile_interface>(new autotile(rawtiles, posmap, type)));
			}
		}
	}

	virtual std::string gettexturemap()
	{
		return texmap;
	}

	virtual std::tr1::tuple<int, boost::shared_array<quad>> getframeforid(int x, int y, std::tr1::function<tileid(int,int)> reversequery)
	{
		int id = reversequery(x,y).id;

		unsigned char surround = (
			((reversequery(x+1, y-1).id == id?1:0) << 0) |
			((reversequery(x+1, y+1).id == id?1:0) << 1) |
			((reversequery(x-1, y+1).id == id?1:0) << 2) |
			((reversequery(x-1, y-1).id == id?1:0) << 3) |
			((reversequery(x  , y-1).id == id?1:0) << 4) |
			((reversequery(x+1, y  ).id == id?1:0) << 5) |
			((reversequery(x  , y+1).id == id?1:0) << 6) |
			((reversequery(x-1, y  ).id == id?1:0) << 7)
		);

		auto type = tiles[id]->gettype();
		if (type == SIMPLE)
		{
			boost::shared_array<quad> tile(new quad[1]);
			tileinfo& info = tinfo[tiles[id]->getbasictile(0,0)];

			quad q = MakeQuad(x * 32,y * 32,32,32);
			q.e[0].t.x = info.x4;
			q.e[0].t.y = info.y4;
			q.e[1].t.x = info.x1;
			q.e[1].t.y = info.y1;
			q.e[2].t.x = info.x2;
			q.e[2].t.y = info.y2;
			q.e[3].t.x = info.x3;
			q.e[3].t.y = info.y3;
			q.e[0].tileOffset = info.width;
			q.e[1].tileOffset = info.width;
			q.e[2].tileOffset = info.width;
			q.e[3].tileOffset = info.width;
			q.e[0].numtiles = info.numframes;
			q.e[1].numtiles = info.numframes;
			q.e[2].numtiles = info.numframes;
			q.e[3].numtiles = info.numframes;
			tile[0] = q;

			return std::tr1::tuple<int, boost::shared_array<quad>>(1, tile);
		}

		boost::shared_array<quad> tile(new quad[4]);

		quad q1 = MakeQuad(x * 32+16,y * 32, 16, 16);
		tileinfo& info1 = tinfo[tiles[id]->getbasictile(0, getcornermask(0, surround))];
		populatequad(info1, q1, info1.width/2, 0);
		tile[0] = q1;

		quad q2 = MakeQuad(x * 32+16,y * 32+16, 16, 16);
		tileinfo& info2 = tinfo[tiles[id]->getbasictile(1, getcornermask(1, surround))];
		populatequad(info2, q2, info2.width/2, info2.height/2);
		tile[1] = q2;

		quad q3 = MakeQuad(x * 32,y * 32+16, 16, 16);
		tileinfo& info3 = tinfo[tiles[id]->getbasictile(2, getcornermask(2, surround))];
		populatequad(info3, q3,            0, info3.height/2);
		tile[2] = q3;

		quad q4 = MakeQuad(x * 32   ,y * 32   , 16, 16);
		tileinfo& info4 = tinfo[tiles[id]->getbasictile(3, getcornermask(3, surround))];
		populatequad(info4, q4, 0, 0);
		tile[3] = q4;

		return std::tr1::tuple<int, boost::shared_array<quad>>(4, tile);

	}
};

#endif // BTILESET_H
