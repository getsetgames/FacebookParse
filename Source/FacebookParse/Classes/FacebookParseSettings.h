//
//  Created by Derek van Vliet on 2015-03-25.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "FacebookParseSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class UFacebookParseSettings : public UObject
{
	GENERATED_BODY()
	
public:
	UFacebookParseSettings(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(Config, EditAnywhere, Category=Parse, meta=(DisplayName="Enable Local Datastore"))
	bool EnableLocalDatastore;
	
	UPROPERTY(Config, EditAnywhere, Category=Parse, meta=(DisplayName="Crash Reporting"))
	bool CrashReporting;
	
	UPROPERTY(Config, EditAnywhere, Category=Parse, meta=(DisplayName="Track App Opened"))
	bool TrackAppOpened;
    
    UPROPERTY(Config, EditAnywhere, Category=Parse, meta=(DisplayName="App ID"))
    FString FBID;
};
