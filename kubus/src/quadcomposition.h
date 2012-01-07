#ifndef QUADCOMPOSITION_H
#define QUADCOMPOSITION_H

#include "primitives.h"
#include "array.h"
#include "composition.h"

class QuadComposition : IMPLEMENTS Composition
{
	Array<Quad> quads;

public:
	QuadComposition()
	{
		quads = Array<Quad>();
	}
	
	~QuadComposition()
	{
	}
	
	void Add(Quad* q)
	{
		quads.Insert(*q);
	}

	virtual void* Buffer()
	{
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
		return false;
	}
	
	virtual SDL_Surface* Texture()
	{
		return NULL;
	}

};

#endif // QUADCOMPOSITION_H
