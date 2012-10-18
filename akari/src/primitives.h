#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "SDL.h"
#include "GL/glew.h"
#include <algorithm>

#pragma pack(push,1)
struct vertex
{
    GLfloat x,y,z;
};

struct color
{
    uint8_t r,g,b,a;
};

struct texcoord
{
	GLfloat x,y;
};

struct element
{
	vertex v;
	color c;
	texcoord t;
	float tileOffset;	// The width of each tile
	float numtiles;		// Number of tiles in texture
};

struct triangle
{
    element e[3];
};

struct quad
{
    element e[4];
};

#pragma pack(pop)

quad MakeQuad(float x, float y, float width, float height);
std::pair<triangle, triangle> QuadToTriangle(quad q);

#endif
