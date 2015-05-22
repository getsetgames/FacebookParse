//
//  Created by Derek van Vliet on 2014-12-10.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#include "FacebookParsePrivatePCH.h"

FString UFacebookFunctions::FacebookGetAccessToken()
{
	FString Result;
	
#if PLATFORM_IOS
	if ([FBSDKAccessToken currentAccessToken])
	{
		Result = FString([FBSDKAccessToken currentAccessToken].tokenString);
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
#endif
	
	return Result;
}
