#ifndef ORDINARYTEXANIMSHADER_H
#define ORDINARYTEXANIMSHADER_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include "texanimshader_interface.h"

class ordinarytexanimshader : public texanimshader_interface
{
	GLuint shader;

	GLint aPosition;
	GLint aTexCoord;
	GLint aColor;
	GLint aTile;
	GLint aTileNum;

	GLint uHasTexture;
	GLint uTexture;
	GLint uTransparency;
	GLint uActiveTile;

	static void printShaderInfoLog(GLuint obj)
	{
		int infologLength = 0;
		int charsWritten  = 0;
		char *infoLog;

		glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);
		if (infologLength > 0)
		{
			infoLog = (char *)malloc(infologLength);
			glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
			printf("%s\n",infoLog);
			free(infoLog);
		}
	}

	static GLuint SetUpShader()
	{
		const char* vertexshader =
			"attribute vec3 aPosition;"
			"attribute vec2 aTexCoord;"
			"attribute vec4 aColor;"
			"attribute float aTile;"
			"attribute float aTileNum;"
			
			"varying vec2 vTexCoord;"
			"varying vec4 vColor;"

			"uniform float uActiveTile;"

			"void main()"
			"{"
				// Transforming The Vertex
			"	gl_Position = gl_ModelViewProjectionMatrix * vec4(aPosition, 1.0);"

				// Pass the rest to fragment shader
			"	vTexCoord = aTexCoord;"
			"	vColor = aColor;"
			"	vTexCoord.x += mod(uActiveTile, aTileNum) * aTile;"
			"}"
		;

		const char* fragmentshader =
			"varying vec2 vTexCoord;"
			"varying vec4 vColor;"
			
			"uniform float uHasTexture;"
			"uniform sampler2D uTexture;"
			"uniform float uTransparency;"

			"void main()"
			"{"
			"	vec4 color = (1.0 - uHasTexture) * vColor;"
			"	vec4 texcolor = uHasTexture * texture2D(uTexture, vTexCoord);"
			"	gl_FragColor = color + texcolor;"
			"	gl_FragColor.a *= uTransparency;"
			"}"
		;

		GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vshader, 1, &vertexshader, NULL);
		glShaderSource(fshader, 1, &fragmentshader, NULL);
		
		printf("Compiling Vertex Shader...\n");
		glCompileShader(vshader);
		printShaderInfoLog(vshader);

		printf("Compiling Fragment Shader...\n");
		glCompileShader(fshader);
		printShaderInfoLog(fshader);

		GLuint prog = glCreateProgram();
		glAttachShader(prog, fshader);
		glAttachShader(prog, vshader);

		glLinkProgram(prog);

		glDeleteShader(vshader);
		glDeleteShader(fshader);

		return prog;
	}
public:
	ordinarytexanimshader()
	{
		shader = SetUpShader();

		aPosition = glGetAttribLocation(shader, "aPosition");
		aTexCoord = glGetAttribLocation(shader, "aTexCoord");
		aColor = glGetAttribLocation(shader, "aColor");
		aTile = glGetAttribLocation(shader, "aTile");
		aTileNum = glGetAttribLocation(shader, "aTileNum");
		
		uActiveTile = glGetUniformLocation(shader, "uActiveTile");
		uHasTexture = glGetUniformLocation(shader, "uHasTexture");
		uTexture = glGetUniformLocation(shader, "uTexture");
		uTransparency = glGetUniformLocation(shader, "uTransparency");
	}

	~ordinarytexanimshader()
	{
		glDeleteProgram(shader);
	}
	
	virtual GLuint getprogram()
	{
		return shader;
	}

	virtual GLuint getposition_attribute()
	{
		return aPosition;
	}

	virtual GLuint getcolor_attribute()
	{
		return aColor;
	}

	virtual GLuint gettile_attribute()
	{
		return aTile;
	}

	virtual GLuint gettilenum_attribute()
	{
		return aTileNum;
	}

	virtual GLuint gettexcoord_attribute()
	{
		return aTexCoord;
	}


	virtual void settransparency_uniform(GLfloat transp)
	{
		glUniform1f(uTransparency, transp);
	}

	virtual void setactivetile_uniform(GLfloat activetile)
	{
		glUniform1f(uActiveTile, activetile);
	}

	virtual void sethastexture_uniform(bool hastexture)
	{
		glUniform1f(uHasTexture, hastexture ? 1.0f : 0.0f);
	}

	virtual void settexture_uniform(GLuint tex)
	{
		glUniform1i(uTexture, tex);
	}
};

#endif // ORDINARYTEXANIMSHADER_H
