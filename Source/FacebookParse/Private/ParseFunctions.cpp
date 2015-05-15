//
//  Created by Derek van Vliet on 2014-12-10.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#include "FacebookParsePrivatePCH.h"

void UParseFunctions::ParseInit(FString ApplicationId, FString ClientKey)
{
	const UFacebookParseSettings* DefaultSettings = GetDefault<UFacebookParseSettings>();
	
#if PLATFORM_IOS
	if (!ApplicationId.IsEmpty() && !ClientKey.IsEmpty())
	{
		if (DefaultSettings->CrashReporting)
		{
			[ParseCrashReporting enable];
		}
		
		if (DefaultSettings->EnableLocalDatastore)
		{
			[Parse enableLocalDatastore];
		}
		
		[Parse setApplicationId:ApplicationId.GetNSString()
					  clientKey:ClientKey.GetNSString()];
		
		if (DefaultSettings->TrackAppOpened)
		{
			IOSAppDelegate* appDelegate = (IOSAppDelegate*)[[UIApplication sharedApplication] delegate];
			[PFAnalytics trackAppOpenedWithLaunchOptions:appDelegate.launchOptions];
		}
	}
#endif
}
