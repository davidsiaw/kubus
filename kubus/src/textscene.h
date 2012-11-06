#ifndef TEXTSCENE_H
#define TEXTSCENE_H


#include <sdl.h>
#include <gl/glew.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "scene.h"
#include "vertexbuffer.h"

class TextScene : IMPLEMENTS Scene
{

public:
    TextScene();
    ~TextScene();
	
	virtual void OnInit();
    virtual void OnRender();
    virtual void OnEvent(SDL_Event* Event);
    virtual void OnLoop();
	virtual bool IsComplete();
};

#endif // TEXTSCENE_H
