#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "vnscene.h"
#include "worldscene.h"
#include "intermissionscene.h"
#include "params.h"
#include "script.h"
#include "textscene.h"

class Controller
{
	Script* script;
	Scene* scene;

public:
    Controller(int , char**)
    :
	script(NULL)
    {
    }

	void Initialize() 
	{
		script = new Script();

		scene = new VNScene();
		scene->OnInit();
	}

    Scene* GetCurrentScene()
    {
		//return scene;

		// run the script until it yields
		// the game.setscene function normally yields
		if (script->getCurrentScene() == NULL || script->getCurrentScene()->IsComplete())
		{
			script->Run();
		}

		// then send the current scene down to handle the app
		return script->getCurrentScene();
    }
};

#endif // CONTROLLER_H

