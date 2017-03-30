//
//  Created by Derek van Vliet on 2015-03-25.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "IFacebookParse.h"

// You should place include statements to your module's private header files here.  You only need to
// add includes for headers that are used in most of your module's source files though.

#if PLATFORM_IOS
#import "IOSAppDelegate.h"
#import <Parse/Parse.h>
#import <ParseCrashReporting/ParseCrashReporting.h>
#import <FBSDKCoreKit/FBSDKCoreKit.h>
#import <FBSDKLoginKit/FBSDKLoginKit.h>

// HACK: fix for this problem: http://stackoverflow.com/questions/28898999/parse-api-1-6-4-cannot-build-project
extern NSString *const BFTaskMultipleExceptionsException = @"BFMultipleExceptionsException";
#endif

DECLARE_LOG_CATEGORY_EXTERN(LogFacebookParse, Log, All);

#include "FacebookParseClasses.h"
