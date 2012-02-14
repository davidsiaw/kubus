#include "module_game.h"

extern "C" { 
#include "lualib.h"
#include "lauxlib.h" 
}

#include "params.h"
#include "intermissionscene.h"
#include "scriptdata.h"
#include "script.h"

int log(lua_State* state)
{
	int argc = lua_gettop(state);
	if (argc == 1 && lua_isstring(state, 1))
	{
		const char* c = lua_tostring(state, 1);
		printf("%s\n", c);
	}
	// error
	return 0;
}

int getImage(lua_State* state)
{
	int argc = lua_gettop(state);
	if (argc == 1 && lua_isstring(state, 1))
	{
		const char* c = lua_tostring(state, 1);
		ScriptData* data = new ScriptData(resources->GetImage(c));
		lua_pushlightuserdata(state, data);
		return 1;
	}
	// error
	return 0;
}

int makeIntermissionScene(lua_State* state)
{
	int argc = lua_gettop(state);
	if (argc == 1 && lua_islightuserdata(state, 1))
	{
		ScriptData* data = (ScriptData*)lua_touserdata(state, 1);
		if (data->GetType() == SDL_SURFACE)
		{
			IntermissionScene* is = new IntermissionScene((SDL_Surface*)data->GetData());
			lua_pushlightuserdata(state, new ScriptData(is));
			return 1;
		}
	}
	// error
	return 0;
}

int doScene(lua_State* state)
{
	int argc = lua_gettop(state);
	if (argc == 1 && lua_islightuserdata(state,1))
	{
		ScriptData* data = (ScriptData*)lua_touserdata(state, 1);
		if (data->GetType() == INTERMISSIONSCENE)
		{
			lua_getglobal(state, SCRIPT_GLOBAL_NAME);
			Script* s = (Script*)lua_touserdata(state, argc+1);
			Scene* scene = (Scene*)data->GetData();
			scene->OnInit();
			s->setCurrentScene(scene);

			lua_yield(state,0);

			return 0;
		}
	}
	// error
	return 0;
}

int destroy(lua_State* state)
{
	int argc = lua_gettop(state);
	if (argc == 1 && lua_islightuserdata(state,1))
	{
		ScriptData* data = (ScriptData*)lua_touserdata(state, 1);
		delete data;
	}
	// error
	return 0;
}

int doExit(lua_State* state)
{
	int argc = lua_gettop(state);
	lua_getglobal(state, SCRIPT_GLOBAL_NAME);
	Script* s = (Script*)lua_touserdata(state, argc+1);
	s->setCurrentScene(NULL);
	return 0;
}

// this function provides the game module to the
// script. The game module contains functions
// that manipulate the engine.
// To use just go game.log()
void installGameModule(lua_State* state)
{
	luaL_Reg module[] = 
	{
		{"log", log},
		{"getImage", getImage},
		{"makeIntermissionScene", makeIntermissionScene},
		{"doScene", doScene},
		{"doExit", doExit},
		{"destroy", destroy},
		{NULL, NULL}
	};

	luaL_openlibs(state);

	luaL_newlib(state, module);
	lua_setglobal(state, "game");

}
