// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Analytics/AnalyticsGetAnalyticsInstanceIdProxy.h"
#include "UltimateMobileKit.h"

UFirebaseAnalyticsGetAnalyticsInstanceIdProxy::UFirebaseAnalyticsGetAnalyticsInstanceIdProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseAnalyticsGetAnalyticsInstanceIdProxy* UFirebaseAnalyticsGetAnalyticsInstanceIdProxy::GetAnalyticsInstanceId()
{
	UFirebaseAnalyticsGetAnalyticsInstanceIdProxy* Proxy = NewObject<UFirebaseAnalyticsGetAnalyticsInstanceIdProxy>();
	return Proxy;
}

void UFirebaseAnalyticsGetAnalyticsInstanceIdProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAnalyticsPtr FirebaseAnalytics = UltimateMobileKit->GetFirebaseAnalytics();

		if (FirebaseAnalytics.IsValid())
		{
			FOnFirebaseAnalyticsGetAnalyticsInstanceIdCompleteDelegate GetAnalyticsInstanceIdCompleteDelegate = FOnFirebaseAnalyticsGetAnalyticsInstanceIdCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseAnalytics->GetAnalyticsInstanceId(GetAnalyticsInstanceIdCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast();
}

void UFirebaseAnalyticsGetAnalyticsInstanceIdProxy::OnQueryCompleted(bool bSuccess, const FString& AnalyticsInstanceId)
{
	if (bSuccess)
	{
		OnSuccess.Broadcast(AnalyticsInstanceId);
	}
	else
	{
		OnFailure.Broadcast();
	}
}
