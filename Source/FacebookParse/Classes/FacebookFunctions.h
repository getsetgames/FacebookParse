//
//  Created by Derek van Vliet on 2014-12-10.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "FacebookFunctions.generated.h"

UCLASS(NotBlueprintable)
class UFacebookFunctions : public UObject {
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, meta = (Keywords = "facebook"), Category = "Facebook")
	static void FacebookActivateApp();

	UFUNCTION(BlueprintCallable, meta = (Keywords = "facebook"), Category = "Facebook")
	static void FacebookApplicationOpenURL(FString URL, FString SourceApplication);
};
