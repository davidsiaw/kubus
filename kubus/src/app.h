#ifndef APP_H
#define APP_H


#include "controller.h"

class App
{
    private:
        Controller* controller;
        bool running;
        SDL_Surface* surfDisplay;

    public:
        App(Controller* controller);
        int OnExecute();
        bool OnInit();
        void OnEvent(Scene* scene, SDL_Event* Event);
        void OnLoop(Scene* scene);
        void OnRender(Scene* scene);
        void OnCleanup();
};

#endif // APP_H
