//
//  Created by Derek van Vliet on 2014-12-10.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#include "FacebookParsePrivatePCH.h"

void UFacebookFunctions::FacebookActivateApp()
{
#if PLATFORM_IOS
	[FBSDKAppEvents activateApp];
#endif
}

void UFacebookFunctions::FacebookApplicationOpenURL(FString URL, FString SourceApplication)
{
#if PLATFORM_IOS
	IOSAppDelegate* appDelegate = (IOSAppDelegate*)[[UIApplication sharedApplication] delegate];
	
	[[FBSDKApplicationDelegate sharedInstance] application:[UIApplication sharedApplication]
												   openURL:[NSURL URLWithString:URL.GetNSString()]
										 sourceApplication:SourceApplication.GetNSString()
												annotation:appDelegate.launchAnnotation];
#endif
}
