// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "Delegates/FirebasePerformanceDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_PERFORMANCEMONITORING && PLATFORM_IOS
#import <FirebasePerformance/FirebasePerformance.h>
#endif

class ULTIMATEMOBILEKIT_API FFirebasePerformance
{
public:
	FFirebasePerformance();
	virtual ~FFirebasePerformance();

	/** Initialize the Firebase Performance API  */
	void Init();

	/** Shutdown the Firebase Performance API  */
	void Shutdown();

	/** Check if Firebase Performance is initialized */
	const bool IsInitialized() const;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_PERFORMANCEMONITORING && PLATFORM_IOS
	NSMutableDictionary* GetTraceDictionary();
#endif

private:
	bool bInitialized = false;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_PERFORMANCEMONITORING && PLATFORM_IOS
	NSMutableDictionary* TraceDictionary;
#endif
};
