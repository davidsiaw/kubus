#ifndef SHADER_INTERFACE_H
#define SHADER_INTERFACE_H

#include <GL/glew.h>

class shader_interface
{
public:
	virtual GLuint getprogram()=0;

	virtual GLuint getposition_attribute()=0;
	virtual GLuint getcolor_attribute()=0;

};

#endif // SHADER_INTERFACE_H
