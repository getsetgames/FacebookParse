#include "ParsePluginPrivatePCH.h"
#include "ParsePluginSettings.h"
#include "ISettingsModule.h"

#if PLATFORM_IOS
#import "IOSAppDelegate.h"
#import <Parse/Parse.h>
#import <ParseCrashReporting/ParseCrashReporting.h>
#endif

DEFINE_LOG_CATEGORY(LogParsePlugin);

#define LOCTEXT_NAMESPACE "ParsePlugin"

class FParsePlugin : public IParsePlugin
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FParsePlugin, ParsePlugin )

void FParsePlugin::StartupModule()
{
	const UParsePluginSettings* DefaultSettings = GetDefault<UParsePluginSettings>();
	
	// initialize iOS
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
										 GetMutableDefault<UParsePluginSettings>()
										 );
	}
}


void FParsePlugin::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE