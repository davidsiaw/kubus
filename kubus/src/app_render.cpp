#include "app.h"

void App::OnRender(Scene* scene)
{
    scene->OnRender();
    SDL_GL_SwapBuffers();
}
