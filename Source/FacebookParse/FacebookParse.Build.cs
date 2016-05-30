//
//  Created by Derek van Vliet on 2015-03-25.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

using System.IO;

namespace UnrealBuildTool.Rules
{
	public class FacebookParse : ModuleRules
	{
		public FacebookParse(TargetInfo Target)
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
						"FacebookSDK",
						"../../lib/iOS/FacebookSDK.embeddedframework.zip"
					)
				);
				PublicAdditionalFrameworks.Add(
					new UEBuildFramework(
						"FBSDKCoreKit",
						"../../lib/iOS/FBSDKCoreKit.embeddedframework.zip"
					)
				);
				PublicAdditionalFrameworks.Add(
					new UEBuildFramework(
						"FBSDKLoginKit",
						"../../lib/iOS/FBSDKLoginKit.embeddedframework.zip"
					)
				);
				PublicAdditionalFrameworks.Add(
					new UEBuildFramework(
						"FBSDKShareKit",
						"../../lib/iOS/FBSDKShareKit.embeddedframework.zip"
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
				
				// PublicAdditionalFrameworks.Add(
				// 	new UEBuildFramework(
				// 		"ParseUI",
				// 		"../../lib/iOS/ParseUI.embeddedframework.zip"
				// 	)
				// );

				PublicFrameworks.AddRange(
					new string[]
					{
						"Accounts",
						"AudioToolbox",
						"CFNetwork",
						"CoreGraphics",
						"CoreLocation",
						"MobileCoreServices",
						"QuartzCore",
						"Social",
						"Security",
						"StoreKit",
						"SystemConfiguration"
					}
				);

				PublicAdditionalLibraries.Add("sqlite3");
				PublicAdditionalLibraries.Add("z");
                PublicAdditionalLibraries.Add("stdc++.6");
			}
			else if(Target.Platform == UnrealTargetPlatform.Android)
			{
				string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, BuildConfiguration.RelativeEnginePath);
				AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(PluginPath, "FacebookParse_APL.xml")));
			}
		}
	}
}
