//
//  Created by Derek van Vliet on 2014-12-10.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#include "FacebookParsePrivatePCH.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "AndroidApplication.h"
#endif

FString UFacebookFunctions::FacebookGetAccessToken()
{
	FString Result;

#if PLATFORM_IOS
	if ([FBSDKAccessToken currentAccessToken])
	{
		Result = FString([FBSDKAccessToken currentAccessToken].tokenString);
	}
#elif PLATFORM_ANDROID

	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env,
			FJavaWrapper::GameActivityClassID,
			"AndroidThunk_Java_FacebookGetAccessToken",
			"()Ljava/lang/String;",
			false);
		jstring AccessToken = (jstring)FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, Method);

		const char *s = Env->GetStringUTFChars(AccessToken, 0);
		Result = FString(UTF8_TO_TCHAR(s));

		Env->ReleaseStringUTFChars(AccessToken, s);
	}
#endif
	
	return Result;
}

FString UFacebookFunctions::FacebookGetAccessTokenExpirationDate()
{
	FString Result;
	
#if PLATFORM_IOS
	if ([FBSDKAccessToken currentAccessToken])
	{
		NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
		NSLocale *enUSPOSIXLocale = [NSLocale localeWithLocaleIdentifier:@"en_US_POSIX"];
		[dateFormatter setLocale:enUSPOSIXLocale];
		[dateFormatter setDateFormat:@"yyyy-MM-dd'T'HH:mm:ss.SSS'Z'"];
		
		Result = FString([dateFormatter stringFromDate:[FBSDKAccessToken currentAccessToken].expirationDate]);
	}
#elif PLATFORM_ANDROID

	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env,
			FJavaWrapper::GameActivityClassID,
			"AndroidThunk_Java_FacebookGetAccessTokenExpirationDate",
			"()Ljava/lang/String;",
			false);
		jstring ExpirationDate = (jstring)FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, Method);

		const char *s = Env->GetStringUTFChars(ExpirationDate, 0);
		Result = FString(UTF8_TO_TCHAR(s));

		Env->ReleaseStringUTFChars(ExpirationDate, s);
	}
#endif
	
	return Result;
}

FString UFacebookFunctions::FacebookGetUserId()
{
	FString Result;

#if PLATFORM_IOS
	if ([FBSDKAccessToken currentAccessToken])
	{
		Result = FString([FBSDKAccessToken currentAccessToken].userID);
	}
#elif PLATFORM_ANDROID

	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env,
			FJavaWrapper::GameActivityClassID,
			"AndroidThunk_Java_FacebookGetUserId",
			"()Ljava/lang/String;",
			false);
		jstring UserId = (jstring)FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, Method);

		const char *s = Env->GetStringUTFChars(UserId, 0);
		Result = FString(UTF8_TO_TCHAR(s));

		Env->ReleaseStringUTFChars(UserId, s);
	}
#endif
	
	return Result;
}
