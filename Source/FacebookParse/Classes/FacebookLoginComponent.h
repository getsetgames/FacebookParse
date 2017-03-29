//
//  Created by Derek van Vliet on 2015-03-25.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "FacebookLoginComponent.generated.h"

UCLASS(ClassGroup=Facebook, HideCategories=(Activation, "Components|Activation", Collision), meta=(BlueprintSpawnableComponent))
class UFacebookLoginComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	void OnRegister() override;
	void OnUnregister() override;
	
	UFUNCTION(BlueprintCallable, meta = (Keywords = "facebook"), Category = "Facebook")
	static void FacebookLoginWithReadPermissions(TArray<FString> Permissions);
	
	UFUNCTION(BlueprintCallable, meta = (Keywords = "facebook"), Category = "Facebook")
	static void FacebookLogout();
	
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FFacebookLoginSucceededDelegate, FString, FString, FString);
	DECLARE_MULTICAST_DELEGATE(FFacebookLoginCancelledDelegate);
	DECLARE_MULTICAST_DELEGATE_OneParam(FFacebookLoginErrorDelegate, FString);
	
	static FFacebookLoginSucceededDelegate FacebookLoginSucceededDelegate;
	static FFacebookLoginCancelledDelegate FacebookLoginCancelledDelegate;
	static FFacebookLoginErrorDelegate FacebookLoginErrorDelegate;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FFacebookLoginSucceededDynDelegate, FString, UserId, FString, AccessToken, FString, TokenExpirationDate);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFacebookLoginCancelledDynDelegate);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFacebookLoginErrorDynDelegate, FString, Error);
	
	UPROPERTY(BlueprintAssignable)
	FFacebookLoginSucceededDynDelegate FacebookLoginSucceeded;
	
	UPROPERTY(BlueprintAssignable)
	FFacebookLoginCancelledDynDelegate FacebookLoginCancelled;
	
	UPROPERTY(BlueprintAssignable)
	FFacebookLoginErrorDynDelegate FacebookLoginError;
	
private:
	void ApplicationOpenURL_Handler(FString URL, FString SourceApplication);
	
	void FacebookLoginSucceeded_Handler(FString UserId, FString AccessToken, FString TokenExpirationDate) { FacebookLoginSucceeded.Broadcast(UserId, AccessToken, TokenExpirationDate); }
	void FacebookLoginCancelled_Handler() { FacebookLoginCancelled.Broadcast(); }
	void FacebookLoginError_Handler(FString Error) { FacebookLoginError.Broadcast(Error); }

};
