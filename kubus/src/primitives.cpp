#include "primitives.h"

Quad MakeXYPlaneQuad(float x, float y, float width, float height)
{
	Quad q = {{
		{{x,      y,       0}, {255,0,    0,255}, {0.0f,1.0f}, 0.0f, 1.0f},
		{{x+width,y,       0}, {0,  255,  0,255}, {1.0f,1.0f}, 0.0f, 1.0f},
		{{x+width,y+height,0}, {0,  0,  255,255}, {1.0f,0.0f}, 0.0f, 1.0f},
		{{x,      y+height,0}, {255,255,255,255}, {0.0f,0.0f}, 0.0f, 1.0f}
	}};

	return q;
}

std::pair<Triangle, Triangle> QuadToTriangle(Quad q)
{
	Triangle t1;
	t1.e[0] = q.e[0];
	t1.e[1] = q.e[1];
	t1.e[2] = q.e[2];
	
	Triangle t2;
	t2.e[0] = q.e[2];
	t2.e[1] = q.e[3];
	t2.e[2] = q.e[0];

	return std::pair<Triangle, Triangle>(t1,t2);
}