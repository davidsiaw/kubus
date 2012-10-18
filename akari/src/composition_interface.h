#ifndef COMPOSITION_INTERFACE_H
#define COMPOSITION_INTERFACE_H

#include <GL/glew.h>

class composition_interface
{
public:
	composition_interface() { }
	virtual ~composition_interface() { }
	virtual void* Buffer() = 0;
	virtual size_t BufferSizeInBytes() const = 0;
	virtual GLenum PrimitiveType() const = 0;
	virtual GLuint ObjectCount() const = 0;
	virtual GLuint ElementsPerObject() const = 0;
	virtual bool UsesTexture() const = 0;
	virtual GLuint Texture() = 0;
};

#endif // COMPOSITION_INTERFACE_H
