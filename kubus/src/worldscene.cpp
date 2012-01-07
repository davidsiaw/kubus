#include "worldscene.h"
#include "params.h"
#include "quadcomposition.h"

#include <time.h>
#include <math.h>


WorldScene::WorldScene()
:
Scene(),world(),
eyeX(0), eyeY(0), eyeZ(16),
centerX(0), centerY(1), centerZ(16),
upX(0), upY(0), upZ(1),
angle(0),vbo(0),vertAngle(0),
worldChanged(true),
foX(sin(0.0)),foY(cos(0.0)),
stX(sin(3.14159/2)),stY(cos(3.14159/2))
{
}

WorldScene::~WorldScene()
{
}

void WorldScene::OnInit()
{
}

void WorldScene::OnRender()
{
    GLint error=0;

    int size = 1024;
    int numOfQuads = size*size;
    int sizeInBytes = numOfQuads*sizeof(Quad);
    srand(time(NULL));

    if (worldChanged)
    {
        /*
        dispList = glGenLists(1);

        glNewList(dispList, GL_COMPILE);

        for(int x=-768; x<768; x++)
        for(int y=-768; y<768; y++)
        {
            glBegin(GL_QUADS);
                glColor3f((double)(rand() % 100) / 500, (double)(rand() % 100) / 100, 0);
                glVertex3i((x)  * 1, (y)  * 1, 0);
                glVertex3i((x+1)* 1, (y)  * 1, 0);
                glVertex3i((x+1)* 1, (y+1)* 1, 0);
                glVertex3i((x)  * 1, (y+1)* 1, 0);
            glEnd();
        }

        glEndList();
        worldChanged = false;
        */


        Quad q = {{
            {{0,0,0}, {0,0,0,0}},
            {{1,0,0}, {0,0,0,0}},
            {{1,1,0}, {0,0,0,0}},
            {{0,1,0}, {0,0,0,0}},
        }};


        QuadComposition qc;
        for (int i=0;i<numOfQuads;i++)
        {
            int c = rand() % 256;

			Quad thequad = q;

            thequad = q;
            thequad.e[0].v.x += (i%size - size/2);
            thequad.e[0].v.y += (i/size - size/2);
            thequad.e[0].v.z += 0;
            thequad.e[0].c.g = c;

            thequad.e[1].v.x += (i%size - size/2);
            thequad.e[1].v.y += (i/size - size/2);
            thequad.e[1].v.z += 0;
            thequad.e[1].c.g = c;

            thequad.e[2].v.x += (i%size - size/2);
            thequad.e[2].v.y += (i/size - size/2);
            thequad.e[2].v.z += 0;
            thequad.e[2].c.g = c;

            thequad.e[3].v.x += (i%size - size/2);
            thequad.e[3].v.y += (i/size - size/2);
            thequad.e[3].v.z += 0;
            thequad.e[3].c.g = c;

			qc.Add(&thequad);
        }

		vbo = new VertexBuffer(&qc);

        worldChanged = false;
    }


    double uz = tan(vertAngle * 3.14159 / 180);

    centerX = eyeX + foX;
    centerY = eyeY + foY;
    centerZ = eyeZ + uz;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt (eyeX, eyeY, eyeZ,
               centerX, centerY, centerZ,
               upX, upY, upZ);


	vbo->Render();

    //glCallList(dispList);
}

void WorldScene::OnEvent(SDL_Event* event)
{
    double newangle;

    switch(event->type)
    {
        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_ESCAPE)
            {
                event->type = SDL_QUIT;
            }
        break;

        case SDL_KEYUP:
        break;

        case SDL_MOUSEMOTION:

            angle += (double)event->motion.xrel / 10.0;
            newangle = vertAngle + (double) (-event->motion.yrel) / 5.0;

            if (newangle < 90  && newangle > -90 )
            {
                vertAngle = newangle;
            }

            foX = sin(angle * 3.14159 / 180);
            foY = cos(angle * 3.14159 / 180);

            stX = sin((angle+90) * 3.14159 / 180);
            stY = cos((angle+90) * 3.14159 / 180);

            SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
            SDL_WarpMouse(screenWidth >> 1, screenHeight >> 1);
            SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
        break;

        case SDL_MOUSEBUTTONDOWN:
        break;

        case SDL_MOUSEBUTTONUP:
        break;

        default:
        break;
    }
}

void WorldScene::OnLoop()
{
    uint8_t* keys = SDL_GetKeyState(NULL);

    GLdouble forward=0, strafe=0;

    if (keys[SDLK_w] != 0) { forward = 1; }
    if (keys[SDLK_a] != 0) { strafe = -1; }
    if (keys[SDLK_s] != 0) { forward = -1; }
    if (keys[SDLK_d] != 0) { strafe = 1; }

    eyeX += forward * foX + strafe * stX;
    eyeY += forward * foY + strafe * stY;

    SDL_ShowCursor(0);
}
