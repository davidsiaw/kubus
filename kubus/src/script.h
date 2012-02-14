#ifndef SCRIPT_H
#define SCRIPT_H

#include "scene.h"
#include "params.h"

extern "C" {
	#include "lua.h"
}

extern const char* SCRIPT_GLOBAL_NAME;

// This class is the script, that controls the game
class Script
{
	lua_State* state;
	Scene* currentScene;

public:
	Script();
	~Script();

	Scene* getCurrentScene() const;
	void setCurrentScene(Scene* scene);
	void Run();
};

#endif //SCRIPT_H
