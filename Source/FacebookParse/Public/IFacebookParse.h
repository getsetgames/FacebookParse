//
//  Created by Derek van Vliet on 2015-03-25.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "ModuleManager.h"

class IFacebookParse : public IModuleInterface
{

public:

	static inline IFacebookParse& Get()
	{
		return FModuleManager::LoadModuleChecked< IFacebookParse >( "FacebookParse" );
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded( "FacebookParse" );
	}
};

