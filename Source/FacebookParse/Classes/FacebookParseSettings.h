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
	
	UPROPERTY(Config, EditAnywhere, Category=Ids, meta=(DisplayName="Application ID"))
	FString ApplicationId;
	
	UPROPERTY(Config, EditAnywhere, Category=Ids, meta=(DisplayName="Client Key"))
	FString ClientKey;
	
	UPROPERTY(Config, EditAnywhere, Category=Features, meta=(DisplayName="Enable Local Datastore"))
	bool EnableLocalDatastore;
	
	UPROPERTY(Config, EditAnywhere, Category=Features, meta=(DisplayName="Crash Reporting"))
	bool CrashReporting;
	
	UPROPERTY(Config, EditAnywhere, Category="Features", meta=(DisplayName="Track App Opened"))
	bool TrackAppOpened;
};
