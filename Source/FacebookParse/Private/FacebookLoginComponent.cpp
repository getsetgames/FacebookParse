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

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeFacebookOnLoginComplete(JNIEnv* jenv, jobject thiz)
{
    UFacebookLoginComponent::FacebookLoginSucceededDelegate.Broadcast
    (
        UFacebookFunctions::FacebookGetUserId(),
        UFacebookFunctions::FacebookGetAccessToken(),
        UFacebookFunctions::FacebookGetAccessTokenExpirationDate()
    );
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeFacebookOnLoginCancelled(JNIEnv* jenv, jobject thiz)
{
    UFacebookLoginComponent::FacebookLoginCancelledDelegate.Broadcast();
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeFacebookOnLoginError(JNIEnv* jenv, jobject thiz, jstring error)
{
	FString Error;

	const char* charsError = jenv->GetStringUTFChars(error, 0);
	Error = FString(UTF8_TO_TCHAR(charsError));
	jenv->ReleaseStringUTFChars(error, charsError);

    UFacebookLoginComponent::FacebookLoginErrorDelegate.Broadcast(Error);
}

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
		FString p;

		const int32 kNumPermissions = Permissions.Num();

		for (int32 i = 0; i < kNumPermissions; i++)
		{
			p += Permissions[i];

			if (i < kNumPermissions - 1)
			{
				p += ",";
			}
		}

		jstring j = Env->NewStringUTF(TCHAR_TO_UTF8(*p));

        static jmethodID Method = FJavaWrapper::FindMethod(Env,
                                                           FJavaWrapper::GameActivityClassID,
                                                           "AndroidThunk_Java_FacebookLoginWithReadPermissions",
                                                           "(Ljava/lang/String;)V",
                                                           false);
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, j);
		Env->DeleteLocalRef(j);
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
