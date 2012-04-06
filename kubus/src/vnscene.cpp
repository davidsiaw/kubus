#include "vnscene.h"
#include "params.h"

#include "primitives.h"
#include "graphicfuncs.h"
#include "multipletexturedquadcomposition.h"

VNScene::VNScene() 
{
}

VNScene::~VNScene() 
{
}

void VNScene::OnInit() 
{
	SDL_Surface* haruna = resources->GetImage("misc\\haruna.png");
	SDL_Surface* sakuraki = resources->GetImage("misc\\sakuraki.png");
	SDL_Surface* satsuki = resources->GetImage("misc\\satsuki.png");
	SDL_Surface* chii = resources->GetImage("misc\\chii.png");

	MultipleTexturedQuadComposition tqc;

	Quad q = MakeXYPlaneQuad(0,0,haruna->w,haruna->h);
	tqc.Add(&q, haruna);

	q = MakeXYPlaneQuad(200,0,sakuraki->w,sakuraki->h);
	tqc.Add(&q, sakuraki);
	
	q = MakeXYPlaneQuad(200,200,satsuki->w,satsuki->h);
	tqc.Add(&q, satsuki);
	
	q = MakeXYPlaneQuad(0,200,chii->w,chii->h);
	tqc.Add(&q, chii);

	q = MakeXYPlaneQuad(400,200,chii->w,chii->h);
	tqc.Add(&q, chii);

	vbo = new VertexBuffer(&tqc);

	//tqc.DebugDumpLightMap("D:\\gcc\\kubus\\res\\misc\\a.bmp");
}

void VNScene::OnRender() 
{
	static int a = 0;

	glLoadIdentity();

	glEnable2D();

	a++;
	a = a % 200;

	vbo->Render(((a%20)/10) + 1, ((float)a/200.0f));

	glDisable2D();
}


void VNScene::OnEvent(SDL_Event* Event) 
{

}

void VNScene::OnLoop()
{

}

bool VNScene::IsComplete()
{
	return false;
}