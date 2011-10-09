#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "worldscene.h"

class Controller
{
    WorldScene* ws;
public:
    Controller(int , char**)
    :
    ws(new WorldScene())
    {
    }

    Scene* GetCurrentScene()
    {
        return ws;
    }
};

#endif // CONTROLLER_H
