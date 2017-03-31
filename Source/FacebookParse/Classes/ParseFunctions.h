//
//  Created by Derek van Vliet on 2014-12-10.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "UObject/Object.h"
#include "UObject/ScriptMacros.h"
#include "ParseFunctions.generated.h"

UCLASS(NotBlueprintable)
class UParseFunctions : public UObject {
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, meta = (Keywords = "facebook parse"), Category = "Facebook|Parse")
	static void ParseInit(FString ApplicationId, FString ClientKey);
};
