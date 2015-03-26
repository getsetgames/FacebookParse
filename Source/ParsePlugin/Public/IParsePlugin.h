//
//  Created by Derek van Vliet on 2015-03-25.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

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

