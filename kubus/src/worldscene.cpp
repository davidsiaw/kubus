#include "worldscene.h"
#include "params.h"


#include <time.h>
#include <math.h>

WorldScene::WorldScene()
:
Scene(),world(),
eyeX(0), eyeY(0), eyeZ(16),
centerX(0), centerY(1), centerZ(16),
upX(0), upY(0), upZ(1),
angle(0),dispList(0),vertAngle(0),
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

#pragma pack(push,1)
struct Vertex
{
    GLfloat x,y,z;
};

struct Color
{
    uint8_t r,g,b,a;
};

struct Element
{
    Vertex v;
    Color c;
};

struct Quad
{
    Element e[4];
};

struct Cube
{
    Quad quads[6];
    Cube(int x, int y, int z)
    {
        // cube constructor
    }
};
#pragma pack(pop)
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

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


        Quad* quads = (Quad*) malloc(sizeInBytes);
        for (int i=0;i<numOfQuads;i++)
        {
            int c = rand() % 256;

            quads[i] = q;
            quads[i].e[0].v.x += (i%size - size/2);
            quads[i].e[0].v.y += (i/size - size/2);
            quads[i].e[0].v.z += 0;
            quads[i].e[0].c.g = c;

            quads[i].e[1].v.x += (i%size - size/2);
            quads[i].e[1].v.y += (i/size - size/2);
            quads[i].e[1].v.z += 0;
            quads[i].e[1].c.g = c;

            quads[i].e[2].v.x += (i%size - size/2);
            quads[i].e[2].v.y += (i/size - size/2);
            quads[i].e[2].v.z += 0;
            quads[i].e[2].c.g = c;

            quads[i].e[3].v.x += (i%size - size/2);
            quads[i].e[3].v.y += (i/size - size/2);
            quads[i].e[3].v.z += 0;
            quads[i].e[3].c.g = c;
        }

        glGenBuffers(1, &dispList);
        glBindBuffer(GL_ARRAY_BUFFER, dispList);
        glBufferData(GL_ARRAY_BUFFER, sizeInBytes, NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeInBytes, quads);

        free(quads);

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


    glBindBuffer(GL_ARRAY_BUFFER, dispList);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, sizeof(Element), BUFFER_OFFSET(0));
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Element), BUFFER_OFFSET(sizeof(Vertex)));

    glBindBuffer(GL_ARRAY_BUFFER, dispList);
    glDrawArrays(GL_QUADS, 0, numOfQuads * 4);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

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
