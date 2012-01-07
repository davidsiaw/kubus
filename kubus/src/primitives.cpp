#include "primitives.h"

Quad MakeXYPlaneQuad(float x, float y, float width, float height)
{
	Quad q = {{
		{{x,      y,       0}, {255,0,    0,255}, {0.0f,1.0f}},
		{{x+width,y,       0}, {0,  255,  0,255}, {1.0f,1.0f}},
		{{x+width,y+height,0}, {0,  0,  255,255}, {1.0f,0.0f}},
		{{x,      y+height,0}, {255,255,255,255}, {0.0f,0.0f}}
	}};

	return q;
}
