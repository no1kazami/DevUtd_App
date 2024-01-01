// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Analytics/AnalyticsInitializeProxy.h"
#include "UltimateMobileKit.h"

UFirebaseAnalyticsInitializeProxy::UFirebaseAnalyticsInitializeProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseAnalyticsInitializeProxy* UFirebaseAnalyticsInitializeProxy::Init()
{
	UFirebaseAnalyticsInitializeProxy* Proxy = NewObject<UFirebaseAnalyticsInitializeProxy>();
	return Proxy;
}

void UFirebaseAnalyticsInitializeProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAnalyticsPtr FirebaseAnalytics = UltimateMobileKit->GetFirebaseAnalytics();

		if (FirebaseAnalytics.IsValid())
		{
			FOnFirebaseAnalyticsInitializeCompleteDelegate InitializeCompleteDelegate = FOnFirebaseAnalyticsInitializeCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseAnalytics->Init(InitializeCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast();
}

void UFirebaseAnalyticsInitializeProxy::OnQueryCompleted(bool bSuccess)
{
	if (bSuccess)
	{
		OnSuccess.Broadcast();
	}
	else
	{
		OnFailure.Broadcast();
	}
}
