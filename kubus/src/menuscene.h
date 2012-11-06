#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "scene.h"

class MenuScene : IMPLEMENTS Scene
{
public:
    MenuScene();
    virtual ~MenuScene();
	virtual void OnInit();
    virtual void OnRender();
    virtual void OnEvent(SDL_Event* Event);
    virtual void OnLoop();
	virtual bool IsComplete();
};

#endif // MENUSCENE_H
