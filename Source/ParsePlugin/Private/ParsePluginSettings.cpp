#include "ParsePluginPrivatePCH.h"
#include "ParsePluginSettings.h"

UParsePluginSettings::UParsePluginSettings(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, EnableLocalDatastore(false)
, TrackAppOpened(false)
{
	
}
