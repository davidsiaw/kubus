#ifndef MULTIPLETEXTUREDQUADCOMPOSITION_H
#define MULTIPLETEXTUREDQUADCOMPOSITION_H

#include "primitives.h"
#include "array.h"
#include "composition.h"
#include "rbsptree.h"

#include <map>

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

class MultipleTexturedQuadComposition : IMPLEMENTS Composition
{

	typedef std::map<SDL_Surface*, Array<size_t>*> qmap;
	typedef RBSPNode<SDL_Surface*, MultipleTexturedQuadComposition*> MTQRBSP;
	
	qmap surfToQuadMap;
	Array<Quad> quads;
	Array<SDL_Surface*> surfaces;
	SDL_Surface* texture;

public:
	MultipleTexturedQuadComposition()
	{
		texture = NULL;
	}
	
	~MultipleTexturedQuadComposition()
	{
		if (texture != NULL)
		{
			SDL_FreeSurface(texture);
		}
	}

	void Add(Quad* q, SDL_Surface* img)
	{
		quads.Insert(*q);

		if (surfToQuadMap.find(img) == surfToQuadMap.end())
		{
			surfaces.Insert(img);
			surfToQuadMap[img] = new Array<size_t>();
		}
		surfToQuadMap[img]->Insert(quads.Count()-1);
		
		// a texture's nullness shows it has changed
		if (texture != NULL)
		{
			SDL_FreeSurface(texture);
			texture = NULL;
		}
	}


	static int CompareSurfaceArea(const SDL_Surface** b, const SDL_Surface** a) 
	{
		int sizea = max((*a)->w, (*a)->h);
		int sizeb = max((*b)->w, (*b)->h);

		return sizea - sizeb;
	}

	static void SetSurface (FRectangle rect, SDL_Surface* data, MultipleTexturedQuadComposition* self)
	{
		int size = self->texture->w;

		// print the texture on the supertexture
		SDL_Rect r;
		r.x = (Sint16)rect.x1;
		r.y = (Sint16)rect.y1;
		r.w = (Sint16)(rect.x2-rect.x1);
		r.h = (Sint16)(rect.y2-rect.y1);
		
		SDL_SetAlpha(data, 0, SDL_ALPHA_OPAQUE);
		SDL_BlitSurface(data, &data->clip_rect, self->texture, &r);

		// update the texcoords
		const size_t* indexes = self->surfToQuadMap[data]->GetBuffer();
		size_t count = self->surfToQuadMap[data]->Count();
		Quad* quads = (Quad*)self->quads.GetBuffer();
		
		for (size_t i=0; i<count; i++)
		{
			quads[indexes[i]].e[0].t.x = rect.x1/size;
			quads[indexes[i]].e[0].t.y = rect.y2/size;

			quads[indexes[i]].e[1].t.x = rect.x2/size;
			quads[indexes[i]].e[1].t.y = rect.y2/size;

			quads[indexes[i]].e[2].t.x = rect.x2/size;
			quads[indexes[i]].e[2].t.y = rect.y1/size;

			quads[indexes[i]].e[3].t.x = rect.x1/size;
			quads[indexes[i]].e[3].t.y = rect.y1/size;
		}

	}

	class TooManyImagesException{};

	void ArrangeLightMap()
	{
		for(int size=256; size < 8192; size*=2)
		{
			FRectangle r;
			r.x1 = 0;
			r.x2 = (float)size;
			r.y1 = 0;
			r.y2 = (float)size;
			
			bool bigenough = true;
			MTQRBSP* rbsp = new MTQRBSP(r);
			
			// First sort by size
			surfaces.Sort((Array<SDL_Surface*>::comparer)CompareSurfaceArea);

			SDL_Surface* const* surfaceArray = surfaces.GetBuffer();

			// Now insert
			for(size_t i=0; i<surfaces.Count(); i++)
			{
				FRectangle rect = {0,0,(float)surfaceArray[i]->w,(float)surfaceArray[i]->h};
				if ( !rbsp->Insert(rect, surfaceArray[i]) )
				{
					bigenough = false;
					break;
				}
			}

			if(bigenough)
			{
				texture = SDL_CreateRGBSurface(
					SDL_HWSURFACE | SDL_SRCALPHA, size, size, 32,
					rmask, gmask, bmask, amask);

				rbsp->RetrieveRectangles(SetSurface, this);
				delete rbsp;
				return;
			}
		}

		throw TooManyImagesException();
	}
	
	virtual void* Buffer()
	{	
		if (texture == NULL)
		{
			ArrangeLightMap();
		}

		return (void*)quads.GetBuffer();
	}

	virtual size_t BufferSizeInBytes() const
	{
		return quads.Count() * sizeof(Quad);
	}

	virtual GLenum PrimitiveType() const
	{
		return GL_QUADS;
	}

	virtual GLuint ObjectCount() const
	{
		return quads.Count();
	}

	virtual GLuint ElementsPerObject() const
	{
		return 4;
	}
	
	virtual bool UsesTexture() const
	{
		return true;
	}
	
	virtual SDL_Surface* Texture()
	{
		if (texture == NULL)
		{
			ArrangeLightMap();
		}

		return texture;
	}

	void DebugDumpLightMap(const char* file)
	{
		SDL_SaveBMP(texture, file);
	}

};

#endif // MULTIPLETEXTUREDQUADCOMPOSITION_H
