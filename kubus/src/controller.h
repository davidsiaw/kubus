#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "vnscene.h"

class Controller
{
	/* Scene declarations */
    VNScene* ws;

public:
    Controller(int , char**)
    :
	ws(new VNScene())
    {
    }

	void Initialize() 
	{
		ws->OnInit();
	}

	/* Game state lies here */
    Scene* GetCurrentScene()
    {
        return ws;
    }
};

#endif // CONTROLLER_H
