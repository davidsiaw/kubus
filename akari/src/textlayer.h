#ifndef TEXTLAYER_H
#define TEXTLAYER_H

#include <vector>
#include <boost/shared_ptr.hpp>
#include "font_interface.h"
#include "vertexbuffer.h"
#include "composition_interface.h"
#include "resources_interface.h"
#include "texanimshader_interface.h"

class textlayer
{
	class textcomposition : public composition_interface
	{
		std::vector<quad> quads;
		boost::shared_ptr<font_interface> font;
		GLuint texturemap;
	public:
		textcomposition(GLuint texturemap, boost::shared_ptr<font_interface> font, std::string text)
			: font(font), texturemap(texturemap)
		{
			float pos = 0;
			for(std::string::iterator chr = text.begin(); chr != text.end(); chr++)
			{
				quad chrquad = font->getquadforchar(*chr);
				chrquad.e[0].v.x += pos;
				chrquad.e[1].v.x += pos;
				chrquad.e[2].v.x += pos;
				chrquad.e[3].v.x += pos;
				quads.push_back(chrquad);
				
				if (chr+1 != text.end())
				{
					pos += font->getspaceforchar(*chr, *(chr+1));
				}
			}
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

	boost::shared_ptr<vertexbuffer> vbuf;
	boost::shared_ptr<font_interface> font;
	boost::shared_ptr<resources_interface> res;
	boost::shared_ptr<texanimshader_interface> shader;

public:
	textlayer(boost::shared_ptr<texanimshader_interface> shader, boost::shared_ptr<resources_interface> res, boost::shared_ptr<font_interface> font) 
		: font(font), res(res), shader(shader)
	{
	}

	void settext(std::string str)
	{
		if (str.size() == 0)
		{
			vbuf = boost::shared_ptr<vertexbuffer>();
		}
		if (vbuf != NULL && vbuf->NumObjects() >= str.size())
		{
			float pos = 0;
			for(size_t i=0; i<str.size(); i++)
			{
				quad chrquad = font->getquadforchar(str[i]);
				chrquad.e[0].v.x += pos;
				chrquad.e[1].v.x += pos;
				chrquad.e[2].v.x += pos;
				chrquad.e[3].v.x += pos;

				vbuf->ChangeQuadAt(i, chrquad);
				
				if (i+1 != str.size())
				{
					pos += font->getspaceforchar(str[i], str[i+1]);
				}
			}
			for (size_t i=str.size(); i<vbuf->NumObjects(); i++)
			{
				quad emptyquad = MakeQuad(0,0,0,0);
				vbuf->ChangeQuadAt(i, emptyquad);
			}
		}
		else
		{
			boost::shared_ptr<textcomposition> composition(new textcomposition(res->getimage(font->gettexturemap()), font, str));
			vbuf = boost::shared_ptr<vertexbuffer>(new vertexbuffer(shader, composition));
		}
	}

	void render(float transparency = 1.0f)
	{
		if (vbuf != NULL)
		{
			glTranslatef(0,0,SHRT_MAX);
			glPushMatrix();
			vbuf->Render(0, transparency);
			glPopMatrix();
		}
	}

};

#endif // TEXTLAYER_H
