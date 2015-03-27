//
//  Created by Derek van Vliet on 2015-03-25.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#include "ParsePluginPrivatePCH.h"
#include "CallbackDevice.h"

#if PLATFORM_IOS
#import <Parse/Parse.h>
#endif

void UParsePushComponent::OnRegister()
{
	Super::OnRegister();
	
	// init here
	
	FCoreDelegates::ApplicationRegisteredForRemoteNotificationsDelegate.AddUObject(this, &UParsePushComponent::ApplicationRegisteredForRemoteNotifications_Handler);
	FCoreDelegates::ApplicationFailedToRegisterForRemoteNotificationsDelegate.AddUObject(this, &UParsePushComponent::ApplicationFailedToRegisterForRemoteNotifications_Handler);
	FCoreDelegates::ApplicationReceivedRemoteNotificationDelegate.AddUObject(this, &UParsePushComponent::ApplicationReceivedRemoteNotification_Handler);
}

void UParsePushComponent::OnUnregister()
{
	Super::OnUnregister();
	
	// clean up here
	
	FCoreDelegates::ApplicationRegisteredForRemoteNotificationsDelegate.RemoveAll(this);
	FCoreDelegates::ApplicationFailedToRegisterForRemoteNotificationsDelegate.RemoveAll(this);
	FCoreDelegates::ApplicationReceivedRemoteNotificationDelegate.RemoveAll(this);
}

void UParsePushComponent::ApplicationRegisteredForRemoteNotifications_Handler(TArray<uint8> Token)
{
#if PLATFORM_IOS
	NSData* TokenData = [NSData dataWithBytes:Token.GetData() length:Token.Num()];
	PFInstallation* Installation = [PFInstallation currentInstallation];
	[Installation setDeviceTokenFromData:TokenData];
	[Installation saveInBackground];
#endif
}

void UParsePushComponent::ApplicationFailedToRegisterForRemoteNotifications_Handler(FString RegisterError)
{
	UE_LOG(LogParsePlugin, Error, TEXT("ApplicationFailedToRegisterForRemoteNotifications: %s"), *RegisterError);
}

void UParsePushComponent::ApplicationReceivedRemoteNotification_Handler(FString Json)
{
	UE_LOG(LogParsePlugin, Log, TEXT("ApplicationReceivedRemoteNotification: %s"), *Json);
}
