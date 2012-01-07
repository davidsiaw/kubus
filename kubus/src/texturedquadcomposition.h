#ifndef TEXTUREDQUADCOMPOSITION_H
#define TEXTUREDQUADCOMPOSITION_H

#include "primitives.h"
#include "array.h"
#include "composition.h"

class TexturedQuadComposition : IMPLEMENTS Composition
{
	Array<Quad>* quads;
	SDL_Surface* texture;

public:
	TexturedQuadComposition(SDL_Surface* tex)
	{
		quads = new Array<Quad>();
		texture = tex;
	}
	
	~TexturedQuadComposition()
	{
		delete quads;
	}

	void Add(Quad* q)
	{
		quads->Insert(*q);
	}
	
	virtual void* Buffer()
	{
		return (void*)quads->GetBuffer();
	}

	virtual size_t BufferSizeInBytes() const
	{
		return quads->Count() * sizeof(Quad);
	}

	virtual GLenum PrimitiveType() const
	{
		return GL_QUADS;
	}

	virtual GLuint ObjectCount() const
	{
		return quads->Count();
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
		return texture;
	}

};

#endif // TEXTUREDQUADCOMPOSITION_H
