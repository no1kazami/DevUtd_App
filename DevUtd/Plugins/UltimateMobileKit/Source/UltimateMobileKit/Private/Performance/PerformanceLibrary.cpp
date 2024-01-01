// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Performance/PerformanceLibrary.h"
#include "UltimateMobileKit.h"

UUltimateMobileKitPerformance::UUltimateMobileKitPerformance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

const bool UUltimateMobileKitPerformance::IsFirebasePerformanceInitialized()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebasePerformancePtr FirebasePerformance = UltimateMobileKit->GetFirebasePerformance();

		if (FirebasePerformance.IsValid())
		{
			return FirebasePerformance->IsInitialized();
		}
	}

	return false;
}
