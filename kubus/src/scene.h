#ifndef SCENE_H
#define SCENE_H

#include <sdl.h>

class Scene
{
public:
        Scene() { }
        virtual ~Scene() { }
        virtual void OnRender() = 0;
        virtual void OnEvent(SDL_Event* Event) = 0;
        virtual void OnLoop() = 0;
};

#endif // SCENE_H
