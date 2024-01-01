// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Config/ConfigInitializeProxy.h"
#include "UltimateMobileKit.h"
#include "Config/ConfigLibrary.h"

UFirebaseConfigInitializeProxy::UFirebaseConfigInitializeProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseConfigInitializeProxy* UFirebaseConfigInitializeProxy::Init(const TArray<UFirebaseVariant*> DefaultParameters, const FString& ConfigNamespace/* = FString()*/)
{
	UFirebaseConfigInitializeProxy* Proxy = NewObject<UFirebaseConfigInitializeProxy>();
	Proxy->DefaultParameters = DefaultParameters;
	Proxy->ConfigNamespace = ConfigNamespace;
	return Proxy;
}

void UFirebaseConfigInitializeProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseConfigPtr FirebaseConfig = UltimateMobileKit->GetFirebaseConfig();

		if (FirebaseConfig.IsValid())
		{
			FOnFirebaseConfigInitializeCompleteDelegate InitializeCompleteDelegate = FOnFirebaseConfigInitializeCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseConfig->Init(DefaultParameters, ConfigNamespace, InitializeCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast();
}

void UFirebaseConfigInitializeProxy::OnQueryCompleted(bool bSuccess)
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
