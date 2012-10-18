#include <stdio.h>
#include <stdlib.h>
#include <sdl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <GL/glew.h>
#include <boost/shared_ptr.hpp>
#include "akari.h"

#include "scene_interface.h"

#include "tilemapscene.h"

#include <map>

int screenWidth = 800;
int screenHeight = 600;
SDL_Surface* screen;

void run(boost::shared_ptr<scene_interface> scene)
{
	scene->init(screen);
	
    SDL_Event evt;
    while(scene->running())
    {
        if(SDL_PollEvent(&evt))
        {
			scene->event(&evt);
        }

        scene->update();

		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
        scene->render();
		SDL_GL_SwapBuffers();
	}

	scene->cleanup();
}

int initialize()
{
	log("Initializing SDL\n");
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {	
		log("SDL_Init: %s\n", SDL_GetError());
		return EXIT_FAILURE;
    }
	
	log("Initializing SDL_TTF\n");
	if(TTF_Init() == -1) {
		log("TTF_Init: %s\n", TTF_GetError());
		return EXIT_FAILURE;
	}
	
	log("Initializing Video\n");
    if((screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL )) == NULL)
    {
		log("SDL_Init: %s\n", SDL_GetError());
		return EXIT_FAILURE;
    }
	
	log("Initializing Glew\n");
    glewInit();
	Init3D(screenWidth, screenHeight);

    return EXIT_SUCCESS;
}

#pragma pack(push, 1)
struct tileinfo
{
	int numframes;
	float width;
	float height;

	//texcoords
	float x1, y1;
	float x2, y2;
	float x3, y3;
	float x4, y4;
};
#pragma pack(pop)

class tile_interface
{
public:
	virtual int getbasictile(unsigned char surround)=0;
};

class simpletile : public tile_interface
{
	int tile;
public:
	simpletile(int tile) : tile(tile)
	{
	}

	virtual int getbasictile(unsigned char surround)
	{
		return tile;
	}
};

class autotile : public tile_interface
{
	std::map<unsigned char, int> surroundtobasictile;
public:
	autotile(std::map<unsigned char, int> surroundtobasictile) : surroundtobasictile(surroundtobasictile)
	{
	}

	virtual int getbasictile(unsigned char surround)
	{
		return surroundtobasictile[surround];
	}
};

enum tile_type
{
	SIMPLE,
	AUTOTILE
};

class mytileset : public tileset_interface
{
	boost::shared_array<tileinfo> tinfo;
	std::vector<boost::shared_ptr<tile_interface>> tiles;

public:
	mytileset()
	{
		FILE* fp = fopen("D:/gcc/akari/res/rmxp.basictiles", "rb");
		int numoftiles;
		fread(&numoftiles, sizeof(int), 1, fp);
		tinfo = boost::shared_array<tileinfo>(new tileinfo[numoftiles]);
		fread(tinfo.get(), sizeof(tileinfo), numoftiles, fp);
		fclose(fp);
		
		fp = fopen("D:/gcc/akari/res/rmxp.tiles", "rb");
		fread(&numoftiles, sizeof(int), 1, fp);
		for (int i=0;i<numoftiles;i++)
		{
			tile_type type;
			fread(&type, sizeof(int), 1, fp);

			if (type == SIMPLE)
			{
				int idx;
				fread(&idx, sizeof(int), 1, fp);
				tiles.push_back(boost::shared_ptr<tile_interface>(new simpletile(idx)));
			}
			else if (type == AUTOTILE)
			{
				int numvariations;
				fread(&numvariations, sizeof(int), 1, fp);
				std::map<unsigned char, int> surroundtobasictile;
				for (int v=0;v<numvariations;v++)
				{
					unsigned char sur;
					int idx;
					fread(&sur,sizeof(unsigned char),1,fp);
					fread(&idx,sizeof(int),1,fp);
					surroundtobasictile[sur] = idx;
				}
				tiles.push_back(boost::shared_ptr<tile_interface>(new autotile(surroundtobasictile)));
			}
		}

	}

	virtual std::string gettexturemap()
	{
		return "D:/gcc/akari/res/rmxp.png";
	}


