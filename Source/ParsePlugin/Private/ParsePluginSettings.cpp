//
//  Created by Derek van Vliet on 2015-03-25.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#include "ParsePluginPrivatePCH.h"
#include "ParsePluginSettings.h"

UParsePluginSettings::UParsePluginSettings(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, EnableLocalDatastore(false)
, CrashReporting(false)
, TrackAppOpened(false)
{
	
}
