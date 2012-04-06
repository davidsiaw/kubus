#ifndef MULTIPLETEXTUREDQUADCOMPOSITION_H
#define MULTIPLETEXTUREDQUADCOMPOSITION_H

#include "primitives.h"
#include "array.h"
#include "composition.h"
#include <map>
#include "supertexture.h"

class MultipleTexturedQuadComposition : IMPLEMENTS Composition
{
	typedef std::map<SDL_Surface*, std::vector<size_t>> qmap;
	
	qmap surfToQuadMap;
	std::vector<Quad> quads;
	std::vector<SDL_Surface*> surfaces;
	SuperTextureInfo texture;
	SuperTexture supertexturer;

public:
	MultipleTexturedQuadComposition()
	{
	}
	
	~MultipleTexturedQuadComposition()
	{
	}

	void Add(Quad* q, SDL_Surface* img)
	{
		quads.push_back(*q);

		if (surfToQuadMap.find(img) == surfToQuadMap.end())
		{
			surfaces.push_back(img);
		}
		surfToQuadMap[img].push_back(quads.size()-1);

		supertexturer.Add(img);
	}

	class TooManyImagesException{};

	void ArrangeLightMap()
	{
		texture = supertexturer.CreateSuperTexture();

		SuperTextureInfo tex = texture;
		std::vector<Quad>& quads = this->quads;

		std::for_each(surfToQuadMap.begin(), surfToQuadMap.end(), 
			[&](std::pair<SDL_Surface*, std::vector<size_t>> kvpair)
			{
				auto coords = tex[kvpair.first];
				std::vector<Quad>& thisquads = quads;

				std::for_each(kvpair.second.begin(), kvpair.second.end(), 
					[&](size_t index)
					{
						for (int i=0;i<4;i++) {
							thisquads[index].e[i].t = coords[i];
						}
					});
			});
	}
	
	virtual void* Buffer()
	{	
		if (texture.GetSuperTextureSurface() == NULL)
		{
			ArrangeLightMap();
		}

		return &quads[0];
	}

	virtual size_t BufferSizeInBytes() const
	{
		return quads.size() * sizeof(Quad);
	}

	virtual GLenum PrimitiveType() const
	{
		return GL_QUADS;
	}

	virtual GLuint ObjectCount() const
	{
		return quads.size();
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
		if (texture.GetSuperTextureSurface() == NULL)
		{
			ArrangeLightMap();
		}

		return texture.GetSuperTextureSurface();
	}

	void DebugDumpLightMap(const char* file)
	{
		SDL_SaveBMP(texture.GetSuperTextureSurface(), file);
	}

};

#endif // MULTIPLETEXTUREDQUADCOMPOSITION_H
