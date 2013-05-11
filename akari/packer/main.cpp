#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "pngfuncs.h"
#include "../src/charmapinfo.h"

SDL_Surface* CreateSurface(int width, int height)
{
    Uint32 rmask, gmask, bmask, amask;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
    
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    return SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32,
                                   rmask, gmask, bmask, amask);
}

int main(int argc, char** argv)
{
	/* Initializing video subsystem */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		exit (-1);
	}
	
	int totalWidth=0;
	int height=0;
	std::vector<SDL_Surface*> surfaces;
	for (int i=1; i<argc; i++)
	{
		SDL_Surface *surf = IMG_Load(argv[i]);
		SDL_SetAlpha(surf, 0, 0xff);
		std::cout << "Processing: " << argv[i] << std::endl;
		surfaces.push_back(surf);
		totalWidth += surf->w;
		if (surf->h > height)
		{
			height = surf->h;
		}
	}
	
	FILE* fp = fopen("output.charmap", "w");
	
	int numSurfaces = surfaces.size();
	fwrite(&numSurfaces, sizeof(int), 1, fp);
	
	SDL_Surface* superSurface = CreateSurface(totalWidth, height);
	int x=0;
	for (size_t i=0; i<surfaces.size(); i++)
	{
		SDL_Rect dstRect;
		dstRect.x = x;
		dstRect.y = 0;
		dstRect.w = surfaces[i]->w;
		dstRect.h = surfaces[i]->h;
		
		int a = SDL_BlitSurface(surfaces[i], NULL, superSurface, &dstRect);
		std::cout << a << std::endl;
		x += surfaces[i]->w;
		
		charmapinformation info;
		info.numtiles = 4;
		
		info.xpixsize = dstRect.w/info.numtiles;
		info.ypixsize = dstRect.h/info.numtiles;
		info.xsize = (float)info.xpixsize / (float)totalWidth;
		info.ysize = (float)info.ypixsize / (float)height;
		info.xstart = (float)dstRect.x / (float)totalWidth;
		info.ystart = 0;
		info.xoffset = (-info.xpixsize+32)/2;
		info.yoffset = (-info.ypixsize+32)/2;
		
		fwrite(&info, sizeof(charmapinformation), 1, fp);
		
	}
	png_save_surface("output.png", superSurface);
	
	fclose(fp);
	return EXIT_SUCCESS;
}
