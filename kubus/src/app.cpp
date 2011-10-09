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

    SDL_Event Event;
    while(running)
    {
        Scene* scene = controller->GetCurrentScene();
        while(SDL_PollEvent(&Event))
        {
            OnEvent(scene, &Event);
        }

        OnLoop(scene);
        OnRender(scene);
    }

    OnCleanup();

    return 0;
}
