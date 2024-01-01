// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthLibrary.h"
#include "UltimateMobileKit.h"

UUltimateMobileKitAuth::UUltimateMobileKitAuth(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

const bool UUltimateMobileKitAuth::IsFirebaseAuthenticationInitialized()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid())
		{
			return FirebaseAuth->IsInitialized();
		}
	}

	return false;
}

void UUltimateMobileKitAuth::SignOut()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid())
		{
			return FirebaseAuth->SignOut();
		}
	}
}

const bool UUltimateMobileKitAuth::IsUserLoggedIn()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid())
		{
			return FirebaseAuth->IsUserLoggedIn();
		}
	}

	return false;
}

const FFirebaseUser UUltimateMobileKitAuth::GetLoggedUser()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid())
		{
			return FirebaseAuth->GetLoggedUser();
		}
	}

	return FFirebaseUser();
}
