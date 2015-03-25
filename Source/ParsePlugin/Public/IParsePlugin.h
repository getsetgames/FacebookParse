#pragma once

#include "ModuleManager.h"

class IParsePlugin : public IModuleInterface
{

public:

	static inline IParsePlugin& Get()
	{
		return FModuleManager::LoadModuleChecked< IParsePlugin >( "ParsePlugin" );
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded( "ParsePlugin" );
	}
};

