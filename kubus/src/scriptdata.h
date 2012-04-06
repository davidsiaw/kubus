#ifndef SCRIPTDATA_H
#define SCRIPTDATA_H

#include "SDL.h"
#include "intermissionscene.h"

// List the types you will pass around here
// DO NOT include the h files

enum DataType
{
	SDL_SURFACE,
	INTERMISSIONSCENE,
};

// This class encapsulates any game data
// that the script needs to pass around
class ScriptData
{
	DataType type;
	void* data;

public:
	// make a constructor for every different type of data

	ScriptData(SDL_Surface* surface)
	{
		type = SDL_SURFACE;
		data = surface;
	}
	
	ScriptData(IntermissionScene* scene)
	{
		type = INTERMISSIONSCENE;
		data = scene;
	}

	~ScriptData()
	{
		switch(type)
		{
		case INTERMISSIONSCENE:
			delete (IntermissionScene*)data;
			break;
		}
	}

	DataType GetType() const
	{
		return type;
	}

	void* GetData() const
	{
		return data;
	}
};

#endif // SCRIPTDATA_H