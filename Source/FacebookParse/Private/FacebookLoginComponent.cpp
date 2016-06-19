//
//  Created by Derek van Vliet on 2015-03-25.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#include "FacebookParsePrivatePCH.h"
#include "CallbackDevice.h"

#if PLATFORM_IOS
NSArray* GetNSStringArray(TArray<FString> FStringArray)
{
	NSMutableArray* NewArray = [NSMutableArray array];
	
	for (auto Itr(FStringArray.CreateIterator()); Itr; Itr++)
	{
		FString String = (*Itr);
		[NewArray addObject:String.GetNSString()];
	}
	
	return NewArray;
}
#elif PLATFORM_ANDROID

#include "Android/AndroidJNI.h"
#include "AndroidApplication.h"

#endif

void UFacebookLoginComponent::OnRegister()
{
	Super::OnRegister();
	
	// init here
	FCoreDelegates::ApplicationOpenURLDelegate.AddUObject(this, &UFacebookLoginComponent::ApplicationOpenURL_Handler);
	UFacebookLoginComponent::FacebookLoginCancelledDelegate.AddUObject(this, &UFacebookLoginComponent::FacebookLoginCancelled_Handler);
	UFacebookLoginComponent::FacebookLoginErrorDelegate.AddUObject(this, &UFacebookLoginComponent::FacebookLoginError_Handler);
	UFacebookLoginComponent::FacebookLoginSucceededDelegate.AddUObject(this, &UFacebookLoginComponent::FacebookLoginSucceeded_Handler);
}

void UFacebookLoginComponent::OnUnregister()
{
	Super::OnUnregister();
	
	// clean up here
	
	FCoreDelegates::ApplicationOpenURLDelegate.RemoveAll(this);
	UFacebookLoginComponent::FacebookLoginCancelledDelegate.RemoveAll(this);
	UFacebookLoginComponent::FacebookLoginErrorDelegate.RemoveAll(this);
	UFacebookLoginComponent::FacebookLoginSucceededDelegate.RemoveAll(this);
}

void UFacebookLoginComponent::FacebookLoginWithReadPermissions(TArray<FString> Permissions)
{
#if PLATFORM_IOS
	dispatch_async(dispatch_get_main_queue(), ^{
		FBSDKLoginManager *login = [[FBSDKLoginManager alloc] init];
		[login logInWithReadPermissions:GetNSStringArray(Permissions) handler:^(FBSDKLoginManagerLoginResult *result, NSError *error)
		 {
			if (error)
			{
				UFacebookLoginComponent::FacebookLoginErrorDelegate.Broadcast(FString([error description]));
			}
			else if (result.isCancelled)
			{
				UFacebookLoginComponent::FacebookLoginCancelledDelegate.Broadcast();
			}
			else
			{
				UFacebookLoginComponent::FacebookLoginSucceededDelegate.Broadcast(UFacebookFunctions::FacebookGetUserId(), UFacebookFunctions::FacebookGetAccessToken(), UFacebookFunctions::FacebookGetAccessTokenExpirationDate());
			}
		 }];
	});
#elif PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        jobjectArray PermissionsArray = (jobjectArray)Env->NewObjectArray(Permissions.Num(), FJavaWrapper::JavaStringClass, NULL);
        
        for (uint32 Param = 0; Param < Permissions.Num(); Param++)
        {
            jstring p = Env->NewStringUTF(TCHAR_TO_UTF8(*Permissions[Param]));
            Env->SetObjectArrayElement(PermissionsArray, Param, p);
            Env->DeleteLocalRef(p);
        }
        
        static jmethodID Method = FJavaWrapper::FindMethod(Env,
                                                           FJavaWrapper::GameActivityClassID,
                                                           "AndroidThunk_Java_FacebookLoginWithReadPermissions",
                                                           "([Ljava/lang/String;)V",
                                                           false);
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, PermissionsArray);
        Env->DeleteLocalRef(PermissionsArray);
    }
#endif
}

void UFacebookLoginComponent::ApplicationOpenURL_Handler(FString URL, FString SourceApplication)
{
#if PLATFORM_IOS
	IOSAppDelegate* appDelegate = (IOSAppDelegate*)[[UIApplication sharedApplication] delegate];
	
	[[FBSDKApplicationDelegate sharedInstance] application:[UIApplication sharedApplication]
												   openURL:[NSURL URLWithString:URL.GetNSString()]
										 sourceApplication:SourceApplication.GetNSString()
												annotation:appDelegate.launchAnnotation];
#endif
}

UFacebookLoginComponent::FFacebookLoginSucceededDelegate UFacebookLoginComponent::FacebookLoginSucceededDelegate;
UFacebookLoginComponent::FFacebookLoginCancelledDelegate UFacebookLoginComponent::FacebookLoginCancelledDelegate;
UFacebookLoginComponent::FFacebookLoginErrorDelegate UFacebookLoginComponent::FacebookLoginErrorDelegate;
