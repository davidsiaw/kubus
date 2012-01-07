#include "directoryresources.h"
#include "SDL_image.h"


DirectoryResources::DirectoryResources(std::string path)
{
	this->path = path;
}

DirectoryResources::~DirectoryResources()
{
}

SDL_Surface* DirectoryResources::GetImage(std::string filename)
{
	SurfaceCache::iterator elem = images.find(filename);
	if (elem == images.end())
	{
		images[filename] = IMG_Load((path + filename).c_str());
	}
	return images[filename];
}
