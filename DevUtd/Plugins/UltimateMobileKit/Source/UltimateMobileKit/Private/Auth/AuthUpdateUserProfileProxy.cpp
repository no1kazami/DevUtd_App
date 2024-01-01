// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthUpdateUserProfileProxy.h"
#include "UltimateMobileKit.h"

UFirebaseAuthUpdateUserProfileProxy::UFirebaseAuthUpdateUserProfileProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseAuthUpdateUserProfileProxy* UFirebaseAuthUpdateUserProfileProxy::UpdateUserProfile(const FFirebaseUserProfile UserProfile)
{
	UFirebaseAuthUpdateUserProfileProxy* Proxy = NewObject<UFirebaseAuthUpdateUserProfileProxy>();
	Proxy->UserProfile = UserProfile;
	return Proxy;
}

void UFirebaseAuthUpdateUserProfileProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid() && FirebaseAuth->IsInitialized())
		{
			FOnFirebaseAuthUpdateUserProfileCompleteDelegate UpdateUserProfileCompleteDelegate = FOnFirebaseAuthUpdateUserProfileCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseAuth->UpdateUserProfile(UserProfile, UpdateUserProfileCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseAuthError::ApiNotAvailable);
}

void UFirebaseAuthUpdateUserProfileProxy::OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error)
{
	if (bSuccess)
	{
		OnSuccess.Broadcast(Error);
	}
	else
	{
		OnFailure.Broadcast(Error);
	}
}
