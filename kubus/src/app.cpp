#include "app.h"

App::App(Controller* in_controller)
:
controller(in_controller),
running(true),
surfDisplay(NULL)
{
    this->running = true;
    this->controller = controller;
}

int App::OnExecute()
{
    if(OnInit() == false)
    {
        return -1;
    }

	controller->Initialize();

    SDL_Event Event;
    while(running)
    {
        Scene* scene = controller->GetCurrentScene();
		if (scene == NULL)
		{
			break;
		}

        if(SDL_PollEvent(&Event))
        {
            OnEvent(scene, &Event);
        }

        OnLoop(scene);
        OnRender(scene);
    }

    OnCleanup();

    return 0;
}
