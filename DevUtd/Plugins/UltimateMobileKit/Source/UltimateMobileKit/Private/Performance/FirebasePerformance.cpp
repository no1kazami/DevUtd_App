// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Performance/FirebasePerformance.h"
#include "UltimateMobileKitComponent.h"

FFirebasePerformance::FFirebasePerformance()
{
}

FFirebasePerformance::~FFirebasePerformance()
{
}

void FFirebasePerformance::Init()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Performance Init"));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_PERFORMANCEMONITORING
	bInitialized = true;

#if PLATFORM_IOS
	TraceDictionary = [[[NSMutableDictionary alloc] autorelease] init];
#endif
#endif
}

void FFirebasePerformance::Shutdown()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Performance Shutdown"));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_PERFORMANCEMONITORING && PLATFORM_IOS
	[TraceDictionary dealloc];
	[TraceDictionary release];
#endif
}

const bool FFirebasePerformance::IsInitialized() const
{
	return bInitialized;
}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_PERFORMANCEMONITORING && PLATFORM_IOS
NSMutableDictionary* FFirebasePerformance::GetTraceDictionary()
{
	return TraceDictionary;
}
#endif
