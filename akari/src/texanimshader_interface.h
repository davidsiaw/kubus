#ifndef TEXANIMSHADER_INTERFACE_H
#define TEXANIMSHADER_INTERFACE_H

#include <GL/glew.h>
#include "shader_interface.h"

class texanimshader_interface : public shader_interface
{
public:
	virtual GLuint gettile_attribute()=0;
	virtual GLuint gettilenum_attribute()=0;
	virtual GLuint gettexcoord_attribute()=0;

	virtual void settransparency_uniform(GLfloat transp)=0;
	virtual void setactivetile_uniform(GLfloat activetile)=0;
	virtual void sethastexture_uniform(bool hastexture)=0;
	virtual void settexture_uniform(GLuint tex)=0;
};

#endif // TEXANIMSHADER_INTERFACE_H
