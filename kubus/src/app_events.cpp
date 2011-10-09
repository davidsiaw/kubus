#include "app.h"

void App::OnEvent(Scene* scene, SDL_Event* event)
{
    scene->OnEvent(event);
    if(event->type == SDL_QUIT)
    {
        running = false;
    }
}
