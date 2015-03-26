//
//  Created by Derek van Vliet on 2015-03-25.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "ParsePushComponent.generated.h"

UCLASS(ClassGroup=Parse, HideCategories=(Activation, "Components|Activation", Collision), meta=(BlueprintSpawnableComponent))
class UParsePushComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	void OnRegister() override;
	void OnUnregister() override;
	
private:
	void ApplicationRegisteredForRemoteNotifications_Handler(TArray<uint8> Token);
	void ApplicationFailedToRegisterForRemoteNotifications_Handler();
};
