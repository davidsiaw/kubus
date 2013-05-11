#ifndef DIRECTORYRESOURCES_H
#define DIRECTORYRESOURCES_H

#include <SDL_image.h>
#include "resources_interface.h"
#include "bitmapfont.h"
#include "btileset.h"
#include "mobilecharacterset.h"
#include "cache.h"

class directoryresources : public resources_interface
{
	cache<boost::shared_ptr<tileset_interface>> tilesets;
	cache<boost::shared_ptr<font_interface>> fonts;
	cache<boost::shared_ptr<objectset_interface>> charmaps;
	cache<GLuint> images;
	std::string directory;

public:
	directoryresources(std::string directory) : directory(directory) {}
	
	virtual GLuint getimage(std::string identifier)
	{
		return images.get(directory + identifier, [&]()->GLuint
		{
			glActiveTexture(GL_TEXTURE0);
			boost::shared_ptr<SDL_Surface> tex(IMG_Load((directory + identifier).c_str()), SDL_FreeSurface);

			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexImage2D(GL_TEXTURE_2D, 0, 4, tex->w, tex->h, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, tex->pixels);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			return texture;
		});
	}

	virtual boost::shared_ptr<tileset_interface> gettileset(std::string identifier)
	{
		return tilesets.get(directory + identifier, [&]()->boost::shared_ptr<tileset_interface>
		{
			FILE* basictilesfile = fopen((directory + identifier + ".basictiles").c_str(), "rb");
			FILE* tilesfile = fopen((directory + identifier + ".tiles").c_str(), "rb");
			return boost::shared_ptr<tileset_interface>(new btileset(basictilesfile, tilesfile, identifier + ".png"));
			fclose(basictilesfile);
			fclose(tilesfile);
		});
	}

	virtual boost::shared_ptr<font_interface> getfont(std::string identifier)
	{
		return fonts.get(directory + identifier, [&]()->boost::shared_ptr<font_interface>
		{
			FILE* fontfile = fopen((directory + identifier + ".font").c_str(), "rb");
			return boost::shared_ptr<font_interface>(new bitmapfont(fontfile, identifier + ".png"));
			fclose(fontfile);
		});
	}

	virtual boost::shared_ptr<objectset_interface> getcharmap(std::string identifier)
	{
		return charmaps.get(directory + identifier, [&]()->boost::shared_ptr<objectset_interface>
		{
			return boost::shared_ptr<objectset_interface>(new mobilecharacterset(directory + identifier));
		});
	}
};

#endif // DIRECTORYRESOURCES_H
