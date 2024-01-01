// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "App/AppMakeGooglePlayAvailableProxy.h"
#include "UltimateMobileKit.h"

UFirebaseAppMakeGooglePlayAvailableProxy::UFirebaseAppMakeGooglePlayAvailableProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseAppMakeGooglePlayAvailableProxy* UFirebaseAppMakeGooglePlayAvailableProxy::MakeGooglePlayAvailable()
{
	UFirebaseAppMakeGooglePlayAvailableProxy* Proxy = NewObject<UFirebaseAppMakeGooglePlayAvailableProxy>();
	return Proxy;
}

void UFirebaseAppMakeGooglePlayAvailableProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAppPtr FirebaseApp = UltimateMobileKit->GetFirebaseApp();

		if (FirebaseApp.IsValid() && FirebaseApp->IsInitialized())
		{
			FOnFirebaseMakeGooglePlayAvailableCompleteDelegate MakeGooglePlayAvailableCompleteDelegate = FOnFirebaseMakeGooglePlayAvailableCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseApp->MakeGooglePlayAvailable(MakeGooglePlayAvailableCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast();
}

void UFirebaseAppMakeGooglePlayAvailableProxy::OnQueryCompleted(bool bSuccess)
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
