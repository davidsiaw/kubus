#include <stdio.h>
#include <stdlib.h>
#include <sdl.h>
#include "app.h"
#include "params.h"

int screenWidth = 1280;
int screenHeight = 1024;

int main(int argc, char* argv[])
{
    Controller* c = new Controller(argc, argv);
    App theApp(c);
    return theApp.OnExecute();
}
