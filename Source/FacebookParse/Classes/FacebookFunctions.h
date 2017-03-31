//
//  Created by Derek van Vliet on 2014-12-10.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "UObject/Object.h"
#include "UObject/ScriptMacros.h"
#include "FacebookFunctions.generated.h"

UCLASS(NotBlueprintable)
class UFacebookFunctions : public UObject {
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta = (Keywords = "facebook"), Category = "Facebook")
	static FString FacebookGetAccessToken();
	
	UFUNCTION(BlueprintPure, meta = (Keywords = "facebook"), Category = "Facebook")
	static FString FacebookGetAccessTokenExpirationDate();
	
	UFUNCTION(BlueprintPure, meta = (Keywords = "facebook"), Category = "Facebook")
	static FString FacebookGetUserId();
};
