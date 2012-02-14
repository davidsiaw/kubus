#include "script.h"

#include <cstdlib>
#include <cstring>

extern "C" { 
#include "lualib.h"
#include "lauxlib.h" 
}

#include "module_game.h"

const char* SCRIPT_GLOBAL_NAME = "_internal_script_object";

static void *l_alloc (void *ud, void *ptr, size_t osize, size_t nsize) 
{
	(void)ud;
	(void)osize;  /* not used */
	if (nsize == 0) 
	{
		free(ptr);
		return NULL;
	}
	else 
	{
		return realloc(ptr, nsize);
	}
}

class PrintLoadFailed{};

Script::Script()
{
	std::string script = resources->GetTextfile("main.lua");
	state = lua_newstate(l_alloc, NULL);

	// put the script state as a global
	// (no good reason, just easy. so we can jsut go getglobal(SCRIPT_GLOBAL_NAME)
	lua_pushlightuserdata(state, this);
	lua_setglobal(state, SCRIPT_GLOBAL_NAME);

	installGameModule(state);

	int result = luaL_loadbuffer(state, script.c_str(), script.length(), "main");
	
	if (result != LUA_OK) 
	{
		printf(lua_tostring(state, -1));
		throw PrintLoadFailed();
	}

	this->currentScene = NULL;
}

Script::~Script()
{
	lua_close(state);
}

void Script::Run()
{
	lua_resume(state, NULL, 0);
}

void Script::setCurrentScene(Scene* scene)
{
	currentScene = scene;
}

Scene* Script::getCurrentScene() const {
	return currentScene;
}
