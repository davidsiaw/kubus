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
	cache<std::tr1::shared_ptr<tileset_interface>> tilesets;
	cache<std::tr1::shared_ptr<font_interface>> fonts;
	cache<std::tr1::shared_ptr<objectset_interface>> charmaps;
	cache<GLuint> images;
	std::string directory;

public:
	directoryresources(std::string directory) : directory(directory) {}
	
	virtual GLuint getimage(std::string identifier)
	{
		return images.get(directory + identifier, [&]()->GLuint
		{
			glActiveTexture(GL_TEXTURE0);
			std::tr1::shared_ptr<SDL_Surface> tex(IMG_Load((directory + identifier).c_str()), SDL_FreeSurface);

			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexImage2D(GL_TEXTURE_2D, 0, 4, tex->w, tex->h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, tex->pixels);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			return texture;
		});
	}

	virtual std::tr1::shared_ptr<tileset_interface> gettileset(std::string identifier)
	{
		return tilesets.get(directory + identifier, [&]()->std::tr1::shared_ptr<tileset_interface>
		{
			FILE* basictilesfile = fopen((directory + identifier + ".basictiles").c_str(), "rb");
			FILE* tilesfile = fopen((directory + identifier + ".tiles").c_str(), "rb");
			return std::tr1::shared_ptr<tileset_interface>(new btileset(basictilesfile, tilesfile, identifier + ".png"));
			fclose(basictilesfile);
			fclose(tilesfile);
		});
	}

	virtual std::tr1::shared_ptr<font_interface> getfont(std::string identifier)
	{
		return fonts.get(directory + identifier, [&]()->std::tr1::shared_ptr<font_interface>
		{
			FILE* fontfile = fopen((directory + identifier + ".font").c_str(), "rb");
			return std::tr1::shared_ptr<font_interface>(new bitmapfont(fontfile, identifier + ".png"));
			fclose(fontfile);
		});
	}

	virtual std::tr1::shared_ptr<objectset_interface> getcharmap(std::string identifier)
	{
		return charmaps.get(directory + identifier, [&]()->std::tr1::shared_ptr<objectset_interface>
		{
			std::vector<charmapinformation> charmapinfo;
			FILE* fp = fopen((directory + identifier + ".charmap").c_str(), "rb");
			int numcharacters;
			fread(&numcharacters, sizeof(int), 1, fp);
			for (int i=0; i<numcharacters; i++)
			{
				charmapinformation cmi;
				fread(&cmi, sizeof(charmapinformation), 1, fp);
				charmapinfo.push_back(cmi);
			}
			fclose(fp);

			return std::tr1::shared_ptr<objectset_interface>(new mobilecharacterset(directory + identifier, charmapinfo));
		});
	}
};

#endif // DIRECTORYRESOURCES_H
