#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "SDL.h"
#include "GL/glew.h"
#include "primitives.h"
#include "composition.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

class VertexBuffer
{
	GLuint buffer;
	size_t buffer_size;

	GLenum type;
	GLuint object_count;
	GLuint elements_per_object;

	bool uses_texture;
	GLuint texture;

public:
	VertexBuffer(Composition* composition)
	{
		buffer_size = composition->BufferSizeInBytes();
		type = composition->PrimitiveType();
		object_count = composition->ObjectCount();
		elements_per_object = composition->ElementsPerObject();
		uses_texture = composition->UsesTexture();

		if (uses_texture)
		{
			SDL_Surface* tex = composition->Texture();

			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
		
			glTexImage2D(GL_TEXTURE_2D, 0, 4, tex->w, tex->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->pixels);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, buffer_size, composition->Buffer());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Render()
	{
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glEnableClientState(GL_VERTEX_ARRAY);
		
		if (uses_texture)
		{
			glEnable(GL_TEXTURE_2D);
			glClientActiveTexture(GL_TEXTURE0);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		}
		else
		{
			glEnableClientState(GL_COLOR_ARRAY);
		}


		glVertexPointer(3, GL_FLOAT, sizeof(Element), BUFFER_OFFSET(0));
		if (uses_texture)
		{
			glTexCoordPointer(2, GL_FLOAT, sizeof(Element), BUFFER_OFFSET(sizeof(Vertex) + sizeof(Color)));
		}
		else
		{
			glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Element), BUFFER_OFFSET(sizeof(Vertex)));
		}
		

		glDrawArrays(type, 0, object_count * elements_per_object);
		

		glDisableClientState(GL_VERTEX_ARRAY);

		if (uses_texture)
		{
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisable(GL_TEXTURE_2D);
		}
		else
		{
			glDisableClientState(GL_COLOR_ARRAY);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	~VertexBuffer()
	{
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &buffer);
		glDeleteTextures(1, &texture);
	}
};

#endif // VERTEXBUFFER_H
