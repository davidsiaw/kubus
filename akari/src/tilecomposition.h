#ifndef TILECOMPOSITION_H
#define TILECOMPOSITION_H

#include <vector>
#include "composition_interface.h"
#include "primitives.h"
#include "GL/glew.h"
#include "resources_interface.h"

class tilecomposition : public composition_interface
{
	std::vector<quad> quads;
	GLuint texturemap;

public:
	tilecomposition(
		int x, 
		int y, 
		unsigned int w, 
		unsigned int h,
		std::tr1::shared_ptr<resources_interface> resources, 
		std::tr1::shared_ptr<mapdesc_interface> mapdesc)
	{
		auto tileset = resources->gettileset(mapdesc->gettilesetname());
		texturemap = resources->getimage(tileset->gettexturemap());

		for (int tilex=0;tilex<w;tilex++) 
		{
			for (int tiley=0;tiley<h;tiley++) 
			{
				auto frame = tileset->getframeforid(tilex + x, tiley + y, [mapdesc](int x, int y){return mapdesc->getid(x,y);});

				for (int i=0;i<std::get<0>(frame);i++)
				{
					quads.push_back(std::get<1>(frame)[i]);
				}

			}
		}
	}

	~tilecomposition()
	{
	}

	virtual void* Buffer()
	{
		return &quads[0];
	}

	virtual size_t BufferSizeInBytes() const
	{
		return quads.size() * sizeof(quad);
	}

	virtual GLenum PrimitiveType() const
	{
		return GL_QUADS;
	}

	virtual GLuint ObjectCount() const
	{
		return quads.size();
	}

	virtual GLuint ElementsPerObject() const
	{
		return 4;
	}

	virtual bool UsesTexture() const
	{
		return true;
	}

	virtual GLuint Texture()
	{
		return texturemap;
	}

};

#endif //TILECOMPOSITION_H
