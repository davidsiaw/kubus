#ifndef COMPOSITION_H
#define COMPOSITION_H

#include "definitions.h"
#include "GL/glew.h"

INTERFACE Composition
{
public:
	Composition() { }
	virtual ~Composition() { }
	virtual void* Buffer() = 0;
	virtual size_t BufferSizeInBytes() const = 0;
	virtual GLenum PrimitiveType() const = 0;
	virtual GLuint ObjectCount() const = 0;
	virtual GLuint ElementsPerObject() const = 0;
	virtual bool UsesTexture() const = 0;
	virtual SDL_Surface* Texture() = 0;
};

#endif // COMPOSITION_H
