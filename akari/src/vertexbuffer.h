#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <tr1/memory>
#include "GL/glew.h"
#include "primitives.h"
#include "composition_interface.h"
#include "texanimshader_interface.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

class vertexbuffer
{
	// The vertex buffer and info
	GLuint buffer;
	size_t buffer_size;

	GLenum type;
	GLuint object_count;
	GLuint elements_per_object;

	// Texture information
	bool uses_texture;
	GLuint texture;

	std::tr1::shared_ptr<texanimshader_interface> shader;

public:
	vertexbuffer(std::tr1::shared_ptr<texanimshader_interface> shader, std::tr1::shared_ptr<composition_interface> composition)
	{
		buffer_size = composition->BufferSizeInBytes();
		type = composition->PrimitiveType();
		object_count = composition->ObjectCount();
		elements_per_object = composition->ElementsPerObject();
		uses_texture = composition->UsesTexture();
		this->texture = composition->Texture();
		this->shader = shader;

        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, buffer_size, composition->Buffer());
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void ChangeQuadAt(size_t index, quad q)
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferSubData(GL_ARRAY_BUFFER, index * sizeof(quad), sizeof(quad), &q);
	}

	void ChangeTriangle(size_t index, triangle t)
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferSubData(GL_ARRAY_BUFFER, index * sizeof(triangle), sizeof(triangle), &t);
	}

	void ChangeElementAt(size_t index, element e)
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferSubData(GL_ARRAY_BUFFER, index * sizeof(element), sizeof(element), &e);
	}

	GLuint NumObjects() const
	{
		return object_count;
	}

	~vertexbuffer()
	{
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &buffer);
	}

	void Render(int tile = 0, float transparency = 1.0f)
	{
		glUseProgram(shader->getprogram());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		
		glEnableVertexAttribArray(shader->getposition_attribute());
		glEnableVertexAttribArray(shader->gettexcoord_attribute());
		glEnableVertexAttribArray(shader->getcolor_attribute());
		glEnableVertexAttribArray(shader->gettile_attribute());
		glEnableVertexAttribArray(shader->gettilenum_attribute());
		
		shader->settransparency_uniform(transparency);
		shader->sethastexture_uniform(uses_texture);
		shader->settexture_uniform(0);
		shader->setactivetile_uniform(tile);

		glVertexAttribPointer(shader->getposition_attribute(), 3, GL_FLOAT, GL_FALSE, sizeof(element), BUFFER_OFFSET(0));
		glVertexAttribPointer(shader->getcolor_attribute(), 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(element),  BUFFER_OFFSET(sizeof(vertex)));
		glVertexAttribPointer(shader->gettexcoord_attribute(), 2, GL_FLOAT, GL_FALSE, sizeof(element), BUFFER_OFFSET(sizeof(vertex) + sizeof(color)));
		glVertexAttribPointer(shader->gettile_attribute(), 1, GL_FLOAT, GL_FALSE, sizeof(element), BUFFER_OFFSET(sizeof(vertex) + sizeof(color) + sizeof(texcoord)));
		glVertexAttribPointer(shader->gettilenum_attribute(), 1, GL_FLOAT, GL_FALSE, sizeof(element), BUFFER_OFFSET(sizeof(vertex) + sizeof(color) + sizeof(texcoord) + sizeof(float)));
		
		glDrawArrays(type, 0, object_count * elements_per_object);
		
		glDisableVertexAttribArray(shader->getposition_attribute());
		glDisableVertexAttribArray(shader->gettexcoord_attribute());
		glDisableVertexAttribArray(shader->getcolor_attribute());
		glDisableVertexAttribArray(shader->gettile_attribute());
		glDisableVertexAttribArray(shader->gettilenum_attribute());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};


#endif // VERTEXBUFFER_H
