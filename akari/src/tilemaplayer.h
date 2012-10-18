#ifndef TILEMAPLAYER_H
#define TILEMAPLAYER_H

#include "boost/shared_ptr.hpp"
#include "boost/shared_array.hpp"

#include "tilecomposition.h"
#include "resources_interface.h"
#include "vertexbuffer.h"
#include "matrix.h"
#include "utils.h"
#include "texanimshader_interface.h"

class tilemaplayer
{
	int camerax,cameray;
	matrix<boost::shared_ptr<vertexbuffer>, 3, 3> buffers;
	boost::shared_ptr<resources_interface> resources;
	boost::shared_ptr<mapdesc_interface> mapdesc;
	boost::shared_ptr<texanimshader_interface> shader;
	int w,h;

	int screenw;
	int screenh;

	// we use these variables to find out if we need to rebuffer
	int anchorx;
	int anchory;

	SDL_mutex* mutex;

	void prepbuffers()
	{
		printf("anchorx %d, anchory %d", anchorx, anchory);
		printf("block matrix:\n");
		printf("%p\t%p\t%p\n",buffers(0,0).get(),buffers(1,0).get(),buffers(2,0).get());
		printf("%p\t%p\t%p\n",buffers(0,1).get(),buffers(1,1).get(),buffers(2,1).get());
		printf("%p\t%p\t%p\n",buffers(0,2).get(),buffers(1,2).get(),buffers(2,2).get());

		boost::shared_ptr<tilecomposition> tc;

		for (int x=0;x<buffers.getcolumns();x++)
		for (int y=0;y<buffers.getrows();y++)
		{
			int locationx = anchorx/32 + (x - buffers.getcolumns() / 2) * w;
			int locationy = anchory/32 + (y - buffers.getrows() / 2) * h;

			if (buffers(x,y) == NULL)
			{
				tc = boost::shared_ptr<tilecomposition>(new tilecomposition(locationx, locationy, w+1, h+1, resources, mapdesc));
				buffers(x, y) = boost::shared_ptr<vertexbuffer>(new vertexbuffer(shader, tc));
			}
		}

		printf("block matrix:\n");
		printf("%p\t%p\t%p\n",buffers(0,0).get(),buffers(1,0).get(),buffers(2,0).get());
		printf("%p\t%p\t%p\n",buffers(0,1).get(),buffers(1,1).get(),buffers(2,1).get());
		printf("%p\t%p\t%p\n",buffers(0,2).get(),buffers(1,2).get(),buffers(2,2).get());
	}

public:

	tilemaplayer(boost::shared_ptr<texanimshader_interface> shader, boost::shared_ptr<resources_interface> resources,  boost::shared_ptr<mapdesc_interface> mapdesc, int width, int height)
		: camerax(0), cameray(0), mapdesc(mapdesc), shader(shader), resources(resources), anchorx(0), anchory(0)
	{
		// We keep 9 vertex buffers the size of the screen
		this->w = width / 32;
		this->h = height / 32;

		this->screenw = width;
		this->screenh = height;

		this->mutex = SDL_CreateMutex();

		prepbuffers();
	}

	int getx() const
	{
		return camerax;
	}
	
	int gety() const
	{
		return cameray;
	}

	static int reprep(void* tmlp) {
		tilemaplayer* tml = (tilemaplayer*)tmlp;
		tml->prepbuffers();
		return 0;
	};

	void setcamera(int x, int y)
	{
		camerax = x;
		cameray = y;

		int marginx = screenw/3;
		int marginy = screenh/3;

		bool needToReprep = false;
		int dx = camerax + anchorx;
		int dy = cameray + anchory;

		if (dx < -2*marginx)
		{
			anchorx += screenw;
			buffers.shift(1,0,[](){return boost::shared_ptr<vertexbuffer>();});
			needToReprep = true;
		}
		else if (dx > 2*marginx)
		{
			anchorx -= screenw;
			buffers.shift(-1,0,[](){return boost::shared_ptr<vertexbuffer>();});
			needToReprep = true;
		}

		if (dy < -2*marginy)
		{
			anchory += screenh;
			buffers.shift(0,1,[](){return boost::shared_ptr<vertexbuffer>();});
			needToReprep = true;
		}
		else if (dy > 2*marginy)
		{
			anchory -= screenh;
			buffers.shift(0,-1,[](){return boost::shared_ptr<vertexbuffer>();});
			needToReprep = true;
		}

		if (needToReprep)
		{
			//SDL_CreateThread(reprep, this);
			prepbuffers();
		}
	}

	void render(int tile)
	{
		// test rebuffer performance
		/*buffers(0,0) = boost::shared_ptr<vertexbuffer>();
		prepbuffers();*/

		glEnable2D(camerax,cameray);

		buffers.foreach([=](boost::shared_ptr<vertexbuffer> v)
		{
			if (v.get() != NULL)
			{
				v->Render(tile);
			}
		});

		glDisable2D();
	}
};

#endif // TILEMAPLAYER_H
