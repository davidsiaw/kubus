#ifndef INTERMISSIONSCENE_H
#define INTERMISSIONSCENE_H


#include <sdl.h>
#include <gl/glew.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "scene.h"
#include "vertexbuffer.h"

class IntermissionScene : IMPLEMENTS Scene
{
	VertexBuffer* vbo;
	SDL_Surface* image;
	int fadeInTime,stickTime,fadeOutTime;
	int mode, currentTime;

public:
    IntermissionScene(SDL_Surface* image, int fadeInTime = 2, int stickTime = 3, int fadeOutTime = 2);
    ~IntermissionScene();
	
	virtual void OnInit();
    virtual void OnRender();
    virtual void OnEvent(SDL_Event* Event);
    virtual void OnLoop();
	virtual bool IsComplete();
};

#endif // INTERMISSIONSCENE_H
