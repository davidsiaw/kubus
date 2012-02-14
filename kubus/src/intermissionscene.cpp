#include "intermissionscene.h"
#include "graphicfuncs.h"
#include "multipletexturedquadcomposition.h"

enum Mode
{
	FADE_IN,
	STICK,
	FADE_OUT,
	END
};

IntermissionScene::IntermissionScene(SDL_Surface* image, int fadeInTime, int stickTime, int fadeOutTime)
{
	this->image = image;
	this->fadeInTime = fadeInTime * 60;
	this->stickTime = stickTime * 60;
	this->fadeOutTime = fadeOutTime * 60;
	this->vbo = NULL;
}

IntermissionScene::~IntermissionScene()
{
	delete vbo;
}

void IntermissionScene::OnInit()
{
	MultipleTexturedQuadComposition tqc;

	Quad q = MakeXYPlaneQuad(0,0,image->w,image->h);
	tqc.Add(&q, image);

	if (vbo != NULL)
	{
		delete vbo;
	}
	
	this->mode = FADE_IN;
	this->currentTime = 0;
	vbo = new VertexBuffer(&tqc);
}

void IntermissionScene::OnRender()
{
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable2D();

	float transparency = 0.0f;
	if (mode == FADE_IN) 
	{
		transparency = (float)currentTime/(float)fadeInTime;
		if (currentTime == fadeInTime)
		{
			mode = STICK;
			currentTime = 0;
		}
	}
	else if (mode == FADE_OUT)
	{
		transparency = 1.0f - (float)currentTime/(float)fadeOutTime;
		if (currentTime == fadeOutTime)
		{
			mode = END;
			currentTime = 0;
		}
	}
	else if (mode == STICK)
	{
		transparency = 1.0f;
		if (currentTime == stickTime)
		{
			mode = FADE_OUT;
			currentTime = 0;
		}
	}

	vbo->Render(1, transparency);

	currentTime++;
	

	glDisable2D();
}

void IntermissionScene::OnEvent(SDL_Event* Event)
{
}

void IntermissionScene::OnLoop()
{
}

bool IntermissionScene::IsComplete()
{
	return mode == END;
}
