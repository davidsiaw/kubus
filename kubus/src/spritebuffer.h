#ifndef TILEBUFFER_H
#define TILEBUFFER_H

#include <SDL.h>
#include <vector>
#include <algorithm>
#include <boost\smart_ptr.hpp>
#include <boost\function.hpp>
#include "vertexbuffer.h"
#include "composition.h"
#include "primitives.h"
#include "supertexture.h"

class SpriteBuffer;

class Character
{
	SpriteBuffer* buf;
	SDL_Surface* surf;
	int x,y;
	int curmode;
	size_t index;

public:
	Character(SDL_Surface* surf, SpriteBuffer* buf, size_t index) :
	  buf(buf), surf(surf), x(0), y(0), curmode(0), index(index)
	{ }

	void SetPosition(int x, int y)
	{
		this->x = x;
		this->y = y;
		buf->UpdateCharacter(this);
	}

	void SetMode(int mode)
	{
		curmode = mode;
		buf->UpdateCharacter(this);
	}

	size_t GetIndex() const 
	{
		return index;
	}

	int X() const
	{
		return x;
	}

	int Y() const 
	{
		return y;
	}

	SDL_Surface* GetSurface()
	{
		return surf;
	}
};

class SpriteBuffer : IMPLEMENTS Composition
{
	boost::shared_array<VertexBuffer> vbuf;
	
	std::vector<Character> characters;
	std::vector<Quad> characterQuads;

	const SuperTextureInfo& sti;

public:
	SpriteBuffer(const SuperTextureInfo& sti) : sti(sti)
	{
	}

	virtual ~SpriteBuffer() 
	{
	}

	Character* CreateCharacter(SDL_Surface* surf)
	{
		vbuf = boost::shared_array<VertexBuffer>();
		Character c(surf, this, characters.size());
		characters.push_back(c);
		characterQuads.push_back(MakeXYPlaneQuad(0,0,surf->w,surf->h));
		return &characters.back();
	}

	void UpdateCharacter(Character* character)
	{
		if (vbuf != NULL)
		{
			Quad& q = characterQuads[character->GetIndex()];
			SDL_Surface* surf = character->GetSurface();
			TexInfo& info = sti[surf];

			q.e[0].v.x = character->X();
			q.e[0].v.y = character->Y();
			
			q.e[1].v.x = character->X() + surf->w;
			q.e[1].v.y = character->Y();
			
			q.e[2].v.x = character->X() + surf->w;
			q.e[2].v.y = character->Y() + surf->h;
			
			q.e[3].v.x = character->X();
			q.e[3].v.y = character->Y() + surf->h;

			
		}
	}

	void Render()
	{
		if (vbuf == NULL)
		{
			vbuf = boost::shared_array<VertexBuffer>(new VertexBuffer(this));
		}
	}

	virtual void* Buffer() 
	{
	}

	virtual size_t BufferSizeInBytes() const 
	{
	}

	virtual GLenum PrimitiveType() const 
	{
	}

	virtual GLuint ObjectCount() const 
	{
	}

	virtual GLuint ElementsPerObject() const 
	{ 
	}

	virtual bool UsesTexture() const 
	{
	}

	virtual SDL_Surface* Texture() 
	{
	}
};

#endif // TILEBUFFER_H
