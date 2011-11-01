#ifndef WORLDSCENE_H
#define WORLDSCENE_H

#include <sdl.h>
#include <gl/glew.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "scene.h"
#include "world.h"

class WorldScene : public Scene
{
    World world;
    GLdouble eyeX, eyeY, eyeZ;
    GLdouble centerX, centerY, centerZ;
    GLdouble upX, upY, upZ;

    GLdouble angle;
    GLuint dispList;
    double vertAngle;

    bool worldChanged;

    GLdouble foX,foY;
    GLdouble stX,stY;

public:
    WorldScene();
    ~WorldScene();
	virtual void OnInit();
    virtual void OnRender();
    virtual void OnEvent(SDL_Event* Event);
    virtual void OnLoop();
};

#endif // WORLDSCENE_H
