//
//  Created by Derek van Vliet on 2015-03-25.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#include "FacebookParsePrivatePCH.h"
#include "FacebookParseSettings.h"
#include "ISettingsModule.h"

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
	// register settings
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "FacebookParse",
										 LOCTEXT("RuntimeSettingsName", "FacebookParse"),
										 LOCTEXT("RuntimeSettingsDescription", "Configure the FacebookParse plugin"),
										 GetMutableDefault<UFacebookParseSettings>()
										 );
	}
}


void FFacebookParse::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE