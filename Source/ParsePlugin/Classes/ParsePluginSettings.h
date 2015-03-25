#pragma once

#include "ParsePluginSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class UParsePluginSettings : public UObject
{
	GENERATED_BODY()
	
public:
	UParsePluginSettings(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(Config, EditAnywhere, Category=Ids, meta=(DisplayName="Application ID"))
	FString ApplicationId;
	
	UPROPERTY(Config, EditAnywhere, Category=Ids, meta=(DisplayName="Client Key"))
	FString ClientKey;
	
	UPROPERTY(Config, EditAnywhere, Category=Features, meta=(DisplayName="Enable Local Datastore"))
	bool EnableLocalDatastore;
	
	UPROPERTY(Config, EditAnywhere, Category=Features, meta=(DisplayName="Crash Reporting"))
	bool CrashReporting;
	
	// iOS
	
	UPROPERTY(Config, EditAnywhere, Category="iOS Features", meta=(DisplayName="Track App Opened"))
	bool TrackAppOpened;
};
