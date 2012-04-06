#ifndef SUPERTEXTURE_H
#define SUPERTEXTURE_H

#include <SDL.h>
#include <map>
#include <vector>
#include <algorithm>
#include <tuple>
#include <boost\smart_ptr.hpp>
#include "rbsptree.h"
#include "primitives.h"

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define rmask 0xff000000
#define gmask 0x00ff0000
#define bmask 0x0000ff00
#define amask 0x000000ff
#else
#define rmask 0x000000ff
#define gmask 0x0000ff00
#define bmask 0x00ff0000
#define amask 0xff000000
#endif


class SuperTextureInfo
{
	typedef std::pair<boost::shared_ptr<SDL_Surface>, std::map<SDL_Surface*, std::vector<TexCoord>>> TheInfo;

	boost::shared_ptr<TheInfo> info;
public:

	SuperTextureInfo() : info()
	{
	}

	SuperTextureInfo(int size) : info(new TheInfo)
	{
		info->first = boost::shared_ptr<SDL_Surface>(
			SDL_CreateRGBSurface(
				SDL_HWSURFACE | SDL_SRCALPHA, 
				size, 
				size, 
				32,
				rmask, gmask, bmask, amask), 
			SDL_FreeSurface);
	}

	std::vector<TexCoord>& operator[] (SDL_Surface* surface) 
	{
		return info->second[surface];
	}

	SDL_Surface* GetSuperTextureSurface() const
	{
		if (info == NULL)
		{
			return NULL;
		}
		return info->first.get();
	}
};

class SuperTexture
{
	typedef RBSPNode<SDL_Surface*, SuperTextureInfo&> TextureTree;

	std::vector<SDL_Surface*> images;

public:
	SuperTexture() : images()
	{
	}

	void Add(SDL_Surface* img)
	{
		images.push_back(img);
	}
	
	class TooManyImagesException{};

	static void SetSurface (FRectangle rect, SDL_Surface* data, SuperTextureInfo& info)
	{
		int size = info.GetSuperTextureSurface()->w;

		// print the texture on the supertexture
		SDL_Rect r;
		r.x = (Sint16)rect.x1;
		r.y = (Sint16)rect.y1;
		r.w = (Sint16)(rect.x2-rect.x1);
		r.h = (Sint16)(rect.y2-rect.y1);
		
		SDL_SetAlpha(data, 0, SDL_ALPHA_OPAQUE);
		SDL_BlitSurface(data, &data->clip_rect, info.GetSuperTextureSurface(), &r);

		std::vector<TexCoord> coords;
		TexCoord t1;
		TexCoord t2;
		TexCoord t3;
		TexCoord t4;

		t1.x = rect.x1/size;
		t1.y = rect.y2/size;

		t2.x = rect.x2/size;
		t2.y = rect.y2/size;
		
		t3.x = rect.x2/size;
		t3.y = rect.y1/size;
		
		t4.x = rect.x1/size;
		t4.y = rect.y1/size;

		coords.push_back(t1);
		coords.push_back(t2);
		coords.push_back(t3);
		coords.push_back(t4);
		
		info[data] = coords;
	}



	SuperTextureInfo CreateSuperTexture()
	{
		for(int size=256; size < 8192; size*=2)
		{
			FRectangle r;
			r.x1 = 0;
			r.x2 = (float)size;
			r.y1 = 0;
			r.y2 = (float)size;
			
			bool bigenough = true;
			TextureTree rbsp(r);
			
			// First sort by size
			std::sort(images.begin(), images.end(), [](SDL_Surface* a, SDL_Surface* b)
			{
				return std::max(a->w, a->h) < std::max(b->w, b->h);
			});

			SDL_Surface* const* surfaceArray = &images[0];

			// Now insert
			for(size_t i=0; i<images.size(); i++)
			{
				FRectangle rect = {0,0,(float)surfaceArray[i]->w,(float)surfaceArray[i]->h};
				if ( !rbsp.Insert(rect, surfaceArray[i]) )
				{
					bigenough = false;
					break;
				}
			}

			if(bigenough)
			{	
				SuperTextureInfo sfi(size);
				rbsp.RetrieveRectangles(SetSurface, sfi);
				return sfi;
			}
		}

		throw TooManyImagesException();
	}

	~SuperTexture()
	{
	}

};

#endif // SUPERTEXTURE_H