	virtual tileframe getframeforid(int x, int y, std::function<tileid(int,int)> reversequery)
	{
		int id = reversequery(x,y).id;

		unsigned char surround = (
			((reversequery(x+1, y-1).id == id?1:0) << 0) |
			((reversequery(x+1, y+1).id == id?1:0) << 1) |
			((reversequery(x-1, y+1).id == id?1:0) << 2) |
			((reversequery(x-1, y-1).id == id?1:0) << 3) |
			((reversequery(x, y-1).id == id  ?1:0) << 4) |
			((reversequery(x+1, y).id == id  ?1:0) << 5) |
			((reversequery(x, y+1).id == id  ?1:0) << 6) |
			((reversequery(x-1, y).id == id  ?1:0) << 7)
		);

		int frameid;

		tileframe frame;
		tileinfo& info = tinfo[tiles[id]->getbasictile(surround)];
		frame.height = info.height;
		frame.width = info.width;
		frame.numframes = info.numframes;
		frame.startframecoord = boost::shared_array<texcoord>(new texcoord[4]);
		frame.startframecoord[0].x = info.x4;
		frame.startframecoord[0].y = info.y4;
		frame.startframecoord[1].x = info.x1;
		frame.startframecoord[1].y = info.y1;
		frame.startframecoord[2].x = info.x2;
		frame.startframecoord[2].y = info.y2;
		frame.startframecoord[3].x = info.x3;
		frame.startframecoord[3].y = info.y3;
		return frame;
	}
};

class mymapdesc : public mapdesc_interface
{
public:
	virtual std::string gettilesetname()
	{
		return "lol";
	}

	virtual tileid getid(int x, int y)
	{
		tileid id;
		id.id =  (unsigned int)( (unsigned int)x / 12 +  (unsigned int)y / 12) % 2;
		return id;
	}
};

#pragma pack(1)
struct fontinfo
{
	unsigned int chr;
    float width;
    float height;
    float x1, y1;
    float x2, y2;
    float x3, y3;
    float x4, y4;
};

class myfont : public font_interface
{
	std::map<unsigned int, quad> quads;

public:
	myfont()
	{
		int numofchars=0;
		FILE* fp = fopen("D:/gcc/akari/res/myfont.font", "rb");
		fread(&numofchars, sizeof(int), 1, fp);
		auto tinfo = boost::shared_array<fontinfo>(new fontinfo[numofchars]);
		fread(tinfo.get(), sizeof(fontinfo), numofchars, fp);
		fclose(fp);

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
		return "D:/gcc/akari/res/myfont.png";
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

class myresources : public resources_interface
{
	boost::shared_ptr<tileset_interface> tileset;
	boost::shared_ptr<mapdesc_interface> mapdesc;
	boost::shared_ptr<font_interface> font;
	std::map<std::string, GLuint> images;

public:
	myresources() : 
		tileset(boost::shared_ptr<tileset_interface>(new mytileset())),
		mapdesc(boost::shared_ptr<mapdesc_interface>(new mymapdesc())),
		font(boost::shared_ptr<font_interface>(new myfont()))
	{
	}

	virtual GLuint getimage(std::string identifier)
	{
		if (images.find(identifier) == images.end())
		{
			glActiveTexture(GL_TEXTURE0);
			boost::shared_ptr<SDL_Surface> tex(IMG_Load(identifier.c_str()), SDL_FreeSurface);

			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexImage2D(GL_TEXTURE_2D, 0, 4, tex->w, tex->h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, tex->pixels);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			images[identifier] = texture;
		}
		return images[identifier];
	}

	virtual boost::shared_ptr<tileset_interface> gettileset(std::string identifier)
	{
		return tileset;
	}

	virtual boost::shared_ptr<mapdesc_interface> getmapdesc(std::string identifier)
	{
		return mapdesc;
	}

	virtual boost::shared_ptr<font_interface> getfont(std::string identifier)
	{
		return font;
	}
};

int main(int argc, char* argv[])
{
	if (initialize() != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	boost::shared_ptr<myresources> dirres(new myresources());
	boost::shared_ptr<mapdesc_interface> mapd = dirres->getmapdesc("");
	boost::shared_ptr<font_interface> font = dirres->getfont("");

	boost::shared_ptr<tilemapscene> tms(new tilemapscene(dirres, mapd, font));
	run(tms);

    return EXIT_SUCCESS;
}
