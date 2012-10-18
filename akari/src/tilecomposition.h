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
		boost::shared_ptr<resources_interface> resources, 
		boost::shared_ptr<mapdesc_interface> mapdesc)
	{
		auto tileset = resources->gettileset(mapdesc->gettilesetname());
		texturemap = resources->getimage(tileset->gettexturemap());

		for (int tilex=0;tilex<w;tilex++) 
		{
			for (int tiley=0;tiley<h;tiley++) 
			{
				auto frame = tileset->getframeforid(tilex + x, tiley + y, [mapdesc](int x, int y){return mapdesc->getid(x,y);});

				quad q = MakeQuad((tilex + x) * 32, (tiley + y) * 32, 32, 32);
				q.e[0].t = frame.startframecoord[0];
				q.e[1].t = frame.startframecoord[1];
				q.e[2].t = frame.startframecoord[2];
				q.e[3].t = frame.startframecoord[3];
				q.e[0].tileOffset = frame.width;
				q.e[1].tileOffset = frame.width;
				q.e[2].tileOffset = frame.width;
				q.e[3].tileOffset = frame.width;
				q.e[0].numtiles = frame.numframes;
				q.e[1].numtiles = frame.numframes;
				q.e[2].numtiles = frame.numframes;
				q.e[3].numtiles = frame.numframes;
				quads.push_back(q);
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
