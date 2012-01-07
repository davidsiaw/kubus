#ifndef RESOURCECONTAINER_H
#define RESOURCECONTAINER_H

#include <string>
#include <SDL.h>

class ResourceContainer
{
public:
        ResourceContainer() { }
        virtual ~ResourceContainer() { }
        virtual SDL_Surface* GetImage(std::string filename) = 0;
};

#endif // RESOURCECONTAINER_H
