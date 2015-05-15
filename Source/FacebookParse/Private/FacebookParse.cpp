//
//  Created by Derek van Vliet on 2015-03-25.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#include "FacebookParsePrivatePCH.h"
#include "FacebookParseSettings.h"
#include "ISettingsModule.h"

#if PLATFORM_IOS
#import "IOSAppDelegate.h"
#import <Parse/Parse.h>
#import <ParseCrashReporting/ParseCrashReporting.h>
#endif

DEFINE_LOG_CATEGORY(LogFacebookParse);

#define LOCTEXT_NAMESPACE "FacebookParse"

class FFacebookParse : public IFacebookParse
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FFacebookParse, FacebookParse )

void FFacebookParse::StartupModule()
{
	const UFacebookParseSettings* DefaultSettings = GetDefault<UFacebookParseSettings>();
	
#if PLATFORM_IOS
	if (!DefaultSettings->ApplicationId.IsEmpty() && !DefaultSettings->ClientKey.IsEmpty())
	{
		if (DefaultSettings->CrashReporting)
		{
			[ParseCrashReporting enable];
		}
		
		if (DefaultSettings->EnableLocalDatastore)
		{
			[Parse enableLocalDatastore];
		}
		
		[Parse setApplicationId:DefaultSettings->ApplicationId.GetNSString()
					  clientKey:DefaultSettings->ClientKey.GetNSString()];
		
		if (DefaultSettings->TrackAppOpened)
		{
			IOSAppDelegate* appDelegate = (IOSAppDelegate*)[[UIApplication sharedApplication] delegate];
			[PFAnalytics trackAppOpenedWithLaunchOptions:appDelegate.launchOptions];
		}
	}
#endif
		
	// register settings
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "Parse",
										 LOCTEXT("RuntimeSettingsName", "Parse"),
										 LOCTEXT("RuntimeSettingsDescription", "Configure the Parse plugin"),
										 GetMutableDefault<UFacebookParseSettings>()
										 );
	}
}


void FFacebookParse::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE