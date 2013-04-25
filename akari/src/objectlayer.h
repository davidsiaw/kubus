#ifndef OBJECTLAYER_H
#define OBJECTLAYER_H

#include <vector>
#include <boost/shared_ptr.hpp>

#include "primitives.h"
#include "vertexbuffer.h"
#include "composition_interface.h"
#include "texanimshader_interface.h"
#include "object_interface.h"

class objectlayer
{	

	class objectcomposition : public composition_interface
	{
		std::vector<quad>& quads;
		GLuint texturemap;
	public:
		objectcomposition(GLuint texturemap, std::vector<quad>& quads)
			: texturemap(texturemap), quads(quads)
		{ }

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

	boost::shared_ptr<vertexbuffer> vbuf;
	boost::shared_ptr<resources_interface> res;
	boost::shared_ptr<texanimshader_interface> shader;
	boost::shared_ptr<objectset_interface> objects;

	std::vector<boost::shared_ptr<object_interface>> objectlist;
	std::vector<quad> quads;
	std::vector<int> freeids;

	quad emptyquad;

	int cameray;
	int camerax;

	int screenw;
	int screenh;

	void increasequadspace(int amount)
	{
		for (int i=0;i<amount;i++)
		{
			freeids.push_back(quads.size());
			quads.push_back(emptyquad);
			objectlist.push_back(boost::shared_ptr<object_interface>());
		}
		boost::shared_ptr<objectcomposition> composition(new objectcomposition(res->getimage(objects->gettexturemap()), quads));
		vbuf = boost::shared_ptr<vertexbuffer>(new vertexbuffer(shader, composition));
	}

public:
	objectlayer(boost::shared_ptr<texanimshader_interface> shader, boost::shared_ptr<resources_interface> res, boost::shared_ptr<objectset_interface> objects, int screenw, int screenh) 
		: objects(objects), res(res), shader(shader), screenw(screenw), screenh(screenh), camerax(0), cameray(0)
	{
		memset(&emptyquad, 0, sizeof(quad));
		increasequadspace(1);
	}

	void foreachobject(std::function<bool(boost::shared_ptr<object_interface>)> objects)
	{
		typedef std::vector<boost::shared_ptr<object_interface>>::iterator iterator;
		for (iterator i = objectlist.begin(); i != objectlist.end(); i++)
		{
			if (!objects(*i))
			{
				return;
			}
		}
	}

	void addobject(boost::shared_ptr<object_interface> obj)
	{
		if (obj->getid() != -1)
		{
		}

		if (freeids.size() == 0)
		{
			increasequadspace(quads.size());
		}

		int id = freeids.back();
		freeids.pop_back();
		quad q = obj->getcurrentquad();

		objectlist[id] = obj;
		quads[id] = q;
		vbuf->ChangeQuadAt(id, q);
		obj->setid(id);
	}

	void removeobject(boost::shared_ptr<object_interface> obj)
	{
		int id = obj->getid();
		obj->setid(-1);
		freeids.push_back(id);
		quads[id] = emptyquad;
		vbuf->ChangeQuadAt(id, emptyquad);
		objectlist[id] = boost::shared_ptr<object_interface>();
	}

	void updateobject(boost::shared_ptr<object_interface> obj)
	{
		vbuf->ChangeQuadAt(obj->getid(), obj->getcurrentquad());
	}

	int getx() const
	{
		return camerax - screenw/2;
	}

	int gety() const
	{
		return cameray - screenh/2;
	}

	void setcamera(int x, int y)
	{
		camerax = x + screenw/2;
		cameray = y + screenh/2;
	}

	void render(int tile, float transparency = 1.0f)
	{
		glEnable2D(camerax,cameray);
		if (vbuf)
		{
			vbuf->Render(tile, transparency);
		}
		glDisable2D();
	}
};


#endif // OBJECTLAYER_H
