#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "SDL.h"
#include "GL/glew.h"

#pragma pack(push,1)
struct Vertex
{
    GLfloat x,y,z;
};

struct Color
{
    uint8_t r,g,b,a;
};

struct TexCoord
{
	GLfloat x,y;
};

struct Element
{
	Vertex v;
	Color c;
	TexCoord t;
	float mark;
};

struct Triangle
{
    Element e[3];
};

struct Quad
{
    Element e[4];
};

#pragma pack(pop)

Quad MakeXYPlaneQuad(float x, float y, float width, float height);


#endif
