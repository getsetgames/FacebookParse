//
//  Created by Derek van Vliet on 2015-03-25.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

namespace UnrealBuildTool.Rules
{
	public class ParsePlugin : ModuleRules
	{
		public ParsePlugin(TargetInfo Target)
		{
			PublicIncludePaths.AddRange(
				new string[] {
					// ... add public include paths required here ...
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					"Developer/Parse/Private",
					// ... add other private include paths required here ...
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"Engine"
					// ... add other public dependencies that you statically link with here ...
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					// ... add private dependencies that you statically link with here ...
				}
				);

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
					// ... add any modules that your module loads dynamically here ...
				}
				);
				
			PrivateIncludePathModuleNames.AddRange(
			new string[] {
				"Settings"
			}
			);
			
			if (Target.Platform == UnrealTargetPlatform.IOS) {
				PublicAdditionalFrameworks.Add( 
					new UEBuildFramework( 
						"Bolts",
						"../../lib/iOS/Bolts.embeddedframework.zip"
					)
				); 
				PublicAdditionalFrameworks.Add( 
					new UEBuildFramework( 
						"Parse",
						"../../lib/iOS/Parse.embeddedframework.zip"
					)
				); 
				PublicAdditionalFrameworks.Add( 
					new UEBuildFramework( 
						"ParseCrashReporting",
						"../../lib/iOS/ParseCrashReporting.embeddedframework.zip"
					)
				); 
				PublicAdditionalFrameworks.Add( 
					new UEBuildFramework( 
						"ParseFacebookUtils",
						"../../lib/iOS/ParseFacebookUtils.embeddedframework.zip"
					)
				); 
				PublicAdditionalFrameworks.Add( 
					new UEBuildFramework( 
						"ParseFacebookUtilsV4",
						"../../lib/iOS/ParseFacebookUtilsV4.embeddedframework.zip"
					)
				); 
				PublicAdditionalFrameworks.Add( 
					new UEBuildFramework( 
						"ParseUI",
						"../../lib/iOS/ParseUI.embeddedframework.zip"
					)
				); 

				PublicFrameworks.AddRange( 
					new string[] 
					{ 
						"AudioToolbox",
						"CFNetwork",
						"CoreGraphics",
						"CoreLocation",
						"MobileCoreServices",
						"QuartzCore",
						"Security",
						"StoreKit",
						"SystemConfiguration"							
					}
				);
				
				AddThirdPartyPrivateStaticDependencies(Target, "libsqlite3");
				AddThirdPartyPrivateStaticDependencies(Target, "zlib");
			}
		}
	}
}
