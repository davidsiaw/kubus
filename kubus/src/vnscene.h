#ifndef VNSCENE_H
#define VNSCENE_H

#include <sdl.h>
#include <gl/glew.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "scene.h"
#include "vertexbuffer.h"

class VNScene : public Scene
{
	VertexBuffer* vbo;

public:
    VNScene();
    ~VNScene();
	
	virtual void OnInit();
    virtual void OnRender();
    virtual void OnEvent(SDL_Event* Event);
    virtual void OnLoop();
};

#endif // VNSCENE_H
